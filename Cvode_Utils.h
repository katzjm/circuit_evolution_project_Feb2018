/*
 * Helper methods for using the CVode ode solver
 *
 * Author: Josh Katz
 */

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

int SetUpCVodeInitial(void **cvode_mem,
                      N_Vector species_concentrations,
                      UserData_Ptr data);

int NetworkToOde(realtype t,
                 N_Vector species_concentrations,
                 N_Vector species_rate_of_change,
                 void *user_data);
