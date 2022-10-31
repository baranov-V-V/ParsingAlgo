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
    PRIVATE
      ${AUTOMATA_SOURCE_DIR}/automata.cpp
      ${AUTOMATA_SOURCE_DIR}/automata_utils.cpp
      ${AUTOMATA_SOURCE_DIR}/transition.cpp
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
    PRIVATE
      ${AUTOMATA_SOURCE_DIR}/automata.cpp
      ${AUTOMATA_SOURCE_DIR}/automata_utils.cpp
      ${AUTOMATA_SOURCE_DIR}/transition.cpp
      ${AUTOMATA_SOURCE_DIR}/main.cpp
  )
endif()
