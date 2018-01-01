/*
 * Implements basic helper methods for using Cvode
 *
 * Author: Josh Katz
 */

#include "stdio.h"

#include "cvode/cvode.h"

#include "Cvode_Utils.h"

int SetUpCVodeInitial(void **cvode_mem, N_Vector *se) {
  int flag;

  *cvode_mem = CVodeCreate(CV_BDF, CV_NEWTON);
  if (*cvode_mem == NULL) {
    printf("Failed to Create CVode");
    return 1;
  }

  flag = CVodeInit(

}

int NetworkToOde(realtype t,
                 N_Vector species_concentrations,
                 N_Vector species_rate_of_change,
                 void *user_data) {

}
