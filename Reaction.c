/*
 * Implementation of the Reaction data structure and associated methods
 *
 * Author: Josh Katz
 */

#include <stdlib.h>
#include <assert.h>
#include "Reaction.h"
#include "Configs.h"

void SetRandomReaction(Reaction_Ptr reaction, RConfig_Ptr config) {
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
static float GetRateConstant(RConfig_Ptr config) {
    
}

void SetRandomUniUni(Reaction_Ptr reaction, RConfig_Ptr config) {
    reaction->reactant_1 = rand() % config->num_reagents;
    reaction->reactant_2 = NO_REAGENT;
    reaction->product_1 = rand() % config->num_reagents;
    reaction->product_2 = NO_REAGENT;
}

void SetRandomBiUni(Reaction_Ptr reaction, RConfig_Ptr config) {
    reaction->reactant_1 = rand() % config->num_reagents;
    reaction->reactant_2 = rand() % config->num_reagents;
    reaction->product_1 = rand() % config->num_reagents;
    reaction->product_2 = NO_REAGENT;
}

void SetRandomUniBi(Reaction_Ptr reaction, RConfig_Ptr config) {
    reaction->reactant_1 = rand() % config->num_reagents;
    reaction->reactant_2 = NO_REAGENT;
    reaction->product_1 = rand() % config->num_reagents;
    reaction->product_2 = rand() % config->num_reagents;
}

void SetRandomBiBi(Reaction_Ptr reaction, RConfig_Ptr config) {
    reaction->reactant_1 = rand() % config->num_reagents;
    reaction->reactant_2 = rand() % config->num_reagents;
    reaction->product_1 = rand() % config->num_reagents;
    reaction->product_2 = rand() % config->num_reagents;
}

void SetReaction(Reaction_Ptr reaction,
                 int reactant_1,
                 int reactant_2,
                 int product_1,
                 int product_2,
                 float rate_constant) {
    assert(reactant_1 >= 0 && product_1 >= 0 && rate_constant >= 0);
    reaction->reactant_1 = reactant_1;
    reaction->reactant_2 = reactant_2;
    reaction->product_1 = product_1;
    reaction->product_2 = product_2;
    reaction->rate_constant = rate_constant;
}

// Change the rate constant of a given reaction by at most a user provided
// amount. The change could either decrease or increase the reaction rate
//
// Parameters:
//      reaction - A pointer to the reaction to modify
//      config - Pointer to a struct containting configuration parameters.
//               See Config.h
void MutateRateConstant(Reaction_Ptr reaction, RConfig_Ptr config);

