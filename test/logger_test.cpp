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
  cpplog(error) << "An error message" << std::endl;
  cpplog(warning) << "A warning" << std::endl;
  cpplog(info) << "Some information" << std::endl;
  cpplog(verbose) << "Detailed information" << std::endl;
  cpplog(debug) << "Debugging info" << std::endl;
  cpplog(debug1) << "Detailed debugging info" << std::endl;
  cpplog(debug2) << "Detailed debugging info (2)" << std::endl;
  cpplog(debug3) << "Detailed debugging info (3)" << std::endl;
  cpplog(debug4) << "Detailed debugging info (4)" << std::endl;
  cpplog(debug5) << "Detailed debugging info (5)" << std::endl;
}

TEST(cpplogging, set_and_print)
{
  // Messages will only be printed up to debug, due to standard MAX_LOG_LEVEL
  logger::set_reporting_level(debug2);
  print_all_log_levels();
}

TEST(cpplogging, use_case)
{
  cpplog(info) << "Entering logging use case" << std::endl;
  const int count = 3;
  cpplog(debug) << "A loop with " << count << " iterations" << std::endl;
  for (int i = 0; i < count; ++i)
  {
    cpplog(debug1) << "the counter i = " << i << std::endl;
    if(i >= 2)
    {
      cpplog(debug2) << "the counter is greater then 2" << std::endl;
    }
  }
}

TEST(cpplogging, indentation)
{
  cpplog(info) << "Entering indentation test" << std::endl;
  const int count = 3;
  cpplog(info) << "A loop with " << count << " iterations" << std::endl;
  for (int i = 0; i < count; ++i)
  {
    cpplog(debug) << "the counter i = " << i << std::endl;
    if(i >= 2)
    {
      cpplog(debug) << "the counter is greater then 2" << std::endl;
    }
  }
}

TEST(cpplogging, multiline)
{
  cpplog(info) << "Testing multiline logging (line 1)" << std::endl
                 << "line 2" << std::endl
                 << "the last last line" << std::endl;
}

TEST(cpplogging, hint)
{
  logger::set_reporting_level(info);
  cpplog(debug, "test_hint") << "Testing hint, should not be printed" << std::endl;
  logger::set_reporting_level(debug, "test_hint");
  cpplog(debug, "test_hint") << "Testing hint, should be printed" << std::endl;
  cpplog(debug) << "Testing hint, should not be printed" << std::endl;
  logger::set_reporting_level(verbose, "test_hint");
  cpplog(info) << "Testing hint, should still be printed" << std::endl;
  logger::clear_reporting_level("test_hint");
}

TEST(cpplogging, file_logging)
{
  std::string filename("logger_test_file.txt");
  FILE * pFile;
  pFile = fopen (filename.c_str(), "w");
  ASSERT_NE(pFile, nullptr);

  file_output::set_stream(pFile);
  cpplog(info) << "This line is written to logger_test_file.txt" << std::endl;
  file_output::set_stream(stderr);
  fclose(pFile);
  cpplog(info) << "This line is written to stderr" << std::endl;
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
  EXPECT_LT(CPPLOG_MAX_LOG_LEVEL, debug5);
  cpplog(debug5) << "This line should not end with BOOM! ............. " << test_assert() << std::endl;
}

// Show that arguments to logging are not executed if the log level is larger
// than logger::reporting_level() (i.e. the BOOST_CHECK(false) in test_assert() should
// never be triggered.
TEST(cpplogging, non_execution_of_arguments_dynamic)
{
  EXPECT_GE(CPPLOG_MAX_LOG_LEVEL, debug);
  logger::set_reporting_level(verbose);
  cpplog(debug) << "This line should not end with BOOM! ............. " << test_assert() << std::endl;
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
  cpplog(info) << "There is just one newline";
  cpplog(info) << "in this message" << std::endl;
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
