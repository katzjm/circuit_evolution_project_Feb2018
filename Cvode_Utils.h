/*
 * Helper methods for using the CVode ode solver
 *
 * Author: Josh Katz
 */

#ifndef _EVOLVER_CVODE_UTILS_H_
#define _EVOLVER_CVODE_UTILS_H_

#include "nvector/nvector_serial.h"

#include "Configs.h"
#include "Network.h"

typedef struct cvode_data_str {
  void *cvode_mem;
  N_Vector concentration_mem;
} CvodeData, *CvodeData_Ptr;

typedef struct user_data_str {
  Network_Ptr network;
  Config_Ptr config;
} UserData, *UserData_Ptr;

void SetUpCvodeFirstRun(CvodeData_Ptr cvode_data,
                       UserData_Ptr user_data);

int NetworkToOde(realtype t,
                 N_Vector species_concentrations,
                 N_Vector species_rate_of_change,
                 void *user_data);

void SetUpCvodeNextRun(CvodeData_Ptr cvode_data);

bool RunCvode(CvodeData_Ptr cvode_data, realtype tout, realtype *t);

#endif  // _EVOLVER_CVODE_UTILS_H_
