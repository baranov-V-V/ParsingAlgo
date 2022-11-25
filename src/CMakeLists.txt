#executable

if(IS_LIB)
  target_include_directories(parsing_algo
    PUBLIC
      ${ALGO_INCLUDE_DIR}
    )

  target_sources(parsing_algo
    PRIVATE
      ${ALGO_SOURCE_DIR}/rule.cpp
      ${ALGO_SOURCE_DIR}/grammar.cpp
      ${ALGO_SOURCE_DIR}/algorithms.cpp
      ${ALGO_SOURCE_DIR}/situation.cpp
  )

else()
  target_include_directories(main
    PUBLIC
      ${ALGO_INCLUDE_DIR}
    )

  target_sources(main
    PRIVATE
      ${ALGO_SOURCE_DIR}/main.cpp
      ${ALGO_SOURCE_DIR}/algorithms.cpp
      ${ALGO_SOURCE_DIR}/rule.cpp
      ${ALGO_SOURCE_DIR}/grammar.cpp
      ${ALGO_SOURCE_DIR}/situation.cpp
  )

endif()
