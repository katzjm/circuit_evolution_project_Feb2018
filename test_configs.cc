/*
 * Implements tests for Configs
 *
 * Author: Josh Katz
 */

extern "C" {
  #include "Configs.h"
}

#include "test_configs.h"
#include <ctime>

namespace evolvertest {

TEST_F(Test_Configs, TestNullFileConfiguration) {
  Configure(&test_config, NULL);
  EXPECT_EQ(test_config.fit_threshold, 0.001);
  EXPECT_EQ(test_config.max_num_generations, 2000);
  EXPECT_EQ(test_config.max_num_reactions, 10);
  EXPECT_EQ(test_config.min_num_reactions, 3);
  EXPECT_EQ(test_config.max_percent_rate_change, 0.01);
  EXPECT_EQ(test_config.max_pop_size, 100);
  EXPECT_EQ(test_config.prob_uni_uni, 0.40);
  EXPECT_EQ(test_config.prob_uni_bi, 0.15);
  EXPECT_EQ(test_config.prob_bi_uni, 0.15);
  EXPECT_EQ(test_config.prob_bi_bi, 0.30);
  EXPECT_EQ(test_config.max_rate_constant, 50);
  EXPECT_EQ(test_config.num_data_pts, 10);
  EXPECT_EQ(test_config.num_species, 5);
  EXPECT_EQ(test_config.function_type, 4);
  EXPECT_EQ(test_config.output_interval, 10);
  EXPECT_EQ(test_config.prob_add_reaction, 0.275);
  EXPECT_EQ(test_config.prob_remove_reaction, 0.225);
  EXPECT_EQ(test_config.prob_rate_change, 0.5);
  EXPECT_EQ(test_config.seed, 1508215203);
  EXPECT_EQ(test_config.initial_concentrations, 5.0);
  EXPECT_EQ(test_config.show_cvode_errors, false);
  EXPECT_EQ(test_config.time_based, true);
}

TEST_F(Test_Configs, TestUserSetupConfiguration) {
  Configure(&test_config, test_file);
  EXPECT_EQ(test_config.fit_threshold, 0.001);
  EXPECT_EQ(test_config.max_num_generations, 2000);
  EXPECT_EQ(test_config.max_num_reactions, 10);
  EXPECT_EQ(test_config.min_num_reactions, 3);
  EXPECT_EQ(test_config.max_percent_rate_change, 0.01);
  EXPECT_EQ(test_config.max_pop_size, 100);
  EXPECT_EQ(test_config.prob_uni_uni, 0.40);
  EXPECT_EQ(test_config.prob_uni_bi, 0.15);
  EXPECT_EQ(test_config.prob_bi_uni, 0.15);
  EXPECT_EQ(test_config.prob_bi_bi, 0.30);
  EXPECT_EQ(test_config.max_rate_constant, 50);
  EXPECT_EQ(test_config.num_data_pts, 10);
  EXPECT_EQ(test_config.num_species, 5);
  EXPECT_EQ(test_config.function_type, 4);
  EXPECT_EQ(test_config.output_interval, 10);
  EXPECT_EQ(test_config.prob_add_reaction, 0.275);
  EXPECT_EQ(test_config.prob_remove_reaction, 0.225);
  EXPECT_EQ(test_config.prob_rate_change, 0.5);
  EXPECT_EQ(test_config.seed, 1508215203);
  EXPECT_EQ(test_config.initial_concentrations, 5.0);
  EXPECT_EQ(test_config.show_cvode_errors, false);
  EXPECT_EQ(test_config.time_based, true);
}

}  // evolvertest
