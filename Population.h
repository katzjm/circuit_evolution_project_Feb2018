/*
 * A Population is a collection of Networks
 *
 * Author: Josh Katz
 */

#ifndef _POPULATION_H_
#define _POPULATION_H_

#include "Network.h"
#include "Configs.h"
#include "Cvode_Utils.h"

typedef struct population_str {
  Network_Ptr *network_order;
  Network_Ptr networks;
  int num_networks;
  N_Vector concentrations;
  CvodeData cvode_data;
  UserData user_data;
} Population, *Population_Ptr;

int SetFirstGeneration(Population_Ptr pop, Config_Ptr config);

double BestFitness(Population_Ptr pop);

void GetSmallStatus(Population_Ptr pop, char *returnbuf);

void GetLargeStatus(Population_Ptr pop, char *returnbuf);

void KillPopulation(Population_Ptr pop);

int SetNextGeneration(Population_Ptr pop, Config_Ptr c);

#endif // _POPULATION_H_
