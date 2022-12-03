cmake_minimum_required(VERSION 3.15)


#testing automata
add_executable(TestAutomata test_automata_utils.cpp)

target_include_directories(TestAutomata
  PUBLIC
    ${CMAKE_SOURCE_DIR}/include
  )

target_sources(TestAutomata
  PUBLIC
    ${AUTOMATA_INCLUDE_DIR}/automata.hpp
    ${AUTOMATA_INCLUDE_DIR}/automata_utils.hpp
    ${AUTOMATA_INCLUDE_DIR}/transition.hpp
  PRIVATE
    ${AUTOMATA_SOURCE_DIR}/automata.cpp
    ${AUTOMATA_SOURCE_DIR}/transition.cpp
    ${AUTOMATA_SOURCE_DIR}/automata_utils.cpp
  ) 

target_link_libraries(TestAutomata
  PUBLIC
    gtest_main
)

add_test(
  NAME TestingAutomata
  COMMAND TestAutomata
)


#testing rule
add_executable(TestRule test_rule.cpp)
target_include_directories(TestRule
  PUBLIC
    ${AUTOMATA_INCLUDE_DIR}
  )
target_sources(TestRule
  PRIVATE
    ${AUTOMATA_SOURCE_DIR}/rule.cpp
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
    ${AUTOMATA_INCLUDE_DIR}
  )
target_sources(TestGrammar
  PRIVATE
    ${AUTOMATA_SOURCE_DIR}/rule.cpp
    ${AUTOMATA_SOURCE_DIR}/grammar.cpp
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
    ${AUTOMATA_INCLUDE_DIR}
  )
target_sources(TestAlgorithms
  PRIVATE
    ${AUTOMATA_SOURCE_DIR}/rule.cpp
    ${AUTOMATA_SOURCE_DIR}/grammar.cpp
    ${AUTOMATA_SOURCE_DIR}/algorithms.cpp
    ${AUTOMATA_SOURCE_DIR}/situation.cpp
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
target_code_coverage(TestAutomata AUTO EXCLUDE test/*)


