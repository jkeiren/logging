cmake_minimum_required(VERSION 2.8)
project (cpplogging)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(CMAKE_CXX_FLAGS_ANALYSIS "${CMAKE_CXX_FLAGS} --analyse")

if(NOT TARGET gtest)
  add_subdirectory(external/googletest)
endif()

# Trick to add header files to projects in IDEs like Visual Studio and XCode
file(GLOB_RECURSE ${PROJECT_NAME}_HEADERS "include/**.h")
file(GLOB_RECURSE ${PROJECT_NAME}_SOURCES "src/**.cpp")

add_custom_target(${PROJECT_NAME}_headers SOURCES ${${PROJECT_NAME}_HEADERS})

include_directories(include)
add_library (${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})

install (TARGETS ${PROJECT_NAME}
         LIBRARY DESTINATION lib
         ARCHIVE DESTINATION lib)
install (FILES ${HEADERS} DESTINATION include)

# Testing
add_subdirectory(test)

