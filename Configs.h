/*
 * Describes helper structs and methods used to configure Networks, Reactions
 * and the program in general
 *
 * Author: Josh Katz
 */

typedef struct reaction_config_str {
    int num_reagents;
    float max_rate_constant;
    float min_rate_constant;
    float max_percent_rate_change;
} RConfig, *RConfig_Ptr;

typedef struct network_config_str {

} NConfig, *NConfig_Ptr;

typedef struct program_config_str {

} PConfig, *PConfig_Ptr;
