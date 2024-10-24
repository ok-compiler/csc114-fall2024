#include "map.h"
#include <iostream>
#include <stdio.h> 
#include <string>
using namespace std;
#include <mutex>

#include <chrono>
#include <thread>
using namespace std::this_thread;
using namespace std::chrono_literals;
using std::chrono::system_clock;


int score = 0;
const int mapX = 12;
const int mapY = 22;
char map[mapY][mapX];
int color[mapY][mapX];

void mapInit() {
    for (int y = 0; y < mapY; y++) {
        for (int x = 0; x < mapX; x++) {
            if (x == mapX - 1 || x == 0 || y == mapY - 1 || y == 0) {
                map[y][x] = '#';
                color[y][x] = 7;
            } else if (map[y][x] != '#') {
                map[y][x] = ' ';
                color[y][x] = 8;
            }
        }
    }
}

void checkColor(int a, char b) {
    string c = string(&b, &b + 1);
    switch (a) {
        case 0: cout << "\033[106m" + c + "\033[0m"; break;
        case 1: cout << "\033[44m" + c + "\033[0m"; break;
        case 2: cout << "\033[45m" + c + "\033[0m"; break;
        case 3: cout << "\033[43m" + c + "\033[0m"; break;
        case 4: cout << "\033[102m" + c + "\033[0m"; break;
        case 5: cout << "\033[41m" + c + "\033[0m"; break;
        case 6: cout << "\033[103m" + c + "\033[0m"; break;
        case 7: cout << "\033[107m" + c + "\033[0m"; break;
        case 8: cout << "\033[100m" + c + "\033[0m"; break;
        default: cerr << "error" << endl;
    }
}

void printMap() {
    lock_guard<mutex> lock(mtx);
    system("clear");
    system("stty cooked");
    for (int y = 0; y < mapY; y++) {
        for (int x = 0; x < mapX; x++) {
            checkColor(color[y][x], map[y][x]);
            if (x == mapX - 1) cout << "\033[0m" << endl;
        }
    }
    cout << "Score: " << score << endl;
    cout << "next piece: " << nextPiece << endl;
    system("stty raw");
}

void lineClear() {
    int collisionCheck_clear = 0;
    int lineClears = 0;
    for (int y = 0; y < mapY; y++) {
        for (int x = 0; x < mapX; x++) {
            if (map[y][x] == '#' && y != 0 && y != mapY - 1) collisionCheck_clear++;
        }
        if (collisionCheck_clear == mapX) {
            lineClears++;
            for (int row = y; row > 1; row--) {
                for (int col = 1; col < mapX - 1; col++) {
                    map[row][col] = map[row - 1][col];
                    color[row][col] = color[row - 1][col];
                }
            }
            for (int col = 1; col < mapX - 1; col++) {
                map[1][col] = ' ';
                color[1][col] = 8;
            }
        }
        collisionCheck_clear = 0;
    }
    switch (lineClears) {
        case 1: score += 40; break;
        case 2: score += 100; break;
        case 3: score += 300; break;
        case 4: score += 1200; break;
    }
}

