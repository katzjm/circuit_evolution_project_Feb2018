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

TEST_F(Test_Configs, TestDefaultConfiguration) {
  Configure(&test_config, NULL);
  EXPECT_EQ(test_config.fit_threshold, 0.1);
  EXPECT_EQ(test_config.max_num_generations, 1000);
  EXPECT_EQ(test_config.max_num_reactions, 20);
  EXPECT_EQ(test_config.max_percent_rate_change, 0.1);
  EXPECT_EQ(test_config.max_pop_size, 100);
  EXPECT_EQ(test_config.max_rate_constant, 50);
  EXPECT_EQ(test_config.min_num_reactions, 2);
  EXPECT_EQ(test_config.num_data_pts, 10);
  EXPECT_EQ(test_config.num_species, 10);
  EXPECT_EQ(test_config.output_interval, 10);
  EXPECT_EQ(test_config.percent_to_clone, 0.5);
  EXPECT_EQ(test_config.prob_add_reaction, 0.25);
  EXPECT_EQ(test_config.prob_remove_reaction, 0.25);
  EXPECT_EQ(test_config.prob_rate_change, 0.5);
  EXPECT_EQ(test_config.prob_uni_uni, 0.25);
  EXPECT_EQ(test_config.prob_uni_bi, 0.25);
  EXPECT_EQ(test_config.prob_bi_uni, 0.25);
  EXPECT_EQ(test_config.prob_bi_bi, 0.25);
  EXPECT_GT(test_config.seed, 0);
  EXPECT_EQ(test_config.show_cvode_errors, false);
  EXPECT_EQ(test_config.time_based, false);
}

TEST_F(Test_Configs, TestUserSetupConfiguration) {
  Configure(&test_config, test_file);
  EXPECT_EQ(test_config.fit_threshold, 0.001);
  EXPECT_EQ(test_config.max_num_generations, 2000);
  EXPECT_EQ(test_config.max_num_reactions, 20);
  EXPECT_EQ(test_config.max_percent_rate_change, 0.1);
  EXPECT_EQ(test_config.max_pop_size, 100);
  EXPECT_EQ(test_config.max_rate_constant, 50);
  EXPECT_EQ(test_config.min_num_reactions, 2);
  EXPECT_EQ(test_config.num_data_pts, 10);
  EXPECT_EQ(test_config.num_species, 5);
  EXPECT_EQ(test_config.output_interval, 1);
  EXPECT_EQ(test_config.percent_to_clone, 0.4);
  EXPECT_EQ(test_config.prob_add_reaction, 0.275);
  EXPECT_EQ(test_config.prob_remove_reaction, 0.225);
  EXPECT_EQ(test_config.prob_rate_change, 0.5);
  EXPECT_EQ(test_config.prob_uni_uni, 0.40);
  EXPECT_EQ(test_config.prob_uni_bi, 0.15);
  EXPECT_EQ(test_config.prob_bi_uni, 0.15);
  EXPECT_EQ(test_config.prob_bi_bi, 0.30);
  EXPECT_EQ(test_config.seed, 1508215203);
  EXPECT_EQ(test_config.show_cvode_errors, false);
  EXPECT_EQ(test_config.time_based, true);
}

TEST_F(Test_Configs, TestNonExistantFileConfiguration) {
  Configure(&test_config, non_existant_file);
  EXPECT_EQ(test_config.fit_threshold, 0.1);
  EXPECT_EQ(test_config.max_num_generations, 1000);
  EXPECT_EQ(test_config.max_num_reactions, 20);
  EXPECT_EQ(test_config.max_percent_rate_change, 0.1);
  EXPECT_EQ(test_config.max_pop_size, 100);
  EXPECT_EQ(test_config.max_rate_constant, 50);
  EXPECT_EQ(test_config.min_num_reactions, 2);
  EXPECT_EQ(test_config.num_data_pts, 10);
  EXPECT_EQ(test_config.num_species, 10);
  EXPECT_EQ(test_config.output_interval, 10);
  EXPECT_EQ(test_config.percent_to_clone, 0.5);
  EXPECT_EQ(test_config.prob_add_reaction, 0.25);
  EXPECT_EQ(test_config.prob_remove_reaction, 0.25);
  EXPECT_EQ(test_config.prob_rate_change, 0.5);
  EXPECT_EQ(test_config.prob_uni_uni, 0.25);
  EXPECT_EQ(test_config.prob_uni_bi, 0.25);
  EXPECT_EQ(test_config.prob_bi_uni, 0.25);
  EXPECT_EQ(test_config.prob_bi_bi, 0.25);
  EXPECT_GT(test_config.seed, 0);
  EXPECT_EQ(test_config.show_cvode_errors, false);
  EXPECT_EQ(test_config.time_based, false);
}

TEST_F(Test_Configs, TestBadConfigsFileConfiguration) {
  Configure(&test_config, bad_configs_file);
  EXPECT_EQ(test_config.fit_threshold, 0.001);
  EXPECT_EQ(test_config.max_num_generations, 1000);
  EXPECT_EQ(test_config.max_num_reactions, 20);
  EXPECT_EQ(test_config.max_percent_rate_change, 0.1);
  EXPECT_EQ(test_config.max_pop_size, 100);
  EXPECT_EQ(test_config.max_rate_constant, 0);
  EXPECT_EQ(test_config.min_num_reactions, 2);
  EXPECT_EQ(test_config.num_data_pts, 10);
  EXPECT_EQ(test_config.num_species, 5);
  EXPECT_EQ(test_config.output_interval, 10);
  EXPECT_EQ(test_config.percent_to_clone, 0.5);
  EXPECT_EQ(test_config.prob_add_reaction, 0.25);
  EXPECT_EQ(test_config.prob_remove_reaction, 0.25);
  EXPECT_EQ(test_config.prob_rate_change, 0.5);
  EXPECT_EQ(test_config.prob_uni_uni, 0.25);
  EXPECT_EQ(test_config.prob_uni_bi, 0.25);
  EXPECT_EQ(test_config.prob_bi_uni, 0.25);
  EXPECT_EQ(test_config.prob_bi_bi, 0.25);
  EXPECT_EQ(test_config.seed, 0);
  EXPECT_EQ(test_config.show_cvode_errors, true);
  EXPECT_EQ(test_config.time_based, true);
}

}  // evolvertest
