/*
 * A Network represents a group of reactions that governs how different
 * reagents interact with one another
 *
 * Author: Josh Katz
 */

#include "Reaction.h"

#define MAX_NUM_REACTIONS 30

typedef struct network_str {
    
    int num_reactions;
    
