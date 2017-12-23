/*
 * A Network represents a group of reactions that governs how different
 * reagents interact with one another. Note that a Network can support
 * MAX_NUM_REACTIONS at a time
 *
 * Author: Josh Katz
 */

#include <stdlib.h>
#include <stdbool.h>

#include "Network.h"
#include "Reaction.h"
#include "Config.h"

// Simple min function. Should not be used when either x or y need to be
// evaluated before comparison
#define min(x, y) (((x) <= (y)) ? (x) : (y))

void SetRandomNetwork(Network_Ptr network, NConfig_Ptr nconfig) {
    int num_reaction_range = nconfig->max_num_reactions - nconfig->min_num_reactions;
    network->num_reactions = rand() % num_reaction_range + nconfig->min_num_reactions;
    for (int i = 0; i < network->num_reactions; i++) {
        SetRandomReaction(&network->reactions[i], nconfig->rconfig);
    }
}

void SetNetwork(Network_Ptr network, Reaction_Ptr reactions, int num_reactions) {
    network->num_reactions = min(num_reactions, MAX_NUM_REACTIONS);
    for (int i = 0; i < network->num_reactions; i++) {
        network->reactions[i] = reactions[i];
    }
}

// Alters the given Network. The Network may have a Reaction added, taken away,
// or have a rate contoustant changed, with the probability of each mutation
// happening given by the client. If an addition or removal of a reaction
// cannot be done, the mutation will be a rate constant change
//
// Parameters:
//      network - Pointer to the network to mutate
//      nconfig - Pointer to a struct containing Network configuration
//                parameters. See Config.h
void MutateNetwork(Network_Ptr network, NConfig_Ptr nconfig) {
    float mutation = (float) rand() / RAND_MAX;
    bool network_changed = false;

    if ((mutation -= nconfig->prob_add_reaction) <= 0) {
        network_changed = AddReaction(network, nconfig);
    } else if ((mutation -= nconfig->prob_remove_reaction) <= 0) {
        network_changed = RemoveReaction(network);
    }

    if (mutation > 0 || network_changed == false) {
        ModifyRateConstant(network, nconfig);
    }
}

// Adds a reaction to the given network
//
// Parameters:
//      network - Pointer to the network to add a reaction to
//      nconfig - Pointer to a struct containing Network configuration
//                parameters. See Config.h
//
// Returns:
//      0 if a Reaction was successfully added, 1 otherwise
bool AddReaction(Network_Ptr network, NConfig_Ptr nconfig);

// Removes a reaction from the given network
//
// Parameters:
//      network - Pointer to the network to remove a reaction from
//
// Returns:
//      0 if a Reaction was successfully removed, 1 otherwise
bool RemoveReaction(Network_Ptr network);

// Modifies the rate constant of one reaction in the given Network
//
// Parameters:
//      network - Pointer to the network to add a reaction to
//      nconfig - Pointer to a struct containing Network configuration
//                parameters. See Config.h
void ModifyRateConstant(Network_Ptr network, NConfig_Ptr nconfig);
