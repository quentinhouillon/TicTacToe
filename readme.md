# TicTacToe

Welcome to TicTacToe, a simple command-line game written in C using the ncurses library.

## Features

- Classic TicTacToe gameplay
- Interactive command-line interface

## Installation

1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/TicTacToe.git
    cd TicTacToe
    ```

2. Compile the game:
    ```sh
    gcc -o tictactoe tictactoe.c -lncurses
    ```

## Usage

Run the game with the following command:
```sh
./tictactoe
```

## How to Play

- The game is played on a 3x3 grid.
- Player 1 is 'X' and Player 2 is 'O'.
- Players take turns placing their marks in empty squares.
- The first player to get 3 of their marks in a row (horizontally, vertically, or diagonally) wins.
- If all 9 squares are filled and neither player has 3 in a row, the game is a draw.

### Enjoy the game!