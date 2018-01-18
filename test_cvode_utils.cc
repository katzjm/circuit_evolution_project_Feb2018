/*
 * Tests that Network works correctly
 *
 * Author: Josh Katz
 */

extern "C" {
  #include "Cvode_Utils.h"
  #include "Network.h"
  #include "Reaction.h"
  #include "Configs.h"
}

#include "test_cvode_utils.h"

namespace evolvertest {

TEST_F(Test_Cvode_Utils, TestGetSpeciesRateOfChange) {
  UserData ud = { &network, &c };
  N_Vector con = GetNewNVector(&c);
  N_Vector condot = GetNewNVector(&c);
  ASSERT_NE(con, nullptr);
  ASSERT_NE(condot, nullptr);
  for (int i = 0; i < c.num_species; i++) {
    NV_Ith_S(con, i) = i;
    NV_Ith_S(condot, i) = 0;
  }

  ASSERT_EQ(0, GetSpeciesRateOfChange(0, con, condot, &ud));
  EXPECT_EQ(NV_Ith_S(condot, 1), 0);
  EXPECT_EQ(NV_Ith_S(condot, 2), 4);
  EXPECT_EQ(NV_Ith_S(condot, 3), 0);
  EXPECT_EQ(NV_Ith_S(condot, 4), 0);
}

TEST_F(Test_Cvode_Utils, TestSingleRun) {
  N_Vector con = GetNewNVector(&c);
  N_Vector condot = GetNewNVector(&c);
  ASSERT_NE(con, nullptr);
  ASSERT_NE(condot, nullptr);
  for (int i = 0; i < c.num_species; i++) {
    NV_Ith_S(con, i) = i;
    NV_Ith_S(condot, i) = 0;
  }
  UserData ud = { &network, &c };
  CvodeData cvode_data = { NULL, con };

  SetUpCvodeFirstRun(&cvode_data, &ud);

  realtype tout = 1;
  realtype t = 0;
  ASSERT_TRUE(RunCvode(&cvode_data, tout, &t));
  EXPECT_GT(NV_Ith_S(con, 1), 1);
  EXPECT_LT(NV_Ith_S(con, 1), 2);
  EXPECT_GT(NV_Ith_S(con, 2), 4);
  EXPECT_LT(NV_Ith_S(con, 2), 5);
  EXPECT_EQ(NV_Ith_S(con, 3), 3);
  EXPECT_EQ(NV_Ith_S(con, 4), 4);

  tout = 8;
  ASSERT_TRUE(RunCvode(&cvode_data, tout, &t));
  EXPECT_GT(NV_Ith_S(con, 1), 1.5);
  EXPECT_LT(NV_Ith_S(con, 1), 2);
  EXPECT_GT(NV_Ith_S(con, 2), 5.75);
  EXPECT_LT(NV_Ith_S(con, 2), 6.25);
  EXPECT_EQ(NV_Ith_S(con, 3), 3);
  EXPECT_EQ(NV_Ith_S(con, 4), 4);

  DestroyCvode(&cvode_data);
}

TEST_F(Test_Cvode_Utils, TestMultipleRun) {
  N_Vector con = GetNewNVector(&c);
  N_Vector condot = GetNewNVector(&c);
  ASSERT_NE(con, nullptr);
  ASSERT_NE(condot, nullptr);
  for (int i = 0; i < c.num_species; i++) {
    NV_Ith_S(con, i) = i;
    NV_Ith_S(condot, i) = 0;
  }
  UserData ud = { &network, &c };
  CvodeData cvode_data = { NULL, con };

  SetUpCvodeFirstRun(&cvode_data, &ud);

  realtype tout = 1;
  realtype t = 0;
  ASSERT_TRUE(RunCvode(&cvode_data, tout, &t));
  EXPECT_GT(NV_Ith_S(con, 1), 1);
  EXPECT_LT(NV_Ith_S(con, 1), 2);
  EXPECT_GT(NV_Ith_S(con, 2), 4);
  EXPECT_LT(NV_Ith_S(con, 2), 5);
  EXPECT_EQ(NV_Ith_S(con, 3), 3);
  EXPECT_EQ(NV_Ith_S(con, 4), 4);

  tout = 8;
  ASSERT_TRUE(RunCvode(&cvode_data, tout, &t));
  EXPECT_GT(NV_Ith_S(con, 1), 1.5);
  EXPECT_LT(NV_Ith_S(con, 1), 2);
  EXPECT_GT(NV_Ith_S(con, 2), 5.75);
  EXPECT_LT(NV_Ith_S(con, 2), 6.25);
  EXPECT_EQ(NV_Ith_S(con, 3), 3);
  EXPECT_EQ(NV_Ith_S(con, 4), 4);

  for (int i = 0; i < c.num_species; i++) {
    NV_Ith_S(con, i) = i;
    NV_Ith_S(condot, i) = 0;
  }

  SetUpCvodeNextRun(&cvode_data);

  tout = 1;
  t = 0;
  ASSERT_TRUE(RunCvode(&cvode_data, tout, &t));
  EXPECT_GT(NV_Ith_S(con, 1), 1);
  EXPECT_LT(NV_Ith_S(con, 1), 2);
  EXPECT_GT(NV_Ith_S(con, 2), 4);
  EXPECT_LT(NV_Ith_S(con, 2), 5);
  EXPECT_EQ(NV_Ith_S(con, 3), 3);
  EXPECT_EQ(NV_Ith_S(con, 4), 4);

  tout = 8;
  ASSERT_TRUE(RunCvode(&cvode_data, tout, &t));
  EXPECT_GT(NV_Ith_S(con, 1), 1.5);
  EXPECT_LT(NV_Ith_S(con, 1), 2);
  EXPECT_GT(NV_Ith_S(con, 2), 5.75);
  EXPECT_LT(NV_Ith_S(con, 2), 6.25);
  EXPECT_EQ(NV_Ith_S(con, 3), 3);
  EXPECT_EQ(NV_Ith_S(con, 4), 4);

  DestroyCvode(&cvode_data);
}

}  // evolvertest
