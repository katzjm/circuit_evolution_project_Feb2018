/* 
 * Module for executing the program
 *
 * Author: Josh Katz
 */

#include <stdlib.h>
#include <stdio.h>

#include "Configs.h"
#include "Population.h"

void Usage() {
  printf("./evolver\n");
  printf("./evolver configuration_file_name\n");
  printf("Evolves a set of reactions to fit data or a function.\n");
  printf("A file listing configuration parameters or data can be provided\n");
  printf("otherwise a default run is executed\n");
  exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
  if (argc > 2) {
    Usage();
  }

  Config c;
  if (argc == 1) {
    Configure(&c, NULL);
  } else {
    Configure(&c, argv[1]);
  }
  
  Population pop;
  SetFirstGeneration(&pop, &c);
  for (int i = 0; i < c.max_num_generations; i++) {
    if (BestFitness(&pop) > c.fit_threshold) {
      break;
    }

    EvaluateGeneration(&pop, &c);

    if (i % c.output_interval == 0) {
      PrintSmallStatus(&pop);
    }

    SetNextGeneration(&pop);
  }

  PrintLargeStatus(&pop);
  KillPopulation(&pop);
  return EXIT_SUCCESS;
}
