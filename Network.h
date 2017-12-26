/*
 * A Network represents a group of reactions that governs how different
 * reagents interact with one another. Note that a Network can support
 * MAX_NUM_REACTIONS at a time
 *
 * Author: Josh Katz
 */

#ifndef _NETWORK_H_
#define _NETWORK_H_

#include <stdbool.h>
#include "Reaction.h"
#include "Configs.h"

#define MAX_NUM_REACTIONS 20

// Memory block for maintaining a network of Reactions
typedef struct network_str {
  Reaction reactions[MAX_NUM_REACTIONS];
  int num_reactions;
} Network, *Network_Ptr;

// Fills the given network with a random number of random reactions with
// constraints outlined in the other parameters
//
// Parameters:
//      network - Pointer to the network to fill with reactions
//      nconfig - Pointer to a struct containing Network configuration
//                parameters. See Config.h
void SetRandomNetwork(Network_Ptr network, Config_Ptr nconfig);

// Fills the given Network with copies of the Reactions in reactions
//
// Parameters:
//      network - Pointer to the network to fill with reactions
//      reactions - Pointer to an array of reactions copy to network
//      num_reactions - The number of reactions in the given reaction array.
//                      Note that if this is greater than MAX_NUM_REACTIONS
//                      than only the first MAX_NUM_REACTIONS are copied into
//                      network
void SetNetwork(Network_Ptr network,
                Reaction_Ptr reactions,
                int num_reactions);

// Alters the given Network. The Network may have a Reaction added, taken away,
// or have a rate contoustant changed, with the probability of each mutation
// happening given by the client. If an addition or removal of a reaction
// cannot be done, the mutation will be a rate constant change
//
// Parameters:
//      network - Pointer to the network to mutate
//      nconfig - Pointer to a struct containing Network configuration
//                parameters. See Config.h
void MutateNetwork(Network_Ptr network, Config_Ptr nconfig);

// Adds a reaction to the given network
//
// Parameters:
//      network - Pointer to the network to add a reaction to
//      nconfig - Pointer to a struct containing Network configuration
//                parameters. See Config.h
//
// Returns:
//      true if a Reaction was successfully added, false otherwise
bool AddReaction(Network_Ptr network, Config_Ptr nconfig);

// Removes a reaction from the given network
//
// Parameters:
//      network - Pointer to the network to remove a reaction from
//
// Returns:
//      true if a Reaction was successfully removed, false otherwise
bool RemoveReaction(Network_Ptr network);

// Modifies the rate constant of one reaction in the given Network
//
// Parameters:
//      network - Pointer to the network to add a reaction to
//      nconfig - Pointer to a struct containing Network configuration
//                parameters. See Config.h
void ModifyRateConstant(Network_Ptr network, Config_Ptr nconfig);

#endif // _NETWORK_H_
