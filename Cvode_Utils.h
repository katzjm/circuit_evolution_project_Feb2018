/*
 * Helper methods for using the CVode ode solver
 *
 * Author: Josh Katz
 */

#include "nvector/nvector_serial.h"

int SetUpCVodeInitial(void **cvode_mem, N_Vector *se);

int NetworkToOde(realtype t,
                 N_Vector species_concentrations,
                 N_Vector species_rate_of_change,
                 void *user_data);
