#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>

using namespace std;

struct Block {
    vector<vector<int>> shape;
};

class Tetris {
public:
    Tetris(int width, int height);
    void loadFigures(const string& directory);
    void run();

private:
    int width;
    int height;
    bool gameOver = false;
    vector<Block> blocks;
    vector<vector<int>> screen;
    Block currentBlock;
    int blockX, blockY;

    bool checkInitialCollision(int startX, int startY, const vector<vector<int>>& shape);
    void initialize();
    void createBlock();
    void draw();
    void update();
    void clearScreen();
    bool moveLeft();
    bool moveRight();
    bool rotateBlock();
    bool checkCollision(int newX, int newY, const vector<vector<int>>& newShape);
    void placeBlock();
    int kbhit();
    void setBufferedInput(bool enable);
};

#endif
