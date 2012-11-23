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
// Override MAX_LOG_LEVEL
// Must come before the first include of logger.h
#define MAX_LOG_LEVEL debug3
#include "cpplogging/logger.h"

using namespace log;

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
  log(info) << "Entering logging use case" << std::endl;
  const int count = 3;
  log(debug) << "A loop with " << count << " iterations" << std::endl;
  for (int i = 0; i < count; ++i)
  {
    log(debug1) << "the counter i = " << i << std::endl;
    if(i >= 2)
    {
      log(debug2) << "the counter is greater then or equal to 2" << std::endl;
    }
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
