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
//      reaction - Pointer to the reaction to change
//      num_reagents - The number of reagents that can be involved in the
//                     reaction. Note that the actual number of reagents
//                     will be between 1 and num_reagents
//      max_rate_constant - The largest reaction rate that this reaction
//                          can have
//      min_rate_constant - The smallest reaction rate that this reaction
//                          can have. Note that the actual reaction is
//                          equally likely to be of any order of magnitude
//                          between min_rate_constant and max_reaction_rate
void SetRandomReaction(Reaction_Ptr reaction,
                       int num_reagents,
                       float max_rate_constant,
                       float min_rate_constant);

// Returns a Reaction with one random reactant and one random product (UniUni),
// and a randomly selected reaction rate
//
// Parameters:
//      reaction - Pointer to the reaction to change
//      num_reagents - The number of reagents that can be involved in the
//                     reaction. Note that the actual number of reagents
//                     will be between 1 and num_reagents
//      max_rate_constant - The largest reaction rate that this reaction
//                          can have
//      min_rate_constant - The smallest reaction rate that this reaction
//                          can have. Note that the actual reaction is
//                          equally likely to be of any order of magnitude
//                          between min_rate_constant and max_reaction_rate
void SetRandomUniUni(Reaction_Ptr reaction,
                     int num_reagents,
                     float max_rate_constant,
                     float min_rate_constant);

// Returns a Reaction with two random reactants and one random product (BiUni),
// and a randomly selected reaction rate
//
// Parameters:
//      reaction - Pointer to the reaction to change
//      num_reagents - The number of reagents that can be involved in the
//                     reaction. Note that the actual number of reagents
//                     will be between 1 and num_reagents
//      max_rate_constant - The largest reaction rate that this reaction
//                          can have
//      min_rate_constant - The smallest reaction rate that this reaction
//                          can have. Note that the actual reaction is
//                          equally likely to be of any order of magnitude
//                          between min_rate_constant and max_reaction_rate
void SetRandomBiUni(Reaction_Ptr reaction,
                    int num_reagents,
                    float max_rate_constant,
                    float min_rate_constant);

// Returns a Reaction with one random reactant and two random products (UniBi),
// and a randomly selected reaction rate
//
// Parameters:
//      reaction - Pointer to the reaction to change
//      num_reagents - The number of reagents that can be involved in the
//                     reaction. Note that the actual number of reagents
//                     will be between 1 and num_reagents
//      max_rate_constant - The largest reaction rate that this reaction
//                          can have
//      min_rate_constant - The smallest reaction rate that this reaction
//                          can have. Note that the actual reaction is
//                          equally likely to be of any order of magnitude
//                          between min_rate_constant and max_reaction_rate
void SetRandomUniBi(Reaction_Ptr reaction,
                    int num_reagents,
                    float max_rate_constant,
                    float min_rate_constant);

// Returns a Reaction with two random reactants and two random products (BiBi),
// and a randomly selected reaction rate
//
// Parameters:
//      reaction - Pointer to the reaction to change
//      num_reagents - The number of reagents that can be involved in the
//                     reaction. Note that the actual number of reagents
//                     will be between 1 and num_reagents
//      max_rate_constant - The largest reaction rate that this reaction
//                          can have
//      min_rate_constant - The smallest reaction rate that this reaction
//                          can have. Note that the actual reaction is
//                          equally likely to be of any order of magnitude
//                          between min_rate_constant and max_reaction_rate
void SetRandomBiBi(Reaction_Ptr reaction,
                   int num_reagents,
                   float max_rate_constant,
                   float min_rate_constant);

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
//      max_percent_change - The maximum magnitude percent change of
//                           the reaction
void MutateRateConstant(Reaction_Ptr reaction, float max_percent_change);
