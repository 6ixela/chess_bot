set(SOURCES
    vector.c
    vector.h
    display.c
    display.h)

add_library(utils ${SOURCES})

target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                                        ${CMAKE_CURRENT_SOURCE_DIR}/../game
                                        ${CMAKE_CURRENT_SOURCE_DIR}/../piece)