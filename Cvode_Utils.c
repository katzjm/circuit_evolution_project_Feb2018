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

int SetUpCVodeInitial(CvodeData_Ptr cvode_data, UserData_Ptr user_data) {
  int flag;

  cvode_data->cvode_mem = CVodeCreate(CV_BDF, CV_NEWTON);
  if (cvode_data->cvode_mem == NULL) {
    printf("Failed to create CVode");
    return 1;
  }

  flag = CVodeInit(cvode_data->cvode_mem,
                   NetworkToOde, 0,
                   cvode_data->concentration_mem);
  if (flag != CV_SUCCESS) {
    printf("Failed to initialize CVode");
    return 1;
  }

  flag = CVodeSStolerances(cvode_data->cvode_mem,
                           RCONST(1.0e-6),
                           RCONST(1.0e-12));
  if (flag != CV_SUCCESS) {
    printf("Failed to set tolerances");
    return 1;
  }

  if (!user_data->config->show_cvode_errors) {
    flag = CVodeSetErrFile(cvode_data->cvode_mem, NULL);
    if (flag != CV_SUCCESS) {
      puts("Failed Setting Error File");
      return 1;
    }
  }

  flag = CVodeSetUserData(cvode_data->cvode_mem, user_data);
  if (flag != CV_SUCCESS) {
    puts("Failed data setting");
    return 1;
  }

  flag = CVDense(cvode_data->cvode_mem, user_data->config->num_species);
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
  Network_Ptr network = ((UserData_Ptr) user_data)->network;
  Config_Ptr c = ((UserData_Ptr) user_data)->config;

  realtype *rate_of_change_data = NV_DATA_S(rate_of_change);
  memset(rate_of_change_data, 0, sizeof(realtype) * c->num_species);

  for (int i = 0; i < network->num_reactions; i++) {
    Reaction_Ptr reaction = &network->reactions[i];
    realtype reaction_rate_of_change = GetRateOfChange(reaction,
                                                       concentrations);

    if (IsChanging(network, reaction->reactant_1)) {
      rate_of_change_data[reaction->reactant_1] -= reaction_rate_of_change;
    }
    if (IsChanging(network, reaction->reactant_2)) {
      rate_of_change_data[reaction->reactant_2] -= reaction_rate_of_change;
    }
    if (IsChanging(network, reaction->product_1)) {
      rate_of_change_data[reaction->product_1] += reaction_rate_of_change;
    }
    if (IsChanging(network, reaction->product_2)) {
      rate_of_change_data[reaction->product_2] += reaction_rate_of_change;
    }
  }
  return 0;
}
