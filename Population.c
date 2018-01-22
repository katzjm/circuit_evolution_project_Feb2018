/*
 * Implements methods for manipulating Populations
 *
 * Author: Josh Katz
 */

#include <stdlib.h>
#include <stdio.h>
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

static int EvaluatePopulation(Population_Ptr pop,
                              Config_Ptr c,
                              CvodeData_Ptr cvode_data,
                              UserData_Ptr user_data) {
  for (int i = 0; i < pop->num_networks; i++) {
    EvaluateNetwork(&pop->networks[i], c, cvode_data, user_data);
  }
  qsort(pop->network_order,
        pop->num_networks,
        sizeof(Network_Ptr),
        CompareNetworks);
  return 0;
}

int SetFirstGeneration(Population_Ptr pop,
                       Config_Ptr config,
                       CvodeData_Ptr cvode_data,
                       UserData_Ptr user_data) {
  pop->num_networks = config->max_pop_size;
  pop->network_order = (Network_Ptr*)
                       malloc(sizeof(Network_Ptr) * pop->num_networks);
  pop->networks = (Network_Ptr) malloc(sizeof(Network) * pop->num_networks);

  if (pop->networks == NULL || pop->network_order == NULL) {
    return 1;
  }

  for (int i = 0; i < pop->num_networks; i++) {
    SetRandomNetwork(&pop->networks[i], config);
    pop->network_order[i] = &pop->networks[i];
  }
  EvaluatePopulation(pop, config, cvode_data, user_data);
  return 0;
}

void KillPopulation(Population_Ptr pop) {
  free(pop->networks);
  free(pop->network_order);
  pop->networks = NULL;
  pop->network_order = NULL;
  pop->num_networks = 0;
}

double BestFitness(Population_Ptr pop) {
  return pop->network_order[0]->fitness;
}

int SetNextGeneration(Population_Ptr pop,
                      Config_Ptr c,
                      CvodeData_Ptr cvode_data,
                      UserData_Ptr user_data) {
  Network_Ptr new_networks = (Network_Ptr) 
                             malloc(sizeof(Network) * pop->num_networks);

  new_networks[0] = pop->networks[0];
  for (int i = 1; i < pop->num_networks; i++) {
    int cloned_network_index = fmin(rand() % pop->num_networks,
                                    rand() % pop->num_networks);
    new_networks[i] = pop->networks[cloned_network_index];
    MutateNetwork(&new_networks[i], c);
  }
  
  free(pop->networks);
  pop->networks = new_networks;
  EvaluatePopulation(pop, c, cvode_data, user_data);
  return 0;
}

void GetSmallStatus(Population_Ptr pop, char *returnbuf) {
  sprintf(returnbuf, "Fittest: %lf", BestFitness(pop));
}

void GetLargeStatus(Population_Ptr pop, char *returnbuf) {
  sprintf(returnbuf, "Fittest: %lf", BestFitness(pop));
}


