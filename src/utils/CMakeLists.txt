set(SOURCES
    vector.c
    vector.h
    display.c
    display.h
    input.c
    input.h)

add_library(utils ${SOURCES})

target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                                        ${CMAKE_CURRENT_SOURCE_DIR}/../game
                                        ${CMAKE_CURRENT_SOURCE_DIR}/../piece
                                        ${CMAKE_CURRENT_SOURCE_DIR}/../board
                                        ${CMAKE_CURRENT_SOURCE_DIR}/../bitBoard)