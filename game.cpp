#include "game.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <random>
#include <chrono>
#include <thread> // Include this for std::this_thread

using namespace std;
namespace fs = std::filesystem;

Tetris::Tetris(int w, int h) : width(w), height(h) {
    initialize();
}

void Tetris::loadFigures(const std::string& directory) {
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
}

void Tetris::run() {
    while (true) {
        draw();
        update();

        this_thread::sleep_for(chrono::milliseconds(1000));
        clearScreen();
    }
}

void Tetris::draw() {
    cout << "Drawing screen..." << endl;
}

void Tetris::update() {
    cout << "Updating game state..." << endl;
}

void Tetris::clearScreen() {
    cout << "\033[2J\033[H";
}
