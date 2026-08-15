# Chess Bot 🎮♟️

A sophisticated chess engine written in C with a custom bitboard-based AI bot. Play against an intelligent alpha-beta pruning bot or watch two bots compete against each other!

## Features

**Game Modes**
- **Bot vs Bot**: Watch two chess engines play each other with configurable difficulty levels
- **Player vs Bot (White)**: Play as white against the AI
- **Player vs Bot (Black)**: Play as black against the AI

**AI Engine**
- Efficient bitboard representation for fast move generation
- Alpha-beta pruning algorithm with configurable search depth (1-7)
- Material-based position evaluation
- Center control bonus evaluation

**Game Features**
- Full chess rule implementation (castling, en passant, promotion)
- Algebraic notation support for moves (e.g., e2e4)
- Clean terminal-based UI with interactive gameplay
- Game statistics and move tracking

## Quick Start

### Prerequisites
- GCC or Clang compiler (C11 or later)
- CMake 3.10+

### Build & Run

```bash
# Clone the repository
git clone https://github.com/yourusername/bot_chess_test.git
cd bot_chess_test

# Build
mkdir -p build && cd build
cmake ..
make

# Play!
./chessBot
```

## Project Structure

```
bot_chess_test/
├── src/
│   ├── main.c                 # Game mode selection and main loop
│   ├── bitBoard/              # Bitboard implementation for efficient board representation
│   ├── bot/                   # Chess AI engine (alpha-beta pruning, evaluation)
│   ├── game/                  # Game state management and FEN parsing
│   │   ├── game_manager.h/c   # Central game manager (coordinates game flow)
│   ├── move/                  # Move generation and validation
│   ├── piece/                 # Piece definitions and properties
│   └── utils/                 # Utility functions
│       ├── display.h/c        # Board display and visualization
│       └── input.h/c          # Player input parsing and validation
├── tests/                     # Unit tests for game logic
└── build/                     # CMake build directory
```

## How to Play

### Select Game Mode

```
╔════════════════════════════════════════╗
║       Chess Game - Mode Selection      ║
╚════════════════════════════════════════╝

1. Bot vs Bot (watch two bots play)
2. Player (White) vs Bot
3. Bot vs Player (Black)

Choose a mode (1-3): 2
```

### Enter Moves in Algebraic Notation

```
Files (columns): a-h (left to right)
Ranks (rows):    1-8 (bottom to top)

Examples:
  e2e4      - Move pawn from e2 to e4
  e7e8q     - Promotion to queen
  e1g1      - Castling
```

### Commands
- `help` - Show help message
- `quit` - Quit the game

## Game Modes in Detail

### 1. Bot vs Bot
Watch two AI engines compete. Choose difficulty level (1-7) for both bots.

### 2. Player vs Bot (White)
You play as White, bot plays as Black. Test your chess skills!

### 3. Bot vs Player (Black)
You play as Black, bot plays as White.

## Algorithm Overview

### Bitboard Representation
64-bit integers represent piece positions for ultra-fast operations:
- O(1) bitwise operations
- Efficient move generation
- Fast board state copying

### Alpha-Beta Pruning
Intelligently searches the game tree by eliminating branches that cannot affect the result:
- Configurable depth (1-7)
- Dramatically faster than brute-force search
- Strength scales with depth

### Position Evaluation
Material + positional score:
- **Pawn**: 10 pts
- **Knight**: 30 pts
- **Bishop**: 30 pts
- **Rook**: 50 pts
- **Queen**: 200 pts
- **King**: 10000 pts
- **Bonus**: +1 for center control per square

## Architecture

### Game Flow
```
main()
  ├─ selectGameMode()
  ├─ selectBotDepth()
  └─ playGame()
      ├─ displayBoard()
      ├─ getPlayerMove() or gameManagerBotMove()
      ├─ updateGameState()
      └─ checkGameOver()
```

### Bitboard Storage
Each piece type gets its own 64-bit integer:
```
WPawn, BPawn       (White/Black Pawns)
WKnight, BKnight   (White/Black Knights)
WBishop, BBishop   (White/Black Bishops)
WRook, BRook       (White/Black Rooks)
WQueen, BQueen     (White/Black Queens)
WKing, BKing       (White/Black Kings)
```

## Performance

On modern CPUs (Intel i7/Ryzen 5):
- Move generation: ~5,000 positions/sec
- Search depth 5: ~2-3 seconds per move
- Search depth 7: ~10-15 seconds per move

## Contributing

We welcome contributions! Areas of interest:
- AI improvements (opening books, endgame knowledge)
- Performance optimizations
- UI enhancements
- Bug fixes

### To contribute:
1. Fork the repository
2. Create a feature branch
3. Make your improvements
4. Submit a pull request

## Future Enhancements

- [ ] Transposition tables
- [ ] Opening book
- [ ] Iterative deepening
- [ ] Graphical interface
- [ ] PGN support
- [ ] FEN position setup

## License

MIT License - feel free to use and modify!

## Acknowledgments

Built with chess programming best practices and love for the game ♟️

---

**Play, learn, and improve!** Questions? Open an issue!