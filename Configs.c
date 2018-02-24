/*
* Implements the basic method for configuring the evolution program
*
* Author: Josh Katz
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "Configs.h"

/* Sets the inputs and outputs that the networks will be evaluated with
 *
 * Parameters:
 *      c - The struct to fill
 */
static void SetTestData(Config_Ptr c) {
  c->inputs = (double *) malloc(sizeof(double) * c->num_data_pts);
  c->outputs = (double *) malloc(sizeof(double) * c->num_data_pts);
  
  switch (c->function_type) {
    case SQUARE: 
      {
        for (int i = 0; i < c->num_data_pts; i++) {
          c->inputs[i] = i;
          c->outputs[i] = i * i;
        }
        break; 
      }
    case CUBE:
      {
        for (int i = 0; i < c->num_data_pts; i++) {
          c->inputs[i] = i;
          c->outputs[i] = i * i * i;
        }
        break;
      }
    case SQUARE_ROOT:
      {
        for (int i = 0; i < c->num_data_pts; i++) {
          c->inputs[i] = i * i;
          c->outputs[i] = i;
        }
        break;
      }
    case CUBE_ROOT:
      {
        for (int i = 0; i < c->num_data_pts; i++) {
          c->inputs[i] = i * i * i;
          c->outputs[i] = i;
        }
        break;
      }
    case OSCILLATOR:
      {
        for (int i = 0; i < c->num_data_pts; i++) {
          c->inputs[i] = i * 5;
          c->outputs[i] = c->initial_concentrations + ((i + 1) * 5) % 15 - 5;
        }
        break;
      }
    case TRANSISTOR: // TODO
      break;
    case CUSTOM: 
      {
        FILE *test_file = fopen(c->test_file, "r");
        char buf[128];
        for (int i = 0; i < c->num_data_pts; i++) {
          fgets(buf, 128, test_file);
          sscanf(buf, "%lf %lf", &c->inputs[i], &c->outputs[i]);
        }
        fclose(test_file);
        break;
      }
  }
}

/* Reads a parameter and its value from a single line of a given file. Advances
 * the cursor of the file by one line
 *
 * Parameters:
 *      f - Pointer to the file parameters are read from
 *      config_name - Return parameter. Contains the parameter's name as per
 *                    the first token of the current line of the file
 *      config_val - Return parameter. Contains the parameter's value as per
 *                    the second token of the current line of the file
 *
 * Returns:
 *      1 if the file has either been fully read or there was a format error
 *      0 otherwise
 */
static int GetConfig(FILE *f, char *config_name, char  *config_val) {
  char buf[128];
  if (fgets(buf, 128, f) == NULL) {
    printf("  Configuration file read\n");
    return 1;
  }
  if (sscanf(buf, "%s %s", config_name, config_val) != 2) {
    printf("  file could not be read to completion\n");
    return 1;
  }
  return 0;
}

/* Sets a parameter and its value into the configuration struct c
 *
 * Parameters:
 *      c - Struct containing evolver parameters
 *      config_name - The parameter's name
 *      config_val - The parameter's value
 */
static void SetConfig(Config_Ptr c, char *config_name, char *config_val) {
  double config_val_numerical;

  /* Evaluation Parameters */
  if (strcmp(config_name, "testPtFile") == 0) {
    strcpy(c->test_file, config_val);
  } else {
    sscanf(config_val, "%lf", &config_val_numerical);
  }

  if (strcmp(config_name, "numDataPoints") == 0) {
    c->num_data_pts = config_val_numerical;
  } else if (strcmp(config_name, "timeBased") == 0) {
    c->time_based = config_val_numerical;
  } else if (strcmp(config_name, "fitType") == 0) {
    c->function_type = config_val_numerical;
  }

  /* Reaction Creation Parameters */
  if (strcmp(config_name, "maxInitialRateConstant") == 0) {
    c->max_rate_constant = config_val_numerical;
  } else if (strcmp(config_name, "probabilityOfUniUni") == 0) {
    c->prob_uni_uni = config_val_numerical;
  } else if (strcmp(config_name, "probabilityOfUniBi") == 0) {
    c->prob_uni_bi = config_val_numerical;
  } else if (strcmp(config_name, "probabilityOfBiUni") == 0) {
    c->prob_bi_uni = config_val_numerical;
  } else if (strcmp(config_name, "probabilityOfBiBi") == 0) {
    c->prob_bi_bi = config_val_numerical;
  }

  /* Network Creation Parameters */
  if (strcmp(config_name, "initialConcentrations") == 0) {
    c->initial_concentrations = config_val_numerical;
  } else if (strcmp(config_name, "maxNumberOfSpecies") == 0) {
    c->num_species = config_val_numerical;
  } else if (strcmp(config_name, "maxNumberOfReactions") == 0) {
    c->max_num_reactions = config_val_numerical;
  } else if (strcmp(config_name, "minNumberOfReactions") == 0) {
    c->min_num_reactions = config_val_numerical;
  }
  
  /* Network Mutation Parameters */
  if (strcmp(config_name, "addReactionMutation") == 0) {
    c->prob_add_reaction = config_val_numerical;
  } else if (strcmp(config_name, "deleteReactionMutation") == 0) {
    c->prob_remove_reaction = config_val_numerical;
  } else if (strcmp(config_name, "rateConstantMutation") == 0) {
    c->prob_rate_change = config_val_numerical;
  } else if (strcmp(config_name, "maxRateConstantPercentVariation") == 0) {
    c->max_percent_rate_change = config_val_numerical;
  }
  
  /* Population Creation Parameter */
  if (strcmp(config_name, "maxPopulationSize") == 0) {
    c->max_pop_size = config_val_numerical;
  }

  /* Population Generation Paremters */
  if (strcmp(config_name, "maxNumberOfGenerations") == 0) {
    c->max_num_generations = config_val_numerical;
  } else if (strcmp(config_name, "fitnessThresholdToStop") == 0) {
    c->fit_threshold = config_val_numerical;
  } else if(strcmp(config_name, "percentageClone") == 0) {
    c->percentage_clone = config_val_numerical;
  }

  /* Output Parameters */
  if (strcmp(config_name, "intervalForOutput") == 0) {
    c->output_interval = config_val_numerical;
  } else if (strcmp(config_name, "showCVodeErrors") == 0) {
    c->show_cvode_errors = config_val_numerical;
  } 

  /* Random Number Generator Seed */
  if (strcmp(config_name, "seed") == 0) {
    c->seed = config_val_numerical;
  }
}

/* Does some basic validation of the given evolving parameters
 *
 * Parameters:
 *      c - Struct containing evolver parameters
 */
static void ValidateConfigs(Config_Ptr c) {
  double max_err = 1e-10;

  // Check the reaction generation probabilities sum to 1
  if (fabs(c->prob_uni_uni + c->prob_uni_bi + c->prob_bi_uni
           + c->prob_bi_bi - 1) > max_err) {
    printf("Reaction generation probabilities do not sum to 1");
    exit(EXIT_FAILURE);
  }

  // Check network mutation probabilities sum to 1
  if (fabs(c->prob_add_reaction + c->prob_remove_reaction + c->prob_rate_change
           - 1) > max_err) {
    printf("Reaction mutation probabilities do not sum to 1");
    exit(EXIT_FAILURE);
  }

  // Check that the minimum number reactions is at most equal to the maximum
  // number of reactions
  if (c->max_num_reactions < c->min_num_reactions) {
    printf("Max reactions must be greater than or equal to min reactions");
    exit(EXIT_FAILURE);
  }
}

/* Opens the given file
 *
 * Parameters:
 *      file_name - the file to be opened
 * 
 * Returns:
 *      A pointer to the given file if successful, NULL otherwise
 */
static FILE* OpenConfigurationFile(const char *file_name) {
  FILE *f;
  if (file_name != NULL) {
    f = fopen(file_name, "r");
  } else {
    f = fopen("setup.txt", "r");
  }
  if (f == NULL) {
    printf("  %s could not be found\n",
           file_name == NULL ? "setup.txt" : file_name);
    return NULL;
  }
  return f;
}

void Configure(Config_Ptr c, const char *file_name) {
  printf("Attempting to configure evolver...\n");

  FILE *f;
  if ((f = OpenConfigurationFile(file_name)) == NULL) {
    exit(EXIT_FAILURE);    
  }

  char config_name[128];
  char config_val[64];
  while (GetConfig(f, config_name, config_val) == 0) {
    SetConfig(c, config_name, config_val);
  }
  ValidateConfigs(c);
  SetTestData(c);

  srand(c->seed);
  fclose(f);
  printf("Configuration successful\n");
}
