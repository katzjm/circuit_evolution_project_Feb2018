/*
 * A Reaction is used to convert one or two reactants into one or two products
 *
 * Author: Josh Katz
 */

#ifndef _REACTION_H_
#define _REACTION_H_

#include "nvector/nvector_serial.h"

#include "Configs.h"

#define NO_REAGENT -1

typedef int species_t;
typedef float rate_t;

typedef struct reaction_str {
  species_t reactant_1;
  species_t reactant_2;
  species_t product_1;
  species_t product_2;
  rate_t rate_constant;
} Reaction, *Reaction_Ptr;

// Returns a Reaction with either one or two reactants and either one or
// two products, and a randomly selected reaction rate
//
// Parameters:
//      reaction - Pointer to the reaction to change
//      config - Pointer to a struct containting configuration parameters.
//               See Config.h
void SetRandomReaction(Reaction_Ptr reaction, Config_Ptr config);

// Returns a Reaction with one random reactant and one random product (UniUni),
// and a randomly selected reaction rate
//
// Parameters:
//      reaction - Pointer to the reaction to change
//      config - Pointer to a struct containting configuration parameters.
//               See Config.h
void SetRandomUniUni(Reaction_Ptr reaction, Config_Ptr config);

// Returns a Reaction with two random reactants and one random product (BiUni),
// and a randomly selected reaction rate
//
// Parameters:
//      reaction - Pointer to the reaction to change
//      config - Pointer to a struct containting configuration parameters.
//               See Config.h
void SetRandomBiUni(Reaction_Ptr reaction, Config_Ptr config);

// Returns a Reaction with one random reactant and two random products (UniBi),
// and a randomly selected reaction rate
//
// Parameters:
//      reaction - Pointer to the reaction to change
//      config - Pointer to a struct containting configuration parameters.
//               See Config.h
void SetRandomUniBi(Reaction_Ptr reaction, Config_Ptr config);

// Returns a Reaction with two random reactants and two random products (BiBi),
// and a randomly selected reaction rate
//
// Parameters:
//      reaction - Pointer to the reaction to change
//      config - Pointer to a struct containting configuration parameters.
//               See Config.h
void SetRandomBiBi(Reaction_Ptr reaction, Config_Ptr config);

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
                 species_t reactant_1,
                 species_t reactant_2,
                 species_t product_1,
                 species_t product_2,
                 rate_t rate_constant);

// Change the rate constant of a given reaction by at most a user provided
// amount. The change could either decrease or increase the reaction rate
//
// Parameters:
//      reaction - A pointer to the reaction to modify
//      config - Pointer to a struct containting configuration parameters.
//               See Config.h
void MutateRateConstant(Reaction_Ptr reaction, Config_Ptr config);

bool IsUniUni(Reaction_Ptr reaction);

bool IsUniBi(Reaction_Ptr reaction);

bool IsBiUni(Reaction_Ptr reaction);

bool IsBiBi(Reaction_Ptr reaction);

void GetReactionString(Reaction_Ptr reaction,
                       char *return_buf,
                       int reaction_num);

double GetRateOfChange(Reaction_Ptr reaction, N_Vector concentrations);

#endif // _REACTION_H_
