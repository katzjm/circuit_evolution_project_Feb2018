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

static Config defaults;

static void SetDefaultConfigs() {
  defaults.fit_threshold = 0.1;
  defaults.max_num_generations = 1000;
  defaults.max_num_reactions = 20;
  defaults.max_percent_rate_change = 0.1;
  defaults.max_pop_size = 100;
  defaults.max_rate_constant = 50;
  defaults.min_num_reactions = 2;
  defaults.num_data_pts = 10;
  defaults.num_species = 10;
  defaults.output_interval = 10;
  defaults.percent_to_clone = 0.5;
  defaults.prob_add_reaction = 0.25;
  defaults.prob_remove_reaction = 0.25;
  defaults.prob_rate_change = 0.5;
  defaults.prob_uni_uni = 0.25;
  defaults.prob_uni_bi = 0.25;
  defaults.prob_bi_uni = 0.25;
  defaults.prob_bi_bi = 0.25;
  defaults.seed = time(NULL);
  defaults.show_cvode_errors = false;
  defaults.time_based = false;
}

static int GetConfig(FILE *f, char *config_name, double *config_val) {
  char buf[128];
  if (fgets(buf, 128, f) == NULL) {
    printf("  Configuration file read\n");
    return 1;
  }
  if (sscanf(buf, "%s %lf", config_name, config_val) != 2) {
    printf("  file could not be read to completion\n");
    return 1;
  }
  return 0;
}

static void SetConfig(Config_Ptr c, char *config_name, double config_val) {
  if (config_val < 0) {
    printf("  Default value used for %s\n", config_name);
    return;
  }

  if (strcmp(config_name, "maxNumberOfGenerations") == 0) {
    c->max_num_generations = config_val;
  } else if (strcmp(config_name, "maxPopulationSize") == 0) {
    c->max_pop_size = config_val;
  } else if (strcmp(config_name, "probabilityOfUniUni") == 0) {
    c->prob_uni_uni = config_val;
  } else if (strcmp(config_name, "probabilityOfUniBi") == 0) {
    c->prob_uni_bi = config_val;
  } else if (strcmp(config_name, "probabilityOfBiUni") == 0) {
    c->prob_bi_uni = config_val;
  } else if (strcmp(config_name, "probabilityOfBiBi") == 0) {
    c->prob_bi_bi = config_val;
  } else if (strcmp(config_name, "percentageClone") == 0) {
    c->percent_to_clone = config_val;
  } else if (strcmp(config_name, "maxNumberOfSpecies") == 0) {
    c->num_species = config_val;
  } else if (strcmp(config_name, "maxNumberOfReactions") == 0) {
    c->max_num_reactions = config_val;
  } else if (strcmp(config_name, "minNumberOfReactions") == 0) {
    c->min_num_reactions = config_val;
  } else if (strcmp(config_name, "addReactionMutation") == 0) {
    c->prob_add_reaction = config_val;
  } else if (strcmp(config_name, "deleteReactionMutation") == 0) {
    c->prob_remove_reaction = config_val;
  } else if (strcmp(config_name, "rateConstantMutation") == 0) {
    c->prob_rate_change = config_val;
  } else if (strcmp(config_name, "intervalForOutput") == 0) {
    c->output_interval = config_val;
  } else if (strcmp(config_name, "fitnessThresholdToStop") == 0) {
    c->fit_threshold = config_val;
  } else if (strcmp(config_name, "seed") == 0) {
    c->seed = config_val;
  } else if (strcmp(config_name, "showCVodeErrors") == 0) {
    c->show_cvode_errors = config_val;
  } else if (strcmp(config_name, "numDataPoints") == 0) {
    c->num_data_pts = config_val;
  } else if (strcmp(config_name, "maxRateConstantPercentVariation") == 0) {
    c->max_percent_rate_change = config_val;
  } else if (strcmp(config_name, "timeBased") == 0) {
    c->time_based = config_val;
  } else if (strcmp(config_name, "maxInitialRateConstant") == 0) {
    c->max_rate_constant = config_val;
  }
}

static void ValidateConfigs(Config_Ptr c) {
  double max_err = 1e-10;
  if (fabs(c->prob_uni_uni + c->prob_uni_bi + c->prob_bi_uni
           + c->prob_bi_bi - 1) > max_err) {
    printf("  Defauts used for reaction type probabilites\n");
    c->prob_uni_uni = defaults.prob_uni_uni;
    c->prob_uni_bi = defaults.prob_uni_bi;
    c->prob_bi_uni = defaults.prob_bi_uni;
    c->prob_bi_bi = defaults.prob_bi_bi;
  }

  if (c->percent_to_clone > 1) {
    printf("  Default used for percentageClone\n");
    c->percent_to_clone = defaults.percent_to_clone;
  }

  if (fabs(c->prob_add_reaction + c->prob_remove_reaction + c->prob_rate_change
           - 1) > max_err) {
    printf("  Defaults used for mutation probabilites\n");
    c->prob_add_reaction = defaults.prob_add_reaction;
    c->prob_remove_reaction = defaults.prob_remove_reaction;
    c->prob_rate_change = defaults.prob_rate_change;
  }

  if (c->max_num_reactions < c->min_num_reactions) {
    printf("  Defaults used for the range of reactions per network\n");
    c->max_num_reactions = defaults.max_num_reactions;
    c->min_num_reactions = defaults.min_num_reactions;
  }
}

void Configure(Config_Ptr c, const char *file_name) {
  SetDefaultConfigs();
  *c = defaults;

  printf("Attempting to configure evolver...\n");

  FILE *f;
  if (file_name != NULL) {
    f = fopen(file_name, "r");
  } else {
    printf("  Using all defaults\nConfiguration successful\n");
    srand(c->seed);
    return;
  }
  if (f == NULL) {
    printf("  %s could not be found. Using all defaults\n",
           file_name == NULL ? "setup.txt" : file_name);
    printf("Configuration successful\n");
    srand(c->seed);
    return;
  }

  char config_name[128];
  double config_val;
  while (GetConfig(f, config_name, &config_val) == 0) {
    SetConfig(c, config_name, config_val);
  }
  ValidateConfigs(c);

  srand(c->seed);

  fclose(f);
  printf("Configuration successful\n");
}
