/*
 * Helper methods for using the CVode ode solver
 *
 * Author: Josh Katz
 */

#include "nvector/nvector_serial.h"

#include "Configs.h"
#include "Network.h"

typedef struct user_data_str {
  Network_Ptr network;
  Config_Ptr config;
} Data, *Data_Ptr;


int SetUpCVodeInitial(void **cvode_mem,
                      N_Vector se, //TODO rename
                      Data_Ptr data);

int NetworkToOde(realtype t,
                 N_Vector species_concentrations,
                 N_Vector species_rate_of_change,
                 void *user_data);
