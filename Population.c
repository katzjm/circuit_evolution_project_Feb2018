/*
 * Implements methods for manipulating Populations
 *
 * Author: Josh Katz
 */

#include <stdlib.h>

#include "Population.h"
#include "Configs.h"

static int EvaluatePopulation(Population_Ptr pop, Config_Ptr c) {
  N_Vector concentrations = GetInitialConcentrations(c);

  for (int i = 0; i < pop->num_networks; i++) {
    EvaluateNetwork(&pop->networks[i], c, concentrations);
  }

  N_VDestroy(concentrations);
  return 0;
}

int SetFirstGeneration(Population_Ptr pop, Config_Ptr config) {
  pop->num_networks = config->max_pop_size;
  pop->network_order = (Network_Ptr*)
                       malloc(sizeof(Network_Ptr) * pop->num_networks);
  pop->networks = (Network_Ptr) malloc(sizeof(Network) * pop->num_networks);

  if (pop->networks == NULL) {
    return 1;
  }

  for (int i = 0; i < pop->num_networks; i++) {
    SetRandomNetwork(&pop->networks[i], config);
    pop->network_order[i] = &pop->networks[i];
  }
  return 0;
}

void KillPopulation(Population_Ptr pop) {
  free(pop->networks);
  free(pop->network_order);
  pop->networks = NULL;
  pop->network_order = NULL;
  pop->num_networks = 0;
}

int SetNextGeneration(Population_Ptr pop) {
  
}
