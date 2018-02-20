/*
 * Implementation of the Reaction data structure and associated methods
 *
 * Author: Josh Katz
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>    // for rand
#include <assert.h>    // for assert
#include <math.h>      // for fmod

#include "Reaction.h"
#include "Configs.h"

void SetRandomReaction(Reaction_Ptr reaction, Config_Ptr config) {
  float reaction_type = (float) rand() / RAND_MAX;
  if ((reaction_type -= config->prob_uni_uni) <= 0) {
    SetRandomUniUni(reaction, config);
  } else if ((reaction_type -= config->prob_uni_bi) <= 0) {
    SetRandomUniBi(reaction, config);
  } else if ((reaction_type -= config->prob_bi_uni) <= 0) {
    SetRandomBiUni(reaction, config);
  } else {
    SetRandomBiBi(reaction, config);
  }
}

// Returns a rate constant according to user-defined parameters.
// See Config.h
static float GetRateConstant(Config_Ptr config) {
  return fmod(rand(), config->max_rate_constant);
}

// Returns a reagent according to user-defined parameters.
// See Config.h
static int GetReagent(Config_Ptr config) {
  return rand() % config->num_species;
}

void SetRandomUniUni(Reaction_Ptr reaction, Config_Ptr config) {
  reaction->reactant_1 = GetReagent(config);
  reaction->reactant_2 = NO_REAGENT;
  reaction->product_1 = GetReagent(config);
  reaction->product_2 = NO_REAGENT;
  reaction->rate_constant = GetRateConstant(config);
}

void SetRandomBiUni(Reaction_Ptr reaction, Config_Ptr config) {
  reaction->reactant_1 = GetReagent(config);
  reaction->reactant_2 = GetReagent(config);
  reaction->product_1 = GetReagent(config);
  reaction->product_2 = NO_REAGENT;
  reaction->rate_constant = GetRateConstant(config);
}

void SetRandomUniBi(Reaction_Ptr reaction, Config_Ptr config) {
  reaction->reactant_1 = GetReagent(config);
  reaction->reactant_2 = NO_REAGENT;
  reaction->product_1 = GetReagent(config);
  reaction->product_2 = GetReagent(config);
  reaction->rate_constant = GetRateConstant(config);
}

void SetRandomBiBi(Reaction_Ptr reaction, Config_Ptr config) {
  reaction->reactant_1 = GetReagent(config);
  reaction->reactant_2 = GetReagent(config);
  reaction->product_1 = GetReagent(config);
  reaction->product_2 = GetReagent(config);
  reaction->rate_constant = GetRateConstant(config);
}

void SetReaction(Reaction_Ptr reaction,
                 species_t reactant_1,
                 species_t reactant_2,
                 species_t product_1,
                 species_t product_2,
                 rate_t rate_constant) {
  assert(reactant_1 >= 0 && product_1 >= 0 && rate_constant >= 0);
  reaction->reactant_1 = reactant_1;
  reaction->reactant_2 = reactant_2;
  reaction->product_1 = product_1;
  reaction->product_2 = product_2;
  reaction->rate_constant = rate_constant;
}

void MutateRateConstant(Reaction_Ptr reaction, Config_Ptr config) {
  float percent_change = fmod(10 * (float) rand() / RAND_MAX,
                              config->max_percent_rate_change);
  int change_direction = rand() % 2 == 0 ? 1 : -1;
  reaction->rate_constant *= (1 + percent_change * change_direction);
}

bool IsUniUni(Reaction_Ptr reaction) {
  return reaction->reactant_2 == NO_REAGENT
         && reaction->product_2 == NO_REAGENT;
}

bool IsUniBi(Reaction_Ptr reaction) {
  return reaction->reactant_2 == NO_REAGENT
         && reaction->product_2 != NO_REAGENT;
}

bool IsBiUni(Reaction_Ptr reaction) {
  return reaction->reactant_2 != NO_REAGENT
         && reaction->product_2 == NO_REAGENT;
}

bool IsBiBi(Reaction_Ptr reaction) {
  return reaction->reactant_2 != NO_REAGENT
         && reaction->product_2 != NO_REAGENT;
}

void GetReactionString(Reaction_Ptr reaction,
                       char *return_buf,
                       bool fixed[],
                       int reaction_num) {
  char buf[32];
  char rate_constant_buf[32];
  if (fixed[0]) {
    sprintf(return_buf, "$S%d ", reaction->reactant_1);
  } else {
    sprintf(return_buf, "S%d ", reaction->reactant_1);
  }

  sprintf(rate_constant_buf, ";  k%d*S%d", reaction_num, reaction->reactant_1);

  if (IsBiUni(reaction) || IsBiBi(reaction)) {
    if (fixed[1]) {
      sprintf(buf, "+ $S%d ", reaction->reactant_2);
    } else {
      sprintf(buf, "+ S%d ", reaction->reactant_2);
    }
    strncat(return_buf, buf, 32);
    sprintf(buf, "*S%d", reaction->reactant_2);
    strncat(rate_constant_buf, buf, 32);
  }

  if (fixed[2]) {
    sprintf(buf, "-> $S%d", reaction->product_1);
  } else {
    sprintf(buf, "-> S%d", reaction->product_1);
  }
  
  strncat(return_buf, buf, 32);
  
  if (IsUniBi(reaction) || IsBiBi(reaction)) {
    if (fixed[3]) {
      sprintf(buf, " + $S%d", reaction->product_2);
    } else {
      sprintf(buf, " + S%d", reaction->product_2);
    }
    strncat(return_buf, buf, 32);
  }

  strncat(return_buf, rate_constant_buf, 32);
}

double GetRateOfChange(Reaction_Ptr reaction,
                       N_Vector concentrations) {
  realtype *concentration_data = NV_DATA_S(concentrations);
  double rate_of_change = reaction->rate_constant
                          * concentration_data[reaction->reactant_1];
  if (reaction->reactant_2 != NO_REAGENT) {
    rate_of_change *= concentration_data[reaction->reactant_2];
  }
  return rate_of_change;
}

