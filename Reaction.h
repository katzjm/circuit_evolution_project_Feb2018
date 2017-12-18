/*
 * A Reaction is used to convert one or two reactants into one or two products
 *
 * Author: Josh Katz
 */

#define NO_REAGENT -1

typedef struct reaction_str {
    int reactant_1;
    int reactant_2;
    int product_1;
    int product_2;
    float rate_constant;
} Reaction, *Reaction_Ptr;

// Returns a Reaction with either one or two reactants and either one or
// two products, and a randomly selected reaction rate
//
// Parameters:
//      num_reagents - The number of reagents that can be involved in the
//                     reaction. Note that the actual number of reagents
//                     will be between 1 and num_reagents
//      max_reaction_rate - The largest reaction rate that this reaction
//                          can have
//      min_reaction_rate - The smallest reaction rate that this reaction
//                          can have. Note that the actual reaction is
//                          equally likely to be of any order of magnitude
//                          between min_reaction_rate and max_reaction_rate
//
// Returns:
//      A Reaction with reagents ranging from 0 to num_reagents - 1 and
//      a reaction rate between min_reaction_rate and max_reaction_rate
Reaction GetRandomReaction(int num_reagents,
                           float max_reaction_rate,
                           float min_reaction_rate);

// Returns a Reaction with one random reactant and one random product (UniUni),
// and a randomly selected reaction rate
//
// Parameters:
//      num_reagents - The number of reagents that can be involved in the
//                     reaction. Note that the actual number of reagents
//                     will be between 1 and num_reagents
//      max_reaction_rate - The largest reaction rate that this reaction
//                          can have
//      min_reaction_rate - The smallest reaction rate that this reaction
//                          can have. Note that the actual reaction is
//                          equally likely to be of any order of magnitude
//                          between min_reaction_rate and max_reaction_rate
//
// Returns:
//      A UniUni Reaction with reagents ranging from 0 to num_reagents - 1 and
//      a reaction rate between min_reaction_rate and max_reaction_rate
Reaction GetRandomUniUni(int num_reagents,
                         float max_reaction_rate,
                         float min_reaction_rate);

// Returns a Reaction with two random reactants and one random product (BiUni),
// and a randomly selected reaction rate
//
// Parameters:
//      num_reagents - The number of reagents that can be involved in the
//                     reaction. Note that the actual number of reagents
//                     will be between 1 and num_reagents
//      max_reaction_rate - The largest reaction rate that this reaction
//                          can have
//      min_reaction_rate - The smallest reaction rate that this reaction
//                          can have. Note that the actual reaction is
//                          equally likely to be of any order of magnitude
//                          between min_reaction_rate and max_reaction_rate
//
// Returns:
//      A BiUni Reaction with reagents ranging from 0 to num_reagents - 1 and
//      a reaction rate between min_reaction_rate and max_reaction_rate
Reaction GetRandomBiUni(int num_reagents,
                        float max_reaction_rate,
                        float min_reaction_rate);

// Returns a Reaction with one random reactant and two random products (UniBi),
// and a randomly selected reaction rate
//
// Parameters:
//      num_reagents - The number of reagents that can be involved in the
//                     reaction. Note that the actual number of reagents
//                     will be between 1 and num_reagents
//      max_reaction_rate - The largest reaction rate that this reaction
//                          can have
//      min_reaction_rate - The smallest reaction rate that this reaction
//                          can have. Note that the actual reaction is
//                          equally likely to be of any order of magnitude
//                          between min_reaction_rate and max_reaction_rate
//
// Returns:
//      A UniBi Reaction with reagents ranging from 0 to num_reagents - 1 and
//      a reaction rate between min_reaction_rate and max_reaction_rate
Reaction GetRandomUniBi(int num_reagents,
                        float max_reaction_rate,
                        float min_reaction_rate);

// Returns a Reaction with two random reactants and two random products (BiBi),
// and a randomly selected reaction rate
//
// Parameters:
//      num_reagents - The number of reagents that can be involved in the
//                     reaction. Note that the actual number of reagents
//                     will be between 1 and num_reagents
//      max_reaction_rate - The largest reaction rate that this reaction
//                          can have
//      min_reaction_rate - The smallest reaction rate that this reaction
//                          can have. Note that the actual reaction is
//                          equally likely to be of any order of magnitude
//                          between min_reaction_rate and max_reaction_rate
//
// Returns:
//      A BiBi Reaction with reagents ranging from 0 to num_reagents - 1 and
//      a reaction rate between min_reaction_rate and max_reaction_rate
Reaction GetRandomBiBi(int num_reagents,
                       float max_reaction_rate,
                       float min_reaction_rate);

// Returns a Reaction with given reactants, products, and reaction rate
//
// Note that reactions must not have NO_REAGENT as either their reactant_1
// or reactant_2, and reaction_rate > 0 must be true
//
// Parameters:
//      reactant_1 - A reactant in the returned Reaction
//      reactant_2 - Another reactant in the returned Reaction
//      product_1 - A product in the returned Reaction
//      product_2 - Another product in the returned Reaction
//      reaction_rate - The reaction rate in the returned Reaction
//
// Returns a Reaction with the given reactants, products and rate,
// or NULL if the given parameters result in an invalid Reaction
Reaction GetReaction(int reactant_1,
                     int reactant_2,
                     int product_1,
                     int product_2,
                     float reaction_rate);

// Change the rate constant of a given reaction by at most a user provided
// amount. The change could either decrease or increase the reaction rate
//
// Parameters:
//      reaction - A pointer to the reaction to modify
//      max_percent_change - The maximum magnitude percent change of
//                           the reaction
//
// Returns:
//      0 on success, 1 otherwise
int MutateRateConstant(Reaction_Ptr reaction, float max_percent_change);
