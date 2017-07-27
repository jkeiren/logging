cmake_minimum_required(VERSION 2.8)
project (cpplogging)

# Target directories for the installation
if(NOT DEFINED ${PROJECT_NAME}_BIN_DIR)
  set(${PROJECT_NAME}_BIN_DIR "bin" CACHE FILEPATH "Installation directory for the binaries")
endif()
if(NOT DEFINED ${PROJECT_NAME}_LIB_DIR)
  set(${PROJECT_NAME}_LIB_DIR "lib" CACHE FILEPATH "Installation directory for the libraries")
endif()
if(NOT DEFINED ${PROJECT_NAME}_INCLUDE_DIR)
  set(${PROJECT_NAME}_INCLUDE_DIR "include/${PROJECT_NAME}" CACHE FILEPATH "Installation directory for the headers")
endif()

### Include google test
if(NOT TARGET gtest)
  add_subdirectory(external/googletest)
endif()

# Trick to add header files to projects in IDEs like Visual Studio and XCode
file(GLOB_RECURSE ${PROJECT_NAME}_HEADERS "include/**.h")
file(GLOB_RECURSE ${PROJECT_NAME}_SOURCES "src/**.cpp")

add_custom_target(${PROJECT_NAME}_headers
  SOURCES ${${PROJECT_NAME}_HEADERS}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(CMAKE_CXX_FLAGS_ANALYSIS "${CMAKE_CXX_FLAGS} --analyse")

include_directories(include)

add_library (${PROJECT_NAME}
  ${${PROJECT_NAME}_SOURCES}
)

install (TARGETS ${PROJECT_NAME} DESTINATION ${${PROJECT_NAME}_LIB_DIR})
install (FILES ${HEADERS} DESTINATION ${${PROJECT_NAME}_INCLUDE_DIR})

# Testing
add_subdirectory(test)

