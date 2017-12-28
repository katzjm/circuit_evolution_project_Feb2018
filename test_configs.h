/*
 * Tests that configs works correctly
 *
 * Author: Josh Katz
 */

#ifndef _EVOLVER_TEST_CONFIGS_H_
#define _EVOLVER_TEST_CONFIGS_H_

#include "gtest/gtest.h"

extern "C" {
  #include "Configs.h"
}

namespace evolvertest {

class Test_Configs : public ::testing::Test {
 protected:
  Test_Configs() {
    test_file = "test-configs/setup.txt";
    non_existant_file = "test-configs/hello.txt";
    bad_format_file = "test-configs/setup_bad_format.txt";
    bad_configs_file = "test-configs/setup_bad_configs.txt";
  }

  virtual ~Test_Configs() {}

//  virtual void SetUp() {}

//  virtual void TearDown() {}

  Config test_config;
  const char *test_file;
  const char *non_existant_file;
  const char *bad_format_file;
  const char *bad_configs_file;
};

} // evolvertest

#endif // _EVOLVER_TEST_CONFIGS_H_
