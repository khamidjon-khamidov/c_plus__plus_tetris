#include "game.h"
#include <iostream>
#include <stdio.h>

using namespace std;

int main() {
    int width, height;
    cout << "Enter screen width: ";
    cin >> width;
    cout << "Enter screen height: ";
    cin >> height;

    Tetris game(width, height);
    game.run();

    return 0;
}