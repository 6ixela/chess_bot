# add_library(my_project_lib my_functions.c)
set(SOURCES
    board.c
    board.h
    main.c
    piece.c
    piece.h
    bot.c
    bot.h
    )

add_library(chessLib ${SOURCES})

add_executable(chessBot ${SOURCES})

target_link_libraries(chessBot chessLib)
