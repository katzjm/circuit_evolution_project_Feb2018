/*
 * Tests that Network works correctly
 *
 * Author: Josh Katz
 */

#ifndef _EVOLVER_TEST_NETWORK_H_
#define _EVOLVER_TEST_NETWORK_H_

#include "gtest/gtest.h"

extern "C" {
  #include "Network.h"
  #include "Reaction.h"
  #include "Configs.h"
}

namespace evolvertest {

class Test_Network : public ::testing::Test {
 protected:
  Test_Network() {
    Configure(&c, NULL);
    Reaction rs[3];
    SetReaction(&rs[0], 1, 1, 2, NO_REAGENT, 2.0);
    SetReaction(&rs[1], 3, NO_REAGENT, 2, NO_REAGENT, 2.0);
    SetReaction(&rs[2], 2, NO_REAGENT, 4, 1, 2.0);
    SetNetwork(&test_network, rs, 0, 3);
  }

  virtual ~Test_Network() {}

//  virtual void SetUp() {}

//  virtual void TearDown() {}

  Config c;
  Network network;
  Network test_network;

};  // Test_Network

}  // evolvertest

#endif // _EVOLVER_TEST_NETWORK_H_
