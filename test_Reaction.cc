/*
 * Test that Reaction has the intended functionality
 *
 * Author: Josh Katz
 */

#include <cassert>
#include <iostream>

extern "C" {
    #include "Reaction.h"
    #include "Configs.h"
}

namespace test {

class Test_Reaction {

    // Test that Random Reactions can be made using config parameters
    void testRandomReactionCreation() {
        RConfig config;
        config.num_reagents = 10;
        config.prob_uni_uni = 0.25;
        config.prob_uni_bi = 0.25;
        config.prob_bi_uni = 0.25;
        config.prob_bi_bi = 0.25;
        config.max_rate_constant = 50;

        Reaction reac;
        for (int i = 0; i < 1000; i++) {
            SetRandomReaction(reac, config);
            
        }
    }

    

} // Test_Reaction

} // test
