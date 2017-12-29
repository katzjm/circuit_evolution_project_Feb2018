/*
 * A Population is a collection of Networks
 *
 * Author: Josh Katz
 */

#ifndef _POPULATION_H_
#define _POPULATION_H_

#include "Network.h"
#include "Configs.h"

typedef struct population_str {
    Network_Ptr networks;
    int num_networks;
} Population, *Population_Ptr;

int SetFirstGeneration(Population_Ptr pop, Config_Ptr config);

double BestFitness(Population_Ptr pop);

void EvaluateGeneration(Population_Ptr pop, Config_Ptr c);

void PrintSmallStatus(Population_Ptr pop);

void PrintLargeStatus(Population_Ptr pop);

void KillPopulation(Population_Ptr pop);

int SetNextGeneration(Population_Ptr pop);

#endif // _POPULATION_H_
