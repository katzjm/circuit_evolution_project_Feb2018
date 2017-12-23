/*
 * Describes helper structs and methods used to configure Networks, Reactions
 * and the program in general
 *
 * Author: Josh Katz
 */

#ifndef _CONFIG_H_
#define _CONFIG_H_

typedef struct config_str {
    int num_reagents;
    float max_rate_constant;
    float max_percent_rate_change;
    float prob_uni_uni;
    float prob_uni_bi;
    float prob_bi_uni;
    float prob_bi_bi;
    int max_num_reactions;
    int min_num_reactions;
    float prob_add_reaction;
    float prob_remove_reaction;
    float prob_rate_change;
} Config, *Config_Ptr;
#endif // _CONFIG_H_
