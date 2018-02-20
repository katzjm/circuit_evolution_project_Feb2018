/*
 * Tests that Population works correctly
 *
 * Author: Josh Katz
 */

extern "C" {
  #include "Population.h"
  #include "Network.h"
  #include "Reaction.h"
  #include "Configs.h"
}

#include "test_population.h"

namespace evolvertest {

TEST_F(Test_Population, TestSetFirstGeneration) {
  Configure(&c, "setup_pop.txt");

  ASSERT_EQ(0, SetFirstGeneration(&pop, &c));
  for (int i = 0; i < c.max_pop_size - 1; i++) {
    printf("%d. %lf\n", i + 1, pop.network_order[i]->fitness);
    EXPECT_LE(pop.network_order[i]->fitness, pop.network_order[i+1]->fitness);
  }

  char network_buf[512];
  GetNetworkString(pop.network_order[1], network_buf, "  ", "\n");
  printf("%s", network_buf);
}

TEST_F(Test_Population, TestRepeatGenerations) {
  Configure(&c, "setup_pop.txt");
  char network_buf[512];
  
  ASSERT_EQ(0, SetFirstGeneration(&pop, &c));
  for (int i = 0; i < 2; i++) {
    for (int i = 0; i < c.max_pop_size; i++) {
      printf("%d. %lf\n", i + 1, pop.network_order[i]->fitness);
      GetNetworkString(pop.network_order[i], network_buf, "  ", "\n");
      printf("%s", network_buf);
    }

    ASSERT_EQ(0, SetNextGeneration(&pop, &c));
    printf("\n");
  }
}

}  // evolvertest

