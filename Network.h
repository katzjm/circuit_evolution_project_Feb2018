/*
 * A Network represents a group of reactions that governs how different
 * reagents interact with one another
 *
 * Author: Josh Katz
 */

#include "Reaction.h"

#define MAX_NUM_REACTIONS 30

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
//      max_num_reactions - The maximum number of reactions that can be
//                          in this network
//      min_num_reactions - The minimum number of reactions that can be
//                          in this network
//      num_reagents - The number of reagents that can be in this network
//      max_rate_constant - The largest rate constant any reaction can have
//      min_rate_constant - The smallest rate constant any reaction can have
void SetRandomNetwork(Network_Ptr network,
                      int max_num_reactions,
                      int min_num_reactions,
                      int num_reagents,
                      float max_rate_constant,
                      float min_rate_constant);


