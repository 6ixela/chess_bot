Welcome to the bot_chess project! You've just cloned an exciting C-based chess bot that's currently in development. This project aims to create a smart chess-playing bot that understands and implements chess rules, including the right to castle for both players.

The project has a well-organized structure with several key directories:
- `src`: This is where the main action happens! You'll find the core logic for the board, bot, game, moves, and pieces here.
- `newBoard`: Contains bitboard-related files, which are crucial for efficient chess operations.
- `piece`: Handles the functionality of individual chess pieces.
- `utils`: Houses helpful utility functions, including display and vector operations.
- `tests`: Contains test files to ensure everything works correctly.

To get started contributing:
1. Familiarize yourself with the code in these directories, especially in `src`.
2. Pay attention to the TODO comments, which mention modifying the code to change parameters based on piece movements.
3. If you're new to chess programming, take some time to understand bitboards and their importance in chess engines.

The project uses CMake for building, so make sure you have it installed. Each module has its own CMakeLists.txt file, making it easy to work on individual components.

Don't hesitate to explore, ask questions, and have fun improving this chess bot! Good luck, and happy coding!