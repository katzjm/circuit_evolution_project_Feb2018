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

bool AddReaction(Network_Ptr network, NConfig_Ptr nconfig) {
    if (network->num_reactions == MAX_NUM_REACTIONS) {
        return false;
    }

    SetRandomReaction(&network->reactions[network->num_reactions], nconfig->rconfig);
    network->num_reactions++;
    return true;
}

bool RemoveReaction(Network_Ptr network) {
    if (network->num_reactions <= 0) {
        return false;
    }
    network->num_reactions--;
    return true;
}

void ModifyRateConstant(Network_Ptr network, NConfig_Ptr nconfig) {
    if (network->num_reactions < 1) {
        return;
    }

    int reaction_to_change = rand() % network->num_reactions;
    MutateRateConstant(&network->reactions[reaction_to_change], nconfig->rconfig);
}
