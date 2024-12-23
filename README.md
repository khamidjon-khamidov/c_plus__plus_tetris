# Tetris Game

This is a simple Tetris game implemented in C++ for the macOS platform. The game is played in the terminal and supports basic Tetris functionalities such as moving, rotating, and placing blocks. Lines are cleared when they are completely filled.

## Features

- Randomly generated Tetris blocks
- Basic block controls (move left, move right, rotate, move down)
- Line clearing when a row is completely filled
- Simple command-line interface for setting screen width and height

## Controls

- `UP ARROW`: Rotate the block
- `LEFT ARROW`: Move block left
- `RIGHT ARROW`: Move block right
- `DOWN ARROW`: Immediately move block one step down

## Command Line Options

- `--help`: Show help message
- `--width WIDTH`: Set the width of the game screen (default: 30)
- `--height HEIGHT`: Set the height of the game screen (default: 15)

## Getting Started

### Prerequisites

- macOS
- g++ (GNU Compiler Collection)

### Building the Game

1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/tetris.git
    cd tetris
    ```

2. Compile the game:
    ```sh
    g++ -std=c++11 main.cpp game.cpp -o tetris
    ```

### Running the Game

1. Run the game with default settings:
    ```sh
    ./tetris
    ```

2. Run the game with custom width and height:
    ```sh
    ./tetris --width 40 --height 20
    ```

3. Alternatively, you can compile and run the game immediately by running the `run.sh` script:
    ```sh
    ./run.sh
    ```

### Help

For help, run:
```sh
./tetris --help
```

### Known Issues
Because terminal line height and character width are not equal, rotated blocks do not produce a visually expected view. This can make the game look slightly off, especially when blocks are rotated.

### Acknowledgments
- This game is inspired by the classic Tetris game.
- ChatGPT for assisting with code generation, debugging, and providing guidance throughout the development process.
- Stack Overflow for providing valuable solutions and code snippets used in this project.