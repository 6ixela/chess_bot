set(SOURCES_TESTS
    test_evaluation.c
    test_game.c
    test_vector.c
    test_move.c
)



add_executable(tests ${SOURCES_TESTS})
target_compile_options(tests PRIVATE --coverage)

target_include_directories(tests PRIVATE ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(tests game piece bot move utils)



add_test(NAME my_test COMMAND ${CMAKE_BINARY_DIR}/tests/tests)
