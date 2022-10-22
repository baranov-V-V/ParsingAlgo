cmake_minimum_required(VERSION 3.8)

add_executable(Test test_automata_utils.cpp)

target_code_coverage(Test AUTO EXCLUDE test/*)

target_include_directories(Test
  PUBLIC
    ${CMAKE_SOURCE_DIR}/include
  )

target_sources(Test
  PUBLIC
    ${AUTOMATA_INCLUDE_DIR}/automata.hpp
    ${AUTOMATA_INCLUDE_DIR}/automata_utils.hpp
    ${AUTOMATA_INCLUDE_DIR}/transition.hpp
  PRIVATE
    ${AUTOMATA_SOURCE_DIR}/automata.cpp
    ${AUTOMATA_SOURCE_DIR}/transition.cpp
    ${AUTOMATA_SOURCE_DIR}/automata_utils.cpp
  ) 

target_link_libraries(Test
  PUBLIC
    gtest_main
)

add_test(
  NAME TestingAutomata
  COMMAND Test
)


