cmake_minimum_required(VERSION 2.6)
project (cpplogging)

add_subdirectory(external/googletest)

# Trick to add header files to projects in IDEs like Visual Studio and XCode
file(GLOB_RECURSE HEADERS "include/**.h")
file(GLOB_RECURSE SOURCES "src/**.cpp")
add_custom_target(${PROJECT_NAME}_headers
  SOURCES ${HEADERS}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(CMAKE_CXX_FLAGS_ANALYSIS "${CMAKE_CXX_FLAGS} --analyse")

include_directories(include)

add_library (cpplogging
  ${SOURCES}
)

# Testing
add_subdirectory(test)

