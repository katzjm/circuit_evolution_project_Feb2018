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
    rate_t rate = network.reactions[network.num_reactions - 1].rate_constant;
    EXPECT_GE(rate, 0);
    EXPECT_LE(rate, 50);
  }
}

TEST_F(Test_Network, TestRemoveReactionOK) {
  ASSERT_TRUE(RemoveReaction(&test_network));
  EXPECT_EQ(2, test_network.num_reactions);
  EXPECT_EQ(10, test_network.sources);
  EXPECT_EQ(4, test_network.sinks);
}

TEST_F(Test_Network, TestEvaluateVsTime) {
  N_Vector concentrations = GetNewNVector(&c);
  CvodeData cvode_data = { NULL, concentrations };
  UserData user_data = { &test_network, &c };

  SetUpCvodeFirstRun(&cvode_data, &user_data);
  ASSERT_EQ(0, EvaluateNetwork(&test_network, &c, &cvode_data));
  EXPECT_LE(test_network.fitness, 0.01);
}

TEST_F(Test_Network, TestRemoveAllReactions) {
  ASSERT_TRUE(RemoveReaction(&test_network));
  EXPECT_EQ(2, test_network.num_reactions);
  EXPECT_EQ(10, test_network.sources);
  EXPECT_EQ(4, test_network.sinks);

  ASSERT_TRUE(RemoveReaction(&test_network));
  EXPECT_EQ(1, test_network.num_reactions);
  EXPECT_EQ(2, test_network.sources);
  EXPECT_EQ(4, test_network.sinks);

  ASSERT_FALSE(RemoveReaction(&test_network));
  EXPECT_EQ(1, test_network.num_reactions);
  EXPECT_EQ(2, test_network.sources);
  EXPECT_EQ(4, test_network.sinks);
}

TEST_F(Test_Network, TestAddReaction) {
  ASSERT_TRUE(AddReaction(&test_network, &c));
  EXPECT_EQ(4, test_network.num_reactions);
}

TEST_F(Test_Network, TestAddTooManyReactions) {
  for (int i = 4; i <= MAX_NUM_REACTIONS; i++) {
    ASSERT_TRUE(AddReaction(&test_network, &c));
    EXPECT_EQ(i, test_network.num_reactions);
  }
  ASSERT_FALSE(AddReaction(&test_network, &c));
  EXPECT_EQ(20, test_network.num_reactions);
}

TEST_F(Test_Network, TestIsSource) {
  EXPECT_FALSE(IsSource(&test_network, 1));
  EXPECT_FALSE(IsSource(&test_network, 2));
  EXPECT_TRUE(IsSource(&test_network, 3));
  EXPECT_FALSE(IsSource(&test_network, 4));
}

TEST_F(Test_Network, TestIsSink) {
  EXPECT_FALSE(IsSink(&test_network, 1));
  EXPECT_FALSE(IsSink(&test_network, 2));
  EXPECT_FALSE(IsSink(&test_network, 3));
  EXPECT_TRUE(IsSink(&test_network, 4));
}

TEST_F(Test_Network, TestIsChanging) {
  EXPECT_TRUE(IsChanging(&test_network, 1));
  EXPECT_TRUE(IsChanging(&test_network, 2));
  EXPECT_FALSE(IsChanging(&test_network, 3));
  EXPECT_FALSE(IsChanging(&test_network, 4));
}

}  // evolvertest
