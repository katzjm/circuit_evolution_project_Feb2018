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
  SQUARE,
  CUBE,
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
  char test_file[64];

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
  double percentage_clone;
  int max_num_generations;

  /* Output Parameters */
  int output_interval;
  bool show_cvode_errors;

  /* Random Number Generator Seed */
  int seed;

} Config, *Config_Ptr;

/* Configure the given Config struct using parameters from the given
 * file. If there is an error reading from the file, quits the program.
 * If the parameters do not make sense (i.e. the sum of the probabilites of
 * mutating a given network do not sum to 1), quits the program
 * 
 * Parameters:
 *      c - The configuration struct that gets filled with parameters
 *      file_name - The name of the file contianing parameters for running
 *                  evolver
 */
void Configure(Config_Ptr c, const char *file_name);

#endif // _CONFIG_H_
