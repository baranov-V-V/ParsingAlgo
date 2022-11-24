cmake_minimum_required(VERSION 3.15)

#testing rule
add_executable(TestRule test_rule.cpp)
target_include_directories(TestRule
  PUBLIC
    ${ALGO_INCLUDE_DIR}
  )
target_sources(TestRule
  PRIVATE
    ${ALGO_SOURCE_DIR}/rule.cpp
  )
target_link_libraries(TestRule
  PUBLIC
    gtest_main
)
add_test(
  NAME TestingRule
  COMMAND TestRule
)

#testing Grammar
add_executable(TestGrammar test_grammar.cpp)
target_include_directories(TestGrammar
  PUBLIC
    ${ALGO_INCLUDE_DIR}
  )
target_sources(TestGrammar
  PRIVATE
    ${ALGO_SOURCE_DIR}/rule.cpp
    ${ALGO_SOURCE_DIR}/grammar.cpp
  )
target_link_libraries(TestGrammar
  PUBLIC
    gtest_main
)
add_test(
  NAME TestingGrammar
  COMMAND TestGrammar
)

#testing Algorithms
add_executable(TestAlgorithms test_algorithms.cpp)
target_include_directories(TestAlgorithms
  PUBLIC
    ${ALGO_INCLUDE_DIR}
  )
target_sources(TestAlgorithms
  PRIVATE
    ${ALGO_SOURCE_DIR}/rule.cpp
    ${ALGO_SOURCE_DIR}/grammar.cpp
    ${ALGO_SOURCE_DIR}/algorithms.cpp
  )
target_link_libraries(TestAlgorithms
  PUBLIC
    gtest_main
)
add_test(
  NAME TestingAlgorithms
  COMMAND TestAlgorithms
)

target_code_coverage(TestRule AUTO EXCLUDE test/*)
target_code_coverage(TestGrammar AUTO EXCLUDE test/*)
target_code_coverage(TestAlgorithms AUTO EXCLUDE test/*)


