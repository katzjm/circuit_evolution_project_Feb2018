/*
 * Implements basic helper methods for using Cvode
 *
 * Author: Josh Katz
 */

#include <stdio.h>
#include <string.h>

#include "cvode/cvode.h"
#include "cvode/cvode_dense.h"
#include "nvector/nvector_serial.h"

#include "Cvode_Utils.h"
#include "Configs.h"
#include "Network.h"
#include "Reaction.h"

int SetUpCVodeInitial(void **cvode_mem,
                      N_Vector species_concentrations,
                      Data_Ptr data) {
  int flag;

  *cvode_mem = CVodeCreate(CV_BDF, CV_NEWTON);
  if (*cvode_mem == NULL) {
    printf("Failed to create CVode");
    return 1;
  }

  flag = CVodeInit(*cvode_mem, NetworkToOde, 0, species_concentrations);
  if (flag != CV_SUCCESS) {
    printf("Failed to initialize CVode");
    return 1;
  }

  flag = CVodeSStolerances(*cvode_mem, RCONST(1.0e-6), RCONST(1.0e-12));
  if (flag != CV_SUCCESS) {
    printf("Failed to set tolerances");
    return 1;
  }

  if (!data->config->show_cvode_errors) {
    flag = CVodeSetErrFile(*cvode_mem, NULL);
    if (flag != CV_SUCCESS) {
      puts("Failed Setting Error File");
      return 1;
    }
  }

  flag = CVodeSetUserData(*cvode_mem, data);
  if (flag != CV_SUCCESS) {
    puts("Failed data setting");
    return 1;
  }

  flag = CVDense(*cvode_mem, data->config->num_species);
  if (flag != CV_SUCCESS) {
    puts("Failed CVDense Initialization");
    return 1;
  }

  return 0;

}

int NetworkToOde(realtype t,
                 N_Vector concentrations,
                 N_Vector rate_of_change,
                 void *user_data) {
  Network_Ptr network = ((Data_Ptr) user_data)->network;
  Config_Ptr c = ((Data_Ptr) user_data)->config;
  
//TODO add something to deal with sources and sinks

  realtype *rate_of_change_data = NV_DATA_S(rate_of_change);
  memset(rate_of_change_data, 0, sizeof(realtype) * c->num_species);

  for (int i = 0; i < network->num_reactions; i++) {
    Reaction_Ptr reaction = &network->reactions[i];
    realtype reaction_rate_of_change = GetRateOfChange(reaction,
                                                       concentrations);
    rate_of_change_data[reaction->reactant_1] -= reaction_rate_of_change;
    rate_of_change_data[reaction->product_1] += reaction_rate_of_change;
    if (reaction->reactant_2 != NO_REAGENT) {
      rate_of_change_data[reaction->reactant_2] -= reaction_rate_of_change;
    }
    if (reaction->product_2 != NO_REAGENT) {
      rate_of_change_data[reaction->product_2] += reaction_rate_of_change;
    }
  }
  return 0;
}
