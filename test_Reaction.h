/*
 * Tests that Reaction works correctly
 *
 * Author: Josh Katz
 */

#ifndef _EVOLVER_TEST_REACTION_H_
#define _EVOLVER_TEST_REACTION_H_

#include "gtest/gtest.h"

extern "C" {
  #include "Reaction.h"
  #include "Configs.h"
}

namespace evolvertest {

class Test_Reaction : public ::testing::Test {
 protected:
  Test_Configs() {
    Configure(&c, NULL);
  }

  virtual ~Test_Configs() {}

//  virtual void SetUp() {}

//  virtual void TearDown() {}

  Config c;
  Reaction reaction;

} // evolvertest

#endif // _EVOLVER_TEST_REACTION_H_
