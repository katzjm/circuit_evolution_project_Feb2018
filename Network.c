/*
* A Network represents a group of reactions that governs how different
* reagents interact with one another. Note that a Network can support
* MAX_NUM_REACTIONS at a time
*
* Author: Josh Katz
*/

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#include "nvector/nvector_serial.h"

#include "Network.h"
#include "Reaction.h"
#include "Configs.h"
#include "Cvode_Utils.h"

static void SetSourcesAndSinks(Network_Ptr network) {
  // Initially sources and sinks simply mark whether a species appears as a
  // reactant or product, respectively. Mark no species initially 
  network->sources = 0;
  network->sinks = 0;
  network->in_network = 0;

  // Mark every species in every reaction
  for (int i = 0; i < network->num_reactions; i++) {
    Reaction_Ptr reaction = &network->reactions[i];

    network->sources |= (1 << reaction->reactant_1);
    network->sinks |= (1 << reaction->product_1);
    if (reaction->reactant_2 != NO_REAGENT) {
      network->sources |= (1 << reaction->reactant_2);
    }
    if (reaction->product_2 != NO_REAGENT) {
      network->sinks |= (1 << reaction->product_2);
    }
  }

  // If a species appears in both sources and sinks it is neither, so remove
  // the mark for that species in both sources and sinks
  int source_and_sink = network->sources & network->sinks;
  network->in_network = network->sources | network->sinks;
  network->sources &= ~source_and_sink;
  network->sinks &= ~source_and_sink;
}

bool IsSource(Network_Ptr network, species_t species) {
  return (network->sources & (1 << species)) != 0;
}

bool IsSink(Network_Ptr network, species_t species) {
  return (network->sinks & (1 << species)) != 0;
}

bool IsInNetwork(Network_Ptr network, species_t species) {
  return (network->in_network & (1 << species)) != 0;
}

bool IsChanging(Network_Ptr network, species_t species) {
  return species != NO_REAGENT
         && IsInNetwork(network, species)
         && !IsSource(network, species)
         && !IsSink(network, species);
}


void SetRandomNetwork(Network_Ptr network, Config_Ptr config) {
  int reaction_range = config->max_num_reactions - config->min_num_reactions;
  network->num_reactions = rand() % reaction_range + config->min_num_reactions;
  network->fitness = INFINITY;
  for (int i = 0; i < network->num_reactions; i++) {
    SetRandomReaction(&network->reactions[i], config);
  }
  SetSourcesAndSinks(network);
}

// Simple min function. Should not be used when either x or y need to be
// evaluated before comparison
#define min(x, y) (((x) <= (y)) ? (x) : (y))

void SetNetwork(Network_Ptr network,
                Reaction_Ptr reactions,
                double fitness,
                int num_reactions) {
  network->num_reactions = min(num_reactions, MAX_NUM_REACTIONS);
  network->fitness = fitness;
  for (int i = 0; i < network->num_reactions; i++) {
    network->reactions[i] = reactions[i];
  }
  SetSourcesAndSinks(network);
}

#undef min

void MutateNetwork(Network_Ptr network, Config_Ptr config) {
  float mutation = (float) rand() / RAND_MAX;
  bool network_changed = false;

  if ((mutation -= config->prob_add_reaction) <= 0) {
    network_changed = AddReaction(network, config);
  } else if ((mutation -= config->prob_remove_reaction) <= 0) {
    network_changed = RemoveReaction(network);
  }

  if (mutation > 0 || network_changed == false) {
    ModifyRateConstant(network, config);
  }
}

bool AddReaction(Network_Ptr network, Config_Ptr config) {
  if (network->num_reactions == MAX_NUM_REACTIONS) {
    return false;
  }

  SetRandomReaction(&network->reactions[network->num_reactions], config);
  network->num_reactions++;
  SetSourcesAndSinks(network);
  return true;
}

bool RemoveReaction(Network_Ptr network) {
  if (network->num_reactions <= 1) {
    return false;
  }
  network->num_reactions--;
  SetSourcesAndSinks(network);
  return true;
}

void ModifyRateConstant(Network_Ptr network, Config_Ptr config) {
  if (network->num_reactions < 1) {
    return;
  }

  int reaction_to_change = rand() % network->num_reactions;
  MutateRateConstant(&network->reactions[reaction_to_change], config);
}

static void SetInitialConcentrations(Network_Ptr network,
                                     CvodeData_Ptr cvode_data,
                                     Config_Ptr c,
                                     int data_point) {
  realtype *init_concentration_data = NV_DATA_S(cvode_data->concentration_mem);

  bool source_found = false;
  for (int i = 0; i < c->num_species; i++) {
    if (c->time_based || source_found || !IsSource(network, i)) {
      init_concentration_data[i] = c->initial_concentrations;
    } else {
      init_concentration_data[i] = c->outputs[data_point];
      source_found = true;
    }
  }
}

static void UpdateSpeciesFitnesses(double *species_fitness,
                                   Network_Ptr network,
                                   double target,
                                   Config_Ptr c,
                                   CvodeData_Ptr cvode_data) {
  for (int i = 0; i < c->num_species; i++) {
    if (IsChanging(network, i)) {
      double found = NV_Ith_S(cvode_data->concentration_mem, i);
      species_fitness[i] += pow(found - target, 2);
    } else {
      species_fitness[i] = INFINITY;
    }
  }
}

static void SetNetworkFitness(Network_Ptr network,
                              double *species_fitness,
                              Config_Ptr c) {
  network->fitness = INFINITY;
  for (int i = 0; i < c->num_species; i++) {
    if (species_fitness[i] < network->fitness) {
      network->fitness = species_fitness[i];
    }
  }
}

static int EvaluateNetworkVsTime(Network_Ptr network,
                                 Config_Ptr c,
                                 CvodeData_Ptr cvode_data) {
  double species_fitness[c->num_species];
  memset(species_fitness, 0, sizeof(species_fitness[0]) * c->num_species);

  realtype t = 0;
  // TODO put SetInitialConcentrations in Cvode Setup because it's necessary for initialization
  SetInitialConcentrations(network, cvode_data, c, -1);
  SetUpCvodeNextRun(cvode_data);
  for (int i = 0; i < c->num_data_pts; i++) {
    realtype tout = c->inputs[i];
    if (tout != t) {
      if (!RunCvode(cvode_data, tout, &t)) {
        network->fitness = INFINITY;
        return 1;
      }
    }
    UpdateSpeciesFitnesses(species_fitness,
                           network,
                           c->outputs[i],
                           c, cvode_data);
  }
  SetNetworkFitness(network, species_fitness, c);
  return 0;
}

static int EvaluateNetworkVsConcentration(Network_Ptr network,
                                          Config_Ptr c,
                                          CvodeData_Ptr cvode_data,
                                          UserData_Ptr user_data) {
  realtype t_spacing = 2;
  realtype t_max = 50;
  realtype steady_state_threshold = 0.001;

  double species_fitness[c->num_species];
  memset(species_fitness, 0, sizeof(species_fitness[0]) * c->num_species);
  N_Vector species_rate_change = N_VNew_Serial(c->num_species);
  for (int i = 0; i < c->num_data_pts; i++) {
    SetInitialConcentrations(network, cvode_data, c, i);
    SetUpCvodeNextRun(cvode_data);

    realtype t = 0;
    realtype tout = t_spacing;
    realtype steady_state_score;
    do {
      if (!RunCvode(cvode_data, tout, &t)) {
        network->fitness = INFINITY;
        return 1;
      }
      tout += t_spacing;

      if (fabs(t - t_spacing) > DBL_EPSILON) {
        GetSpeciesRateOfChange(t, cvode_data->concentration_mem,
                               species_rate_change, &user_data);
        steady_state_score = N_VL1Norm(species_rate_change);
      } else {
        steady_state_score = INFINITY;
      }
    } while (steady_state_score > steady_state_threshold && t < t_max);
    
    if (t >= t_max) {
      network->fitness = INFINITY;
      return 1;
    }
    UpdateSpeciesFitnesses(species_fitness,
                           network,
                           c->outputs[i],
                           c, cvode_data);
  }
  SetNetworkFitness(network, species_fitness, c);
  N_VDestroy_Serial(species_rate_change);
  return 0;
}

int EvaluateNetwork(Network_Ptr network,
                    Config_Ptr c,
                    CvodeData_Ptr cvode_data,
                    UserData_Ptr user_data) {
  user_data->network = network;
  if (c->time_based) {
    return EvaluateNetworkVsTime(network, c, cvode_data);
  } else {
    return EvaluateNetworkVsConcentration(network, c, cvode_data, user_data);
  }
}

void GetNetworkString(Network_Ptr network,
                      char *return_buf,
                      const char *pre_reaction,
                      const char *post_reaction) {
  strcpy(return_buf, pre_reaction);
  for (int i = 0; i < network->num_reactions; i++) {
    char reaction_buf[32];
    GetReactionString(&network->reactions[i], reaction_buf, i);
    if (i != 0) {
      strncat(return_buf, pre_reaction, 32);
    }
    strncat(return_buf, reaction_buf, 32);
    strncat(return_buf, post_reaction, 32);
  }
}
