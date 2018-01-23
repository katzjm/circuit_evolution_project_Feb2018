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
  N_Vector concentrations = GetNewNVector(&c);
  CvodeData cvode_data = { NULL, concentrations };
  UserData user_data = { NULL, &c };
  SetUpCvodeFirstRun(&cvode_data, &user_data);
  SetUpCvodeNextRun(&cvode_data);

  ASSERT_EQ(0, SetFirstGeneration(&pop, &c, &cvode_data, &user_data));
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
  N_Vector concentrations = GetNewNVector(&c);
  CvodeData cvode_data = { NULL, concentrations };
  UserData user_data = { NULL, &c };
  char network_buf[1024];

  SetUpCvodeFirstRun(&cvode_data, &user_data);
  ASSERT_EQ(0, SetFirstGeneration(&pop, &c, &cvode_data, &user_data));
  for (int i = 0; i < 10; i++) {
    for (int i = 0; i < c.max_pop_size; i++) {
      printf("%d. %lf\n", i + 1, pop.network_order[i]->fitness);
      GetNetworkString(pop.network_order[i], network_buf, "  ", "\n");
      printf("%s", network_buf);

      //EXPECT_LE(pop.network_order[i]->fitness, pop.network_order[i+1]->fitness);
    }

    SetUpCvodeNextRun(&cvode_data);
    ASSERT_EQ(0, SetNextGeneration(&pop, &c, &cvode_data, &user_data));
    printf("\n");
  }
}

}  // evolvertest

