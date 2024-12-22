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
    vector<Block> blocks;
    vector<vector<int>> screen;
    Block currentBlock;
    int blockX, blockY;

    void initialize();
    void draw();
    void update();
    void clearScreen();
    void moveLeft();
    void moveRight();
    void rotateBlock();
    bool checkCollision(int newX, int newY, const vector<vector<int>>& newShape);
    void placeBlock();
    int kbhit();
    void setBufferedInput(bool enable);
};

#endif
