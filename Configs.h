/*
 * Describes helper structs and methods used to configure Networks, Reactions
 * and the program in general
 *
 * Author: Josh Katz
 */

#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <stdbool.h>

typedef struct config_str {
  double inputs;
  double outputs;
  double max_rate_constant;
  double max_percent_rate_change;
  double prob_uni_uni;
  double prob_uni_bi;
  double prob_bi_uni;
  double prob_bi_bi;
  double prob_add_reaction;
  double prob_remove_reaction;
  double prob_rate_change;
  double percent_to_clone;
  double fit_threshold;
  double initial_concentrations;

  int seed;
  int max_num_generations;
  int max_pop_size;
  int num_species;
  int max_num_reactions;
  int min_num_reactions;
  int output_interval;
  int num_data_pts;

  bool function_based;
  bool show_cvode_errors;
  bool time_based;
} Config, *Config_Ptr;


void Configure(Config_Ptr c, const char *file_name);

#endif // _CONFIG_H_
