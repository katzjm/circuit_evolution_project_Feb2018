/*
 * Tests that Cvode_Utils works correctly
 *
 * Author: Josh Katz
 */

#ifndef _EVOLVER_TEST_CVODE_UTILS_H_
#define _EVOLVER_TEST_CVODE_UTILS_H_

#include "gtest/gtest.h"

extern "C" {
  #include "Cvode_Utils.h"
  #include "Network.h"
  #include "Reaction.h"
  #include "Configs.h"
}

namespace evolvertest {

class Test_Cvode_Utils : public ::testing::Test {
 protected:
  Test_Cvode_Utils() {
    Configure(&c, NULL);
    Reaction rs[3];
    SetReaction(&rs[0], 1, 1, 2, NO_REAGENT, 2.0);
    SetReaction(&rs[1], 3, NO_REAGENT, 2, NO_REAGENT, 2.0);
    SetReaction(&rs[2], 2, NO_REAGENT, 4, 1, 2.0);
    SetNetwork(&network, rs, 0, 3);
  }

  virtual ~Test_Cvode_Utils() {}

//  virtual void SetUp() {}

//  virtual void TearDown() {}

  Config c;
  Network network;

};  // Test_Network

}  // evolvertest

#endif // _EVOLVER_TEST_CVODE_UTILS_H_
