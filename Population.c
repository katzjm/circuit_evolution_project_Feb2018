/*
 * Implements methods for manipulating Populations
 *
 * Author: Josh Katz
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "Population.h"
#include "Configs.h"

static int CompareNetworks(const void *a, const void *b) {
  Network_Ptr network_a = *((Network_Ptr *) a);
  Network_Ptr network_b = *((Network_Ptr *) b);
  if (network_a->fitness < network_b->fitness) {
    return -1;
  } else if (network_a->fitness > network_b->fitness) {
    return 1;
  }
  return 0;
}

static int EvaluatePopulation(Population_Ptr pop, Config_Ptr c) {
  for (int i = 0; i < pop->num_networks; i++) {
    EvaluateNetwork(&pop->networks[i], c, &pop->cvode_data, &pop->user_data);
    if (pop->networks[i].fitness == INFINITY) {
      SetRandomNetwork(&pop->networks[i], c);
      EvaluateNetwork(&pop->networks[i], c, &pop->cvode_data, &pop->user_data);
    }
  }
  qsort(pop->network_order,
        pop->num_networks,
        sizeof(Network_Ptr),
        CompareNetworks);
  return 0;
}

int SetFirstGeneration(Population_Ptr pop, Config_Ptr c) {
  pop->num_networks = c->max_pop_size;
  pop->network_order = (Network_Ptr*)
                       malloc(sizeof(Network_Ptr) * pop->num_networks);
  pop->networks = (Network_Ptr) malloc(sizeof(Network) * pop->num_networks);
  if (pop->networks == NULL || pop->network_order == NULL) {
    return 1;
  }

  for (int i = 0; i < pop->num_networks; i++) {
    SetRandomNetwork(&pop->networks[i], c);
    pop->network_order[i] = &pop->networks[i];
  }
  
  pop->concentrations = GetNewNVector(c);
  pop->cvode_data.cvode_mem = NULL;
  pop->cvode_data.concentration_mem = pop->concentrations;
  pop->user_data.network = &pop->networks[0];
  pop->user_data.config = c;
  SetUpCvodeFirstRun(&pop->cvode_data, &pop->user_data);

  EvaluatePopulation(pop, c);
  return 0;
}

void KillPopulation(Population_Ptr pop) {
  free(pop->networks);
  pop->networks = NULL;

  free(pop->network_order);
  pop->network_order = NULL;

  pop->num_networks = 0;

  DestroyCvode(&pop->cvode_data);
}

double BestFitness(Population_Ptr pop) {
  return pop->network_order[0]->fitness;
}

int SetNextGeneration(Population_Ptr pop, Config_Ptr c) {
  Network_Ptr new_networks = (Network_Ptr) 
                             malloc(sizeof(Network) * pop->num_networks);

  new_networks[0] = *pop->network_order[0];
  pop->network_order[0] = &new_networks[0];
  for (int i = 1; i < pop->num_networks; i++) {
    int cloned_network_index = fmin(rand() % pop->num_networks,
                                    rand() % pop->num_networks);
    new_networks[i] = *pop->network_order[cloned_network_index];
    pop->network_order[i] = &new_networks[i];
    MutateNetwork(&new_networks[i], c);
  }
  
  free(pop->networks);
  pop->networks = new_networks;
  EvaluatePopulation(pop, c);
  return 0;
}

void GetSmallStatus(Population_Ptr pop, char *return_buf) {
  sprintf(return_buf, "Fittest: %lf", BestFitness(pop));
}

void GetLargeStatus(Population_Ptr pop, char *return_buf, Config_Ptr c) {
  char network_buf[1024];
  char concentration_buf[512];
  GetNetworkString(pop->network_order[0], network_buf, "   ", "\n"); 
  sprintf(return_buf, "Fittest: \n%s", network_buf);

  strncat(return_buf, "\n   ", 10);
  SetInitialConcentrations(pop->network_order[0], &pop->cvode_data, c, 0);
  for (int i = 0; i < c->num_species; i++) {
    sprintf(concentration_buf, "S%d = %lf; ", i, NV_Ith_S(pop->concentrations, i));
    strncat(return_buf, concentration_buf, 32);
  }
  strncat(return_buf, "\n", 2);
}

