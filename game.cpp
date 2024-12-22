#include "game.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <random>
#include <chrono>
#include <thread>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;
namespace fs = std::filesystem;

Tetris::Tetris(int w, int h) : width(w), height(h) {
    initialize();
}

void Tetris::loadFigures(const string& directory) {
    for (const auto& entry : fs::directory_iterator(directory)) {
        ifstream file(entry.path());
        if (file) {
            Block block;
            string line;
            while (getline(file, line)) {
                vector<int> row;
                for (char c : line) {
                    if (c == '0' || c == '1') {
                        row.push_back(c - '0');
                    }
                }
                block.shape.push_back(row);
            }
            blocks.push_back(block);
        }
    }
}

void Tetris::initialize() {
    loadFigures("figures");

    screen = vector<vector<int>>(height, vector<int>(width, 0));

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, blocks.size() - 1);
    currentBlock = blocks[dis(gen)];
    blockX = width / 2 - currentBlock.shape[0].size() / 2;
    blockY = 0;
}

void Tetris::run() {
    setBufferedInput(false);
    while (true) {
        clearScreen();
        draw();
        update();

        this_thread::sleep_for(chrono::milliseconds(1000));
    }
    setBufferedInput(true);
}

void Tetris::draw() {
    vector<vector<int>> tempScreen = screen;

    for (int i = 0; i < width; ++i) {
        tempScreen[0][i] = 1;
        tempScreen[height - 1][i] = 1;
    }

    for (int i = 0; i < height; ++i) {
        tempScreen[i][0] = 1;
        tempScreen[i][width - 1] = 1;
    }

    for (int i = 0; i < currentBlock.shape.size(); ++i) {
        for (int j = 0; j < currentBlock.shape[0].size(); ++j) {
            if (currentBlock.shape[i][j] == 1) {
                tempScreen[blockY + i][blockX + j] = 1;
            }
        }
    }

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (tempScreen[i][j] == 1) {
                if (i == 0 || i == height - 1) {
                    cout << "-";
                } else if (j == 0 || j == width - 1) {
                    cout << "|";
                } else {
                    cout << "#";
                }
            } else {
                if (i == 0 || i == height - 1) {
                    cout << "-";
                } else if (j == 0 || j == width - 1) {
                    cout << "|";
                } else {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
}

void Tetris::update() {
    if (kbhit()) {
        char key = getchar();
        if (key == 68) {
            moveLeft();
        } else if (key == 67) {
            moveRight();
        } else if (key == 72) {
            rotateBlock();
        }
    }

    if (!checkCollision(blockX, blockY + 1, currentBlock.shape)) {
        blockY++;
    } else {
        placeBlock();
        initialize();
    }
}

void Tetris::clearScreen() {
    cout << "\033[2J\033[H";
}

void Tetris::moveLeft() {
    if (!checkCollision(blockX - 1, blockY, currentBlock.shape)) {
        blockX--;
    }
}

void Tetris::moveRight() {
    if (!checkCollision(blockX + 1, blockY, currentBlock.shape)) {
        blockX++;
    }
}

void Tetris::rotateBlock() {
    int originalHeight = currentBlock.shape.size();
    int originalWidth = currentBlock.shape[0].size();

    vector<vector<int>> newShape(originalWidth, vector<int>(originalHeight));

    for (int i = 0; i < originalHeight; ++i) {
        for (int j = 0; j < originalWidth; ++j) {
            newShape[j][originalHeight - 1 - i] = currentBlock.shape[i][j];
        }
    }

    if (!checkCollision(blockX, blockY, newShape)) {
        currentBlock.shape = newShape;
    }
}

bool Tetris::checkCollision(int newX, int newY, const vector<vector<int>>& newShape) {
    for (int i = 0; i < newShape.size(); ++i) {
        for (int j = 0; j < newShape[0].size(); ++j) {
            if (newShape[i][j] == 1) {
                int x = newX + j;
                int y = newY + i;
                if (x < 0 || x >= width || y >= height || screen[y][x] == 1) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Tetris::placeBlock() {
    for (int i = 0; i < currentBlock.shape.size(); ++i) {
        for (int j = 0; j < currentBlock.shape[0].size(); ++j) {
            if (currentBlock.shape[i][j] == 1) {
                screen[blockY + i][blockX + j] = 1;
            }
        }
    }
}

int Tetris::kbhit() {
    termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

void Tetris::setBufferedInput(bool enable) {
    static termios oldt;
    termios newt;

    if (enable) {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    } else {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    }
}
