cmake_minimum_required(VERSION 3.15)

project(PARSING_ALGORITHMS)

set(IS_LIB "YES")
if(PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(IS_LIB "NO")
endif()

if(IS_LIB)
  message(DUBUG: " BUILDING AS LIB")
else()
  message(DUBUG: " BUILDING FOR TEST OR EXECUTE")
endif()

if(NOT IS_LIB)
  list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/third_party/cmake-scripts")
  include(code-coverage)
  add_code_coverage()
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 99)
set(CMAKE_POSITION_INDEPENDENT_CODE)

set(ALGO_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(ALGO_SOURCE_DIR  ${PROJECT_SOURCE_DIR}/src)
set(ALGO_TEST_DIR    ${PROJECT_SOURCE_DIR}/test)

if(IS_LIB)
  add_library(parsing_algo)
else()
  add_executable(main)
endif()

if(NOT IS_LIB)
  message(DUBUG " ENABLE TESTS")

  enable_testing()
  add_subdirectory(third_party)
  add_subdirectory(test)
endif()

add_subdirectory(src)