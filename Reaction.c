/*
 * Implementation of the Reaction data structure and associated methods
 *
 * Author: Josh Katz
 */

#include <stdlib.h>

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

// Returns a Reaction with one random reactant and one random product (UniUni),
// and a randomly selected reaction rate
//
// Parameters:
//      reaction - Pointer to the reaction to change
//      config - Pointer to a struct containting configuration parameters.
//               See Config.h
void SetRandomUniUni(Reaction_Ptr reaction, RConfig_Ptr config) {
    
}

// Returns a Reaction with two random reactants and one random product (BiUni),
// and a randomly selected reaction rate
//
// Parameters:
//      reaction - Pointer to the reaction to change
//      config - Pointer to a struct containting configuration parameters.
//               See Config.h
void SetRandomBiUni(Reaction_Ptr reaction, RConfig_Ptr config;

// Returns a Reaction with one random reactant and two random products (UniBi),
// and a randomly selected reaction rate
//
// Parameters:
//      reaction - Pointer to the reaction to change
//      config - Pointer to a struct containting configuration parameters.
//               See Config.h
void SetRandomUniBi(Reaction_Ptr reaction, RConfig_Ptr config);

// Returns a Reaction with two random reactants and two random products (BiBi),
// and a randomly selected reaction rate
//
// Parameters:
//      reaction - Pointer to the reaction to change
//      config - Pointer to a struct containting configuration parameters.
//               See Config.h
void SetRandomBiBi(Reaction_Ptr reaction, RConfig_Ptr config);

// Returns a Reaction with given reactants, products, and reaction rate
//
// Note that reactions must not have NO_REAGENT as either their reactant_1
// or reactant_2, and rate_constant > 0 must be true
//
// Parameters:
//      reaction - Pointer to the reaction to change
//      reactant_1 - A reactant in the returned Reaction
//      reactant_2 - Another reactant in the returned Reaction
//      product_1 - A product in the returned Reaction
//      product_2 - Another product in the returned Reaction
//      rate_constant - The reaction rate in the returned Reaction
void SetReaction(Reaction_Ptr reaction,
                 int reactant_1,
                 int reactant_2,
                 int product_1,
                 int product_2,
                 float rate_constant);

// Change the rate constant of a given reaction by at most a user provided
// amount. The change could either decrease or increase the reaction rate
//
// Parameters:
//      reaction - A pointer to the reaction to modify
//      config - Pointer to a struct containting configuration parameters.
//               See Config.h
void MutateRateConstant(Reaction_Ptr reaction, RConfig_Ptr config);

