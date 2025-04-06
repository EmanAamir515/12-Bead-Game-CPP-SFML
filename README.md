# 12-Bead-Game-CPP-SFML
This is a 2-player board game (like Checkers) where:
__Green (Player 1) and Blue (Player 2) take turns moving beads on a 5x5 grid.__
__The goal is to eliminate all opponent’s beads by jumping over them.__

**Compulsary to Run:**
(Requires SFML library installed and image files like Best.jpg in the folder.)
**Why It’s Cool**
Colorful UI: Glowing beads and menus.
Simple Rules: Easy to learn, hard to master.
Persistent Saves: No progress is lost!

**Key Features**
SFML Graphics
Uses sf::CircleShape to draw colored beads (Green/Blue) with glowing outlines.
Has a menu system (New Game, Continue, Exit) and win announcements.

**Game Logic:**
Valid Moves: Beads can move 1 or 2 steps diagonally (like Halma).
Jump Captures: If you jump over an opponent’s bead, it gets removed.
Turn Management: Tracks whose turn it is (Green/Blue).
Save/Load Game
Saves the board state to GAME.txt (with 'G' for Green, 'B' for Blue, 'E' for empty).
Loads the game to continue where you left off.
Visual Effects
Highlights possible moves in purple.
Shows a winner screen when the game ends.

**How It Works (Simplified Functions explanation)**
setbead(): Positions beads on the grid.
Greenbead()/Bluebead(): Sets colors for each player.
selectedbead(): Checks valid moves when a bead is clicked.
move(): Handles bead movement and captures.
checkwin(): Detects if a player has won.



