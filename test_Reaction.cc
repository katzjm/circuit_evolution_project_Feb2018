/*
 * Test that Reaction has the intended functionality
 *
 * Author: Josh Katz
 */

extern "C" {
  #include "Reaction.h"
  #include "Configs.h"
}

#include "test_Reaction.h"

namespace evolvertest {

TEST_F(Test_Reaction, TestRandomReaction) {
  int num_uni_uni = 0;
  int num_uni_bi = 0;
  int num_bi_uni = 0;
  int num_bi_bi = 0;

  for (int i = 0; i < 1000; i++) {
    SetRandomReaction(&reaction, &c);
    EXPECT_GE(reaction.reactant_1, 0);
    EXPECT_LT(reaction.reactant_1, c.num_species);
    EXPECT_GE(reaction.product_1, 0);
    EXPECT_LT(reaction.product_1, c.num_species);
    EXPECT_GE(reaction.reactant_2, -1);
    EXPECT_LT(reaction.reactant_2, c.num_species);
    EXPECT_GE(reaction.product_2, -1);
    EXPECT_LT(reaction.product_2, c.num_species);
    EXPECT_LT(reaction.rate_constant, 50);
    EXPECT_GE(reaction.rate_constant, 0);

    if (reaction.reactant_2 == -1 && reaction.product_2 == -1) {
      num_uni_uni++;
    } else if (reaction.reactant_2 == -1 && reaction.product_2 != -1) {
      num_uni_bi++;
    } else if (reaction.reactant_2 != -1 && reaction.product_2 == -1) {
      num_bi_uni++;
    } else {
      num_bi_bi++;
    }
  }

  printf("After 1000 reactions of equal type probability, there were:\n");
  printf("  %d uni uni reactions\n", num_uni_uni);
  printf("  %d uni bi reactions\n", num_uni_bi);
  printf("  %d bi uni reactions\n", num_bi_uni);
  printf("  %d bi bi reactions\n", num_bi_bi);

  EXPECT_GT(num_uni_uni, 100);
  EXPECT_GT(num_uni_bi, 100);
  EXPECT_GT(num_bi_uni, 100);
  EXPECT_GT(num_bi_bi, 100);
}

TEST_F(Test_Reaction, TestMutateRateConstant) {
  int num_increases = 0;
  int num_decreases = 0;

  SetRandomReaction(&reaction, &c);
  double prev_rate_constant = reaction.rate_constant;
  for (int i = 0; i < 1000; i++) {
    MutateRateConstant(&reaction, &c);
    EXPECT_GT(reaction.rate_constant, 0);

    // Note that it's ok for the new rate constant to be the same
    // as the old, so long that it happens infrequently. Failing this
    // test a few times in a thousand attempts should be fine
    EXPECT_NE(reaction.rate_constant, prev_rate_constant);

    if (reaction.rate_constant > prev_rate_constant) {
      num_increases++;
      EXPECT_LT(reaction.rate_constant - prev_rate_constant,
                prev_rate_constant * c.max_percent_rate_change);
    } else if (reaction.rate_constant < prev_rate_constant) {
      num_decreases++;
      EXPECT_LT(prev_rate_constant - reaction.rate_constant,
                prev_rate_constant * c.max_percent_rate_change);
    }
    prev_rate_constant = reaction.rate_constant;
  }

  EXPECT_GT(num_increases, 0);
  EXPECT_GT(num_decreases, 0);
}

TEST_F(Test_Reaction, TestGetRateOfChange) {
  N_Vector concentrations = N_VNew_Serial(c.num_species);
  for (int i = 0; i < c.num_species; i++) {
    NV_Ith_S(concentrations, i) = i;
  }

  SetReaction(&reaction, 4, 3, 3, 4, 5.0);
  EXPECT_EQ(60, GetRateOfChange(&reaction, concentrations));
  N_VDestroy_Serial(concentrations);
}

}  // evolvertest

