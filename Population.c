/*
 * Implements methods for manipulating Populations
 *
 * Author: Josh Katz
 */

#include <stdlib.h>

#include "Population.h"
#include "Configs.h"

int SetRandomPopulation(Population_Ptr pop, Config_Ptr config) {
  pop->num_networks = config->max_pop_size;
  pop->networks = (Network_Ptr) malloc(sizeof(Network) * pop->num_networks);

  if (pop->networks == NULL) {
    return 1;
  }

  for (int i = 0; i < pop->num_networks; i++) {
    SetRandomNetwork(&pop->networks[i], config);
  }
  return 0;
}

void KillPopulation(Population_Ptr pop) {
  free(pop->networks);
  pop->networks = NULL;
  pop->num_networks = 0;
}

int SetNextGeneration(Population_Ptr pop) {

}
