#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>

using namespace std;

struct Block {
    vector<vector<int> > shape;
};

class Tetris {
public:
    Tetris(int width, int height);
    void loadFigures(const std::string& directory);
    void run();

private:
    int width;
    int height;
    vector<Block> blocks;

    void initialize();
    void draw();
    void update();
    void clearScreen();
};

#endif