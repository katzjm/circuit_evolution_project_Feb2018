/*
 * Implements the basic method for configuring the evolution program
 *
 * Author: Josh Katz
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Configs.h"

static int GetConfig(FILE *f, char *config_name, double *config_val) {
    char buf[128];
    if (fgets(buf, 128, f) == NULL) {
        return 1;   
    }
    if (sscanf(buf, "%s %lf", config_name, config_val) != 2) {
        return 1;
    }
    return 0;
}

static void SetConfig(Config_Ptr c, char *config_name, double config_val) {
    if (config_val < 0) {
        printf("Default value used for %s\n", config_name);   
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
    }
}

static void ValidateConfigs(Config_Ptr c) {
    double max_err = 1e10;
    if (fabs(c->prob_uni_uni + c->prob_uni_bi + c->prob_bi_uni + c->prob_bi_bi - 1) > max_err) {
        printf("Defauts used for reaction type probabilites\n");
    } else if (c->percent_to_clone > 1) {
        printf("Default used for percentageClone");
    } else if (c->prob_add_reaction + c->prob_remove_reaction + c->prob_rate_change)

}

int Configure(Config_Ptr c) {
    FILE *f = fopen("setup.txt", "r");
    if (f == NULL) {
        perror("setup.txt could not be found");
        return 1;
    }
    
    char config_name[128];
    double config_val;
    while (GetConfig(f, config_name, &config_val) == 0) {
        SetConfig(c, config_name, config_val);
    }
    
    fclose(f);
    return 0;
}
