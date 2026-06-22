# LUDO Game in C

A console-based implementation of the classic LUDO board game written in C. This project features four players, each controlling four pieces, with various game mechanics including dice rolling, piece movement, capturing opponents, and mystery cells that add unpredictability to the gameplay.

## Author

**H.G.Suraweera** (23002001)

## Features

- **4-Player Game**: Red, Green, Yellow, and Blue players
- **4 Pieces per Player**: Each player controls four pieces
- **Dice Rolling**: Random dice rolls determine movement and first player
- **Piece Movement**: Move pieces around a 52-position board
- **Capturing Mechanics**: Land on opponent pieces to send them back to base
- **Mystery Cells**: Randomly appearing special cells that teleport pieces to predefined positions (Bhawana, Kotuwa, Pita-Kotuwa)
- **Approach Cells**: Special positions that lead pieces toward home
- **Win Condition**: First player to move all four pieces to home wins

## Game Rules

1. **Starting the Game**:
   - Each player rolls a die; the highest roll determines who goes first
   - Player order is set based on the initial roll results

2. **Entering the Board**:
   - Pieces start at the base (position -1)
   - Roll a 6 to enter a piece onto the board at your starting position
   - Starting positions: Red (28), Green (41), Yellow (2), Blue (15)

3. **Movement**:
   - Roll the dice to move pieces forward
   - Pieces move around the 52-position board
   - Landing on an opponent's piece captures it (sends it back to base)

4. **Special Positions**:
   - **Base (-1)**: Starting position for all pieces
   - **Home (-2)**: Final destination; first player to get all pieces home wins
   - **Approach Cell (-3)**: Entry point to the home path for each player
   - **Mystery Cells**: Randomly appear on the board and teleport pieces to special locations

5. **Mystery Cell Teleportation**:
   - When a piece lands on a mystery cell, it is teleported to one of three positions:
     - Position 9 (Bhawana)
     - Position 27 (Kotuwa)
     - Position 46 (Pita-Kotuwa)

6. **Extra Turns**:
   - Rolling a 6 grants an extra turn

## Project Structure

```
LUDOgame/
├── ludo.c           # Main game loop and player turn management
├── gamelogic.c      # Core game mechanics and logic
├── types.c          # Data structures and type definitions
├── ludo_latex_report.tex  # Detailed technical report (LaTeX)
├── ludo_latex_report.pdf  # Compiled PDF report
└── README.md        # This file
```

## How to Compile and Run

### Prerequisites
- GCC compiler (or any C compiler)
- Make (optional, for using Makefile)

### Compilation

Using GCC directly (since `ludo.c` already `#include`s the other files):
```bash
gcc ludo.c -o ludo_game
```

### Running the Game

```bash
./ludo_game
```

On Windows:
```bash
ludo_game.exe
```

## Gameplay Example

```
Red rolls 3
Green rolls 6
Yellow rolls 2
Blue rolls 4

Green player rolled the highest with 6 and began the game first!!!!

player order: Green	Yellow	Blue	Red	

=============================== round 1!!========
>>>>>>>>>>>>>>>>>>>>> A mystery cell appered in 15 position
Green rolled 4
Green's piece 1 enters the board at position 41 (start position)!!!
...
```

## Technical Details

### Data Structures

The core structure used is `player`, which encapsulates all information for each player:

```c
struct player {
    char *name;
    int Sposition;      // Starting position on board
    int pieces[4];      // Positions of the four pieces
    int teleport[3];    // Teleportation positions
};
```

### Key Functions

- `roll_dice()`: Generates random dice roll (1-6)
- `rollDice()`: Determines first player by rolling for all players
- `playerOrder()`: Sets the turn order based on initial rolls
- `initPlayers()`: Initializes all players and pieces
- `move_pieces()`: Handles piece movement based on dice rolls
- `capture()`: Checks and executes capturing of opponent pieces
- `mysterycells()`: Manages mystery cell appearance logic
- `mysterycellbehave()`: Handles teleportation when landing on mystery cells
- `roadToHome()`: Manages movement along the home path
- `allPiecesInHome()`: Checks if a player has won

### Time Complexity

- **Piece Movement**: O(1) - Fixed number of operations
- **Player Order Determination**: O(1) - Constant number of players (4)
- **Capturing**: O(1) - Fixed number of pieces to check
- **Mystery Cell Teleportation**: O(1) - Simple random selection

The overall program maintains O(1) time complexity for most operations due to the fixed number of players and pieces.

## Game Mechanics

### Board Layout
- Circular board with 52 positions
- Each player has a unique starting position
- Special approach cells lead to individual home paths
- Mystery cells appear dynamically during gameplay

### Piece States
- **Base (-1)**: Piece is waiting to enter the board
- **On Board (0-51)**: Piece is on the main board
- **Approach Cell (-3)**: Piece is on the path to home
- **Home (-2)**: Piece has reached its destination

### AI Behavior
Each player (Red, Green, Yellow, Blue) has automated decision-making logic that:
1. Prioritizes moving pieces on approach cells
2. Attempts to capture opponent pieces when possible
3. Moves pieces out of base when advantageous
4. Moves the first available piece as a fallback

## Development

This project demonstrates:
- Modular C programming with separate concerns
- Use of structures for data organization
- Random number generation for game mechanics
- Console-based user interface
- Game state management
- Turn-based game logic

## Future Enhancements

Possible improvements that could be made:
- Add human player input option
- Implement graphical board display
- Add sound effects
- Save/load game state
- Network multiplayer support
- Configurable board sizes and player counts

## License

This is an academic project created for educational purposes.

## References

See `ludo_latex_report.pdf` for the complete technical documentation and implementation details.