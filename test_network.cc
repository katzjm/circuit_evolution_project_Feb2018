/*
 * Tests that Network works correctly
 *
 * Author: Josh Katz
 */

extern "C" {
  #include "Network.h"
  #include "Reaction.h"
  #include "Configs.h"
}

#include "test_network.h"

namespace evolvertest {

TEST_F(Test_Network, TestRandomNetworkSetting) {
  for (int i = 0; i < 1000; i++) {
    SetRandomNetwork(&network, &c);

    EXPECT_GE(network.num_reactions, 2);
    EXPECT_LE(network.num_reactions, 20);

    // Test that the final memory block can be accessed
    rate_t rate = network.reactions[network.num_reactions - 1];
    EXPECT_GE(rate, 0);
    EXPECT_LE(rate, 50);
  }
}

}  // evolvertest
