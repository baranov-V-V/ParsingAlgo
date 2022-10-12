set(AUTOMATA_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(AUTOMATA_SOURCE_DIR  ${CMAKE_SOURCE_DIR}/src)

add_library(Automata)

target_include_directories(Automata
  PUBLIC
    ${CMAKE_SOURCE_DIR}/include
  )

target_sources(Automata
  PUBLIC
    ${ALGO_INCLUDE_DIR}/example.hpp
  PRIVATE
    ${ALGO_SOURCE_DIR}/example.cpp
)