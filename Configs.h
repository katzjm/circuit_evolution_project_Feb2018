/*
 * Describes helper structs and methods used to configure Networks, Reactions
 * and the program in general
 *
 * Author: Josh Katz
 */

#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <stdbool.h>

enum FitType {
  CUSTOM,
  SQUARE_ROOT,
  CUBE_ROOT,
  OSCILLATOR,
  TRANSISTOR
};

typedef struct config_str {
  /* Evaluation Parameters */
  double *inputs;
  double *outputs;
  int num_data_pts;
  enum FitType function_type;
  bool time_based;

  /* Reaction Creation Parameters */
  double max_rate_constant;
  double prob_uni_uni;
  double prob_uni_bi;
  double prob_bi_uni;
  double prob_bi_bi;

  /* Network Creation Parameters */
  double initial_concentrations;
  int max_num_reactions;
  int min_num_reactions;
  int num_species;

  /* Network Mutation Parameters */
  double max_percent_rate_change;
  double prob_add_reaction;
  double prob_remove_reaction;
  double prob_rate_change;

  /* Population Creation Parameter */
  int max_pop_size;

  /* Population Generation Paremters */
  double fit_threshold;
  int max_num_generations;

  /* Output Parameters */
  int output_interval;
  bool show_cvode_errors;

  /* Random Number Generator Seed */
  int seed;

} Config, *Config_Ptr;


void Configure(Config_Ptr c, const char *file_name);

#endif // _CONFIG_H_
