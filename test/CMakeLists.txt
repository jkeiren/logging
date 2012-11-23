# ########## Project setup ##########
project(cpplogging_tests)
cmake_minimum_required(VERSION 2.6)

ENABLE_TESTING()
# Define macro for build_and_run_test_targets
# This method compiles tests when invoked
macro(build_and_run_test_target TARGET)
  add_test(NAME "${TARGET}" COMMAND ${CMAKE_CTEST_COMMAND}
   --build-and-test
   "${CMAKE_CURRENT_SOURCE_DIR}"
   "${CMAKE_CURRENT_BINARY_DIR}"
   --build-noclean
   --build-nocmake
   --build-generator "${CMAKE_GENERATOR}"
   --build-makeprogram "${CMAKE_MAKE_PROGRAM}"
   --build-exe-dir "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
   --build-target "${TARGET}"
   --build-project "${PROJECT_NAME}"
   --test-command "${TARGET}"
  )
endmacro( build_and_run_test_target TARGET )

include_directories(
  ${cpplogging_SOURCE_DIR}/include
  ${gtest_SOURCE_DIR}/include
)

file(GLOB TEST_SOURCES "*.cpp")

foreach(TEST_SOURCE ${TEST_SOURCES})
  get_filename_component(test "${TEST_SOURCE}" NAME_WE)
  add_executable("${test}" "${TEST_SOURCE}")
  target_link_libraries("${test}"
     gtest
     gtest_main
     cpplogging
  )

  # MACRO is defined in CMakeLists.txt in root of source tree
  build_and_run_test_target( ${test} )
endforeach()
