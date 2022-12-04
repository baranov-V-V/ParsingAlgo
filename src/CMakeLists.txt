#executable

if(IS_LIB)
  target_include_directories(automata
    PUBLIC
      ${PROJECT_SOURCE_DIR}/include
    )

  target_sources(automata
    PUBLIC
      ${AUTOMATA_INCLUDE_DIR}/automata.hpp
      ${AUTOMATA_INCLUDE_DIR}/automata_utils.hpp
      ${AUTOMATA_INCLUDE_DIR}/transition.hpp
      ${AUTOMATA_INCLUDE_DIR}/rule.hpp
      ${AUTOMATA_INCLUDE_DIR}/grammar.hpp
      ${AUTOMATA_INCLUDE_DIR}/algorithms.hpp
      ${AUTOMATA_INCLUDE_DIR}/situation.hpp
    PRIVATE
      ${AUTOMATA_SOURCE_DIR}/automata.cpp
      ${AUTOMATA_SOURCE_DIR}/automata_utils.cpp
      ${AUTOMATA_SOURCE_DIR}/transition.cpp
      ${AUTOMATA_SOURCE_DIR}/rule.cpp
      ${AUTOMATA_SOURCE_DIR}/grammar.cpp
      ${AUTOMATA_SOURCE_DIR}/algorithms.cpp
      ${AUTOMATA_SOURCE_DIR}/situation.cpp
  )

else()
  target_include_directories(main
    PUBLIC
      ${PROJECT_SOURCE_DIR}/include
    )

  target_sources(main
    PUBLIC
      ${AUTOMATA_INCLUDE_DIR}/automata.hpp
      ${AUTOMATA_INCLUDE_DIR}/automata_utils.hpp
      ${AUTOMATA_INCLUDE_DIR}/transition.hpp
      ${AUTOMATA_INCLUDE_DIR}/rule.hpp
      ${AUTOMATA_INCLUDE_DIR}/grammar.hpp
      ${AUTOMATA_INCLUDE_DIR}/algorithms.hpp
      ${AUTOMATA_INCLUDE_DIR}/situation.hpp

    PRIVATE
      ${AUTOMATA_SOURCE_DIR}/automata.cpp
      ${AUTOMATA_SOURCE_DIR}/automata_utils.cpp
      ${AUTOMATA_SOURCE_DIR}/transition.cpp
      ${AUTOMATA_SOURCE_DIR}/rule.cpp
      ${AUTOMATA_SOURCE_DIR}/grammar.cpp
      ${AUTOMATA_SOURCE_DIR}/algorithms.cpp
      ${AUTOMATA_SOURCE_DIR}/main.cpp
      ${AUTOMATA_SOURCE_DIR}/situation.cpp

  )
endif()
