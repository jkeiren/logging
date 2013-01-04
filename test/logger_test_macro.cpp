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
// Override CPPLOG_MAX_LOG_LEVEL
// Must come before the first include of logger.h
#define CPPLOG_MAX_LOG_LEVEL debug3
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
  // The last two won't be printed because of max log level.
}

TEST(cpplogging, set_and_print)
{
  // Print of debug3 level will not occur
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
      cpplog(debug2) << "the counter is greater then or equal to 2" << std::endl;
    }
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
