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

TEST_F(Test_Population, TestOscillatorStaysOnTop) {
  Config c_o;
  Configure(&c_o, "test-files/test_network_oscillator.txt");
  
  Reaction ro[3];
  Network oscillator;
  SetReaction(&ro[0], 0, 1, 1, 1, 1.0);
  SetReaction(&ro[1], 1, 2, 2, 2, 1.0); 
  SetReaction(&ro[2], 2, NO_REAGENT, 3, NO_REAGENT, 1.0);
  SetNetwork(&oscillator, ro, 0, 3);

  char network_buf[512];

  ASSERT_EQ(0, SetFirstGeneration(&pop, &c_o));

  *pop.network_order[45] = oscillator;
  GetNetworkString(pop.network_order[45], network_buf, "  ", "\n");
  printf("Initial top with oscillator put on:\n%s\n\n", network_buf);

  for (int i = 0; i < 1000; i++) {
    ASSERT_EQ(0, SetNextGeneration(&pop, &c_o));
  }

  GetNetworkString(pop.network_order[0], network_buf, "  ", "\n");

  printf("End top with oscillator put on:\n%s\n", network_buf);
}

TEST_F(Test_Population, TestOscillatorVariantsConverge) {
  Config c_o;
  Configure(&c_o, "test-files/test_network_oscillator.txt");
  
  Reaction ro[3];
  Network oscillator;
  SetReaction(&ro[0], 0, 1, 1, 1, 1.0);
  SetReaction(&ro[1], 1, 2, 2, 2, 1.0); 
  SetReaction(&ro[2], 2, NO_REAGENT, 3, NO_REAGENT, 1.0);
  SetNetwork(&oscillator, ro, 0, 3);

  char network_buf[512];

  ASSERT_EQ(0, SetFirstGeneration(&pop, &c_o));

  *pop.network_order[0] = oscillator;
  pop.network_order[0]->reactions[0].rate_constant = 2.0;
  *pop.network_order[1] = oscillator;
  pop.network_order[1]->reactions[0].rate_constant = 2.0;
  *pop.network_order[2] = oscillator;
  pop.network_order[2]->reactions[0].rate_constant = 2.0;
  *pop.network_order[3] = oscillator;
  pop.network_order[3]->reactions[0].rate_constant = 2.0;
  *pop.network_order[4] = oscillator;
  pop.network_order[4]->reactions[0].rate_constant = 2.0;

  ASSERT_EQ(EvaluateNetwork(&oscillator, &c_o, &pop.cvode_data, &pop.user_data), 0);
  ASSERT_EQ(EvaluateNetwork(pop.network_order[0], &c_o, &pop.cvode_data, &pop.user_data), 0);

  printf("Fitenss of normal oscillator: %lf\n", oscillator.fitness);
  printf("Fitness of altered oscillator: %lf\n", pop.network_order[0]->fitness);

  for (int i = 0; i < 1000; i++) {
    ASSERT_EQ(0, SetNextGeneration(&pop, &c_o));
    for (int i = 0; i < pop.num_networks; i++) {
      printf("Fitess of network %d: %lf\n", i + 1, pop.network_order[i]->fitness);
    }
    printf("\n");
  }

  GetNetworkString(pop.network_order[0], network_buf, "  ", "\n");

  printf("End top with oscillator put on:\n%s\n", network_buf);
}

}  // evolvertest

