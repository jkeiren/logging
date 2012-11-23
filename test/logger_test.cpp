// Author(s): Jeroen Keiren
// Copyright: see the accompanying file COPYING or copy at
// https://svn.win.tue.nl/trac/MCRL2/browser/trunk/COPYING
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
/// \file logger_test.cpp

#include <gtest/gtest.h>
#include "cpplogging/logger.h"

using namespace cpplogging;

void print_all_log_levels()
{
  log(error) << "An error message" << std::endl;
  log(warning) << "A warning" << std::endl;
  log(info) << "Some information" << std::endl;
  log(verbose) << "Detailed information" << std::endl;
  log(debug) << "Debugging info" << std::endl;
  log(debug1) << "Detailed debugging info" << std::endl;
  log(debug2) << "Detailed debugging info (2)" << std::endl;
  log(debug3) << "Detailed debugging info (3)" << std::endl;
  log(debug4) << "Detailed debugging info (4)" << std::endl;
  log(debug5) << "Detailed debugging info (5)" << std::endl;
}

TEST(cpplogging, set_and_print)
{
  // Messages will only be printed up to debug, due to standard MAX_LOG_LEVEL
  logger::set_reporting_level(debug2);
  print_all_log_levels();
}

TEST(cpplogging, use_case)
{
  log(info) << "Entering logging use case" << std::endl;
  const int count = 3;
  log(debug) << "A loop with " << count << " iterations" << std::endl;
  for (int i = 0; i < count; ++i)
  {
    log(debug1) << "the counter i = " << i << std::endl;
    if(i >= 2)
    {
      log(debug2) << "the counter is greater then 2" << std::endl;
    }
  }
}

TEST(cpplogging, indentation)
{
  log(info) << "Entering indentation test" << std::endl;
  const int count = 3;
  log(info) << "A loop with " << count << " iterations" << std::endl;
  for (int i = 0; i < count; ++i)
  {
    log(debug) << "the counter i = " << i << std::endl;
    if(i >= 2)
    {
      log(debug) << "the counter is greater then 2" << std::endl;
    }
  }
}

TEST(cpplogging, multiline)
{
  log(info) << "Testing multiline logging (line 1)" << std::endl
                 << "line 2" << std::endl
                 << "the last last line" << std::endl;
}

TEST(cpplogging, hint)
{
  logger::set_reporting_level(info);
  log(debug, "test_hint") << "Testing hint, should not be printed" << std::endl;
  logger::set_reporting_level(debug, "test_hint");
  log(debug, "test_hint") << "Testing hint, should be printed" << std::endl;
  log(debug) << "Testing hint, should not be printed" << std::endl;
  logger::set_reporting_level(verbose, "test_hint");
  log(info) << "Testing hint, should still be printed" << std::endl;
  logger::clear_reporting_level("test_hint");
}

TEST(cpplogging, file_logging)
{
  std::string filename("logger_test_file.txt");
  FILE * pFile;
  pFile = fopen (filename.c_str(), "w");
  ASSERT_NE(pFile, nullptr);

  file_output::set_stream(pFile);
  log(info) << "This line is written to logger_test_file.txt" << std::endl;
  file_output::set_stream(stderr);
  fclose(pFile);
  log(info) << "This line is written to stderr" << std::endl;
  remove(filename.c_str());
}

std::string test_assert()
{
  EXPECT_TRUE(false);
  return "BOOM!";
}

// Show that arguments to logging are not executed if the log level is larger
// than MAX_LOG_LEVEL (i.e. the BOOST_CHECK(false) in test_assert() should
// never be triggered.
TEST(cpplogging, non_execution_of_arguments_static)
{
  EXPECT_LT(MAX_LOG_LEVEL, debug5);
  log(debug5) << "This line should not end with BOOM! ............. " << test_assert() << std::endl;
}

// Show that arguments to logging are not executed if the log level is larger
// than logger::reporting_level() (i.e. the BOOST_CHECK(false) in test_assert() should
// never be triggered.
TEST(cpplogging, non_execution_of_arguments_dynamic)
{
  EXPECT_GE(MAX_LOG_LEVEL, debug);
  logger::set_reporting_level(verbose);
  log(debug) << "This line should not end with BOOM! ............. " << test_assert() << std::endl;
}

TEST(cpplogging, fflush)
{
  for(int i = 0; i < 10; ++i)
  {
    fprintf(stderr, "%d", i);
    fflush(stderr);
  }
  fprintf(stderr, "\n");
  fflush(stderr);
}

TEST(cpplogging, multiline_nonewline)
{
  log(info) << "There is just one newline";
  log(info) << "in this message" << std::endl;
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
