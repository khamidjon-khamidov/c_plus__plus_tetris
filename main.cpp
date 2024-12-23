#include "game.h"
#include <iostream>
#include <stdio.h>

using namespace std;

void showHelp() {
    cout << "Usage: tetris [OPTIONS]\n";
    cout << "Options:\n";
    cout << "  --help           Show this help message\n";
    cout << "  --width WIDTH    Set the width of the game screen\n";
    cout << "  --height HEIGHT  Set the height of the game screen\n";
    cout << "\nControls:\n";
    cout << "  UP ARROW         Rotate the block\n";
    cout << "  LEFT ARROW       Move block left\n";
    cout << "  RIGHT ARROW      Move block right\n";
    cout << "  DOWN ARROW       Immediately move block one step down\n";
}

void waitForAnyKey() {
    cout << "Press any key to start the game..." << endl;
    getchar();
}

int main(int argc, char* argv[]) {
    int width = 60;
    int height = 30;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--help") == 0) {
            showHelp();
            return 0;
        } else if (strcmp(argv[i], "--width") == 0) {
            if (i + 1 < argc) {
                width = atoi(argv[++i]);
            }
        } else if (strcmp(argv[i], "--height") == 0) {
            if (i + 1 < argc) {
                height = atoi(argv[++i]);
            }
        } else {
            cerr << "Unknown option: " << argv[i] << "\n";
            showHelp();
            return 1;
        }
    }

    waitForAnyKey();

    Tetris game(width, height);
    game.run();

    return 0;
}

