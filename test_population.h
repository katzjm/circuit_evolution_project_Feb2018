/*
 * Tests that Population works correctly
 *
 * Author: Josh Katz
 */

#ifndef _EVOLVER_TEST_POPULATION_H_
#define _EVOLVER_TEST_POPULATION_H_

#include "gtest/gtest.h"

extern "C" {
  #include "Population.h"
  #include "Network.h"
  #include "Reaction.h"
  #include "Configs.h"
}

namespace evolvertest {

class Test_Population : public ::testing::Test {
 protected:
  Test_Population() {}

  virtual ~Test_Population() {}

//  virtual void SetUp() {}

//  virtual void TearDown() {}

  char config_file[25];
  Config c;
  Population pop;

};  // Test_Population

}  // evolvertest

#endif // _EVOLVER_TEST_POPULATION_H_
