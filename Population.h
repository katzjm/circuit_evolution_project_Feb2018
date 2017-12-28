/*
 * A Population is a collection of Networks
 *
 * Author: Josh Katz
 */

#ifndef _POPULATION_H_
#define _POPULATION_H_

#include "Reaction.h"
#include "Network.h"
#include "Config.h"

typedef struct population_str {
    Network_Ptr networks;
    int num_networks;
} Population, *Population_Ptr;

Population_Ptr GetRandomPopulation(Config_Ptr pconfig);

void KillPopulation(Population_Ptr pop);

Population_Ptr GetNextGeneration(Population_Ptr pop);

#endif // _POPULATION_H_
