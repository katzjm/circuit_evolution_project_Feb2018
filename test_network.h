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
  }

  virtual ~Test_Network() {}

//  virtual void SetUp() {}

//  virtual void TearDown() {}

  Config c;
  Network network;

};  // Test_Network

}  // evolvertest

#endif // _EVOLVER_TEST_NETWORK_H_
