#include "game.h"
#include <iostream>
#include <stdio.h>

using namespace std;

void waitForAnyKey() {
    cout << "Press any key to start the game..." << endl;
    getchar();
}

int main() {
    int width = 30;
    int height = 15;

    waitForAnyKey();

    Tetris game(width, height);
    game.run();

    return 0;
}

