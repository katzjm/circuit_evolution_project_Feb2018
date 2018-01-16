/*
 * Implements basic helper methods for using Cvode
 *
 * Author: Josh Katz
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cvode/cvode.h"
#include "cvode/cvode_dense.h"
#include "nvector/nvector_serial.h"

#include "Cvode_Utils.h"
#include "Configs.h"
#include "Network.h"
#include "Reaction.h"

static void CheckSuccess(int flag, const char *error_message) {
  if (flag != CV_SUCCESS) {
    printf("%s", error_message);
    exit(EXIT_FAILURE);
  }
}

void SetUpCVodeFirstRun(CvodeData_Ptr cvode_data, UserData_Ptr user_data) {
  int flag;

  cvode_data->cvode_mem = CVodeCreate(CV_BDF, CV_NEWTON);
  if (cvode_data->cvode_mem == NULL) {
    printf("Failed to create CVode");
    exit(EXIT_FAILURE);
  }

  flag = CVodeInit(cvode_data->cvode_mem,
                   GetSpeciesRateOfChange, 0,
                   cvode_data->concentration_mem);
  CheckSuccess(flag, "Failed to initialize CVode");

  flag = CVodeSStolerances(cvode_data->cvode_mem,
                           RCONST(1.0e-6),
                           RCONST(1.0e-12));
  CheckSuccess(flag, "Failed to set tolerances");

  if (!user_data->config->show_cvode_errors) {
    flag = CVodeSetErrFile(cvode_data->cvode_mem, NULL);
    CheckSuccess(flag, "Failed Setting Error File");
  }

  flag = CVodeSetUserData(cvode_data->cvode_mem, user_data);
  CheckSuccess(flag, "Failed data setting");

  flag = CVDense(cvode_data->cvode_mem, user_data->config->num_species);
  CheckSuccess(flag, "Failed CVDense Initialization");
}

int GetSpeciesRateOfChange(realtype t,
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
    if (IsChanging(network, reaction->reactant_2) &&
        reaction->reactant_1 != reaction->reactant_2) {
      rate_of_change_data[reaction->reactant_2] -= reaction_rate_of_change;
    }
    if (IsChanging(network, reaction->product_1)) {
      rate_of_change_data[reaction->product_1] += reaction_rate_of_change;
    }
    if (IsChanging(network, reaction->product_2) &&
        reaction->product_1 != reaction->product_2) {
      rate_of_change_data[reaction->product_2] += reaction_rate_of_change;
    }
  }
  return 0;
}

void SetUpCvodeNextRun(CvodeData_Ptr cvode_data) {
  int flag = CVodeReInit(cvode_data->cvode_mem, 0,
                         cvode_data->concentration_mem);
  CheckSuccess(flag, "Failed to Reinitialize CVode");
}

bool RunCvode(CvodeData_Ptr cvode_data, realtype tout, realtype *t) {
  return CVode(cvode_data->cvode_mem, tout,
               cvode_data->concentration_mem, t, CV_NORMAL) == CV_SUCCESS;
}
