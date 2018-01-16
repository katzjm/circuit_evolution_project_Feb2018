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
  UserData ud = {&network, &c};
  N_Vector con = N_VNew_Serial(c.num_species);
  N_Vector condot = N_VNew_Serial(c.num_species);
  for (int i = 0; i < c.num_species; i++) {
    NV_Ith_S(con, i) = i;
    NV_Ith_S(condot, i) = 0;
  }

  ASSERT_EQ(0, GetSpeciesRateOfChange(0, con, condot, &ud));
  EXPECT_EQ(NV_Ith_S(condot, 1), 2);
  EXPECT_EQ(NV_Ith_S(condot, 2), 4);
  EXPECT_EQ(NV_Ith_S(condot, 3), 0);
  EXPECT_EQ(NV_Ith_S(condot, 4), 0);
}

TEST_F(Test_Cvode_Utils, TestIsSource) {
  EXPECT_EQ(false, IsSource(&network, 1));
  EXPECT_EQ(false, IsSource(&network, 2));
  EXPECT_EQ(true, IsSource(&network, 3));
  EXPECT_EQ(false, IsSource(&network, 4));
}

TEST_F(Test_Cvode_Utils, TestIsSink) {
  EXPECT_EQ(false, IsSink(&network, 1));
  EXPECT_EQ(false, IsSink(&network, 2));
  EXPECT_EQ(false, IsSink(&network, 3));
  EXPECT_EQ(true, IsSink(&network, 4));
}

TEST_F(Test_Cvode_Utils, TestIsChanging) {
  EXPECT_EQ(true, IsChanging(&network, 1));
  EXPECT_EQ(true, IsChanging(&network, 2));
  EXPECT_EQ(false, IsChanging(&network, 3));
  EXPECT_EQ(false, IsChanging(&network, 4));
}


}  // evolvertest
