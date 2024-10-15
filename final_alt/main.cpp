#include <iostream>
#include <fstream> // allow file opening
#include <stdio.h> //allow inputs without pressing enter
#include <string>
using namespace std;

// time/sleep_for() stuff
#include <chrono>
#include <thread>
using namespace std::this_thread;
using namespace std::chrono_literals;
using std::chrono::system_clock;

// piece position (each individual squares, there's 4 squares per piece)
int pieceX[4] = {10, 11, 12, 13};
int pieceY[4] = {2, 2, 2, 2};
int newpieceX[4];
int newpieceY[4];
int pieceValue = 0;

// map values
const int mapX = 25;
const int mapY = 25;
char map[mapY][mapX];
int topOut = 0;
char wasd;


//initializes map
void mapInit() {
	for(int y = 0; y < mapY; y++){ //for each mapY value
		for(int x = 0; x < mapX; x++){ // and then each mapX value
			if (x == mapX - 1 || x == 0) { // if x value is 0 or 99, set border
				map[y][x] = '#';
			}
			else if (y == mapY - 1 || y == 0) { // if y value is 0 or 99, set border
				map[y][x] = '#';
			}
			else {
				map[y][x] = '.';
			}
		}
	}
}

//updates player position within map
void updatePiece(int init) {
	for(int i = 0; i < 4; i++) {
		newpieceX[i] = pieceX[i];
		newpieceY[i] = pieceY[i];
	}
	
	if (init == 0) {
		map[pieceY[0]][pieceX[0]] = '@';
		map[pieceY[1]][pieceX[1]] = '@';
		map[pieceY[2]][pieceX[2]] = '@';
		map[pieceY[3]][pieceX[3]] = '@';
		
	}
	/*else {
		if (wasd != '~') system("stty raw"); 
		wasd = getchar(); 
		switch(wasd) {
			case 'w': 
				if (newplayerY == 0) {
					newm = true;
					newplayerY = 24;
					locY++;
					mapInit();
				}
				else {
					newm = false;
					newplayerY--;
				}
			break;
			case 'a': 
				if (newplayerX == 0) {
					newm = true;
					newplayerX = 49;
					locX--;
					mapInit();
				}
				else {
					newm = false;
					newplayerX--; 
				}
			break;	
			case 's': 
				if (newplayerY == 24) {
					newm = true;
					newplayerY = 0;
					locY--;
					mapInit();
				}
				else {
					newm = false;
					newplayerY++; 
				}
			break;
			case 'd': 
				if (newplayerX == 49) {
					newm = true;
					newplayerX = 0;
					locX++;
					mapInit();
				}
				else {
					newm = false;
					newplayerX++;
				} 
			break;
			case '~':
			system("stty cooked");
			break;
		}
		system("stty cooked");
		if (map[newplayerY][newplayerX] != '#') {
			
			playerX = newplayerX;
			playerY = newplayerY;
			map[playerY][playerX] = '@';
		} else map[playerY][playerX] = '@';
	}*/
}

void updatePos() {
	for(int i = 0; i < 4; i++){
		//pieceY[i];
	}
}


//initializes next piece w/ "random" number generator
int initPiece() {
	auto time = system_clock::now().time_since_epoch() / 1ns;
	cout << time << endl;
	time ^= time << 13;
    	time ^= time >> 17;
    	time ^= time << 5;
    	time ^= time << 9;
    	cout << time << endl;
    	time %= 7;
    	switch(abs(time)) {
    		case 0:
    			std::cout << "T piece" << std::endl;
    			return 0;
    		break;
    		case 1:
    			std::cout << "L piece" << std::endl;
    			return 1;
    		break;
    		case 2:
    			std::cout << "I piece" << std::endl;
    			return 2;
    		break;
    		case 3:
    			std::cout << "J piece" << std::endl;
    			return 3;
    		break;
    		case 4:
    			std::cout << "Z piece" << std::endl;
    			return 4;
    		break;
    		case 5:
    			std::cout << "R piece" << std::endl;
    			return 5;
    		break;
    		case 6:
    			std::cout << "square piece" << std::endl;
    			return 6;
    		break;
    		
    	}
	return 0;
}

//clears console and prints map output
void printMap(){
	system("clear");
	for(int y = 0; y < mapY; y++){ //for each mapX value
		for(int x = 0; x < mapX; x++){ // and then each mapY value
			if (x == mapX - 1) std::cout << map[y][x] << std::endl;
			else std::cout << map[y][x];
		}
	}
}

// main ui function (literally just executes all the other functions)
int main() {
	mapInit();
	updatePiece(0);
	printMap();
	while(true) {
		mapInit();
		updatePos();
		printMap();
		pieceValue = initPiece();
		updatePiece(0);
		sleep_for(1s);
	}
	return 0;
}
