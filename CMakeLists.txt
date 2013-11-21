cmake_minimum_required(VERSION 2.6)
project (cpplogging)

message (STATUS "Internal googletest: ${cpplogging_USE_INTERNAL_GOOGLETEST}")

# Target directories for the installation
if(NOT ${PROJECT_NAME}_BIN_DIR)
  set(${PROJECT_NAME}_BIN_DIR "bin" CACHE FILEPATH "Installation directory for the binaries")
endif()
if(NOT ${PROJECT_NAME}_LIB_DIR)
  set(${PROJECT_NAME}_LIB_DIR "lib" CACHE FILEPATH "Installation directory for the libraries")
endif()
if(NOT ${PROJECT_NAME}_INCLUDE_DIR)
  set(${PROJECT_NAME}_INCLUDE_DIR "include/${PROJECT_NAME}" CACHE FILEPATH "Installation directory for the headers")
endif()
if(NOT ${PROJECT_NAME}_USE_INTERNAL_GOOGLETEST)
  set(${PROJECT_NAME}_USE_INTERNAL_GOOGLETEST ON CACHE BOOL "If set, the internal version of googletest is used, otherwise we rely on a version of googletest being included in a calling script")
endif()

if(${PROJECT_NAME}_USE_INTERNAL_GOOGLETEST)
  message(STATUS "Using Google test from external/googletest")
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

