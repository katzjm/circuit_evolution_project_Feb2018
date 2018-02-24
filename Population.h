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
  Network_Ptr *old_network_order;

  Network_Ptr networks;
  Network_Ptr old_networks;
  
  int num_networks;
  N_Vector concentrations;
  CvodeData cvode_data;
  UserData user_data;
} Population, *Population_Ptr;

// Fills the population pop with networks, all evaluated
int SetFirstGeneration(Population_Ptr pop, Config_Ptr config);

// Sets the next generation of networks in the population. This includes
// cloning, mutation and reevaluation of networks in the new generation
int SetNextGeneration(Population_Ptr pop, Config_Ptr c);

// Returns the fitness of the best network in the population
double BestFitness(Population_Ptr pop);

// Through returnbuf, returns the status of the population without the
// best network
void GetSmallStatus(Population_Ptr pop, char *returnbuf);

// Through returnbuf, returns the status of the population with the
// best network
void GetLargeStatus(Population_Ptr pop, char *returnbuf, Config_Ptr c);

// Destroys the memory required to keep the population
void KillPopulation(Population_Ptr pop);

#endif // _POPULATION_H_
