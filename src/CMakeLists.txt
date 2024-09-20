# add_library(my_project_lib my_functions.c)
set(SOURCES
    board.c
    board.h
    main.c
    piece.c
    piece.h
    )

add_subdirectory(bot)

add_subdirectory(game)

add_library(chessLib ${SOURCES})

add_executable(chessBot ${SOURCES})

target_link_libraries(chessBot chessLib)
