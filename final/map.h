#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <mutex>
#include <stdio.h>
#include <thread>
#include <chrono>

extern const int mapX, mapY;
extern char map[22][12];
extern int color[22][12];
extern std::mutex mtx;
extern int score;
extern int pieceX[4], pieceY[4];
extern int pieceValue;
extern char wasd;

void mapInit();
void checkColor(int a, char b);
void printMap();
void lineClear();

#endif

