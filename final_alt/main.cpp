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

//multithreading stuff so everything doesnt break
#include <thread>
#include <mutex>
mutex mtx;

// piece position (each individual squares, there's 4 squares per piece)
int pieceX[4] = {10, 11, 12, 13};
int pieceY[4] = {2, 2, 2, 2};
int newpieceX[4];
int newpieceY[4];
int newpieceY_delay[4];
int pieceValue = 0;
int collisionCheck;

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
    			cout << "T piece" << endl;
    			return 0;
    		break;
    		case 1:
    			cout << "L piece" << endl;
    			return 1;
    		break;
    		case 2:
    			cout << "I piece" << std::endl;
    			return 2;
    		break;
    		case 3:
    			cout << "J piece" << endl;
    			return 3;
    		break;
    		case 4:
    			cout << "Z piece" << endl;
    			return 4;
    		break;
    		case 5:
    			cout << "R piece" << endl;
    			return 5;
    		break;
    		case 6:
    			cout << "square piece" << endl;
    			return 6;
    		break;
    		
    	}
	return 0;
}

//clears console and prints new map
void printMap(){
	system("clear");
	for(int y = 0; y < mapY; y++){ //for each mapX value
		for(int x = 0; x < mapX; x++){ // and then each mapY value
			if (x == mapX - 1) cout << map[y][x] << endl;
			else cout << map[y][x];
		}
	}
}

//updates player position within map
void updatePiece(int init) {
	lock_guard<mutex> lock(mtx);
	for(int i = 0; i < 4; i++) {
		newpieceX[i] = pieceX[i];
		newpieceY[i] = pieceY[i];
	}
	
	if (init == 0) {
		for(int i = 0; i < 4; i++) {
		map[pieceY[i]][pieceX[i]] = '@';
		}
	}
	else {
		while(true) {
			mapInit();
			pieceValue = initPiece();
		if (wasd != '~') system("stty raw"); 
		wasd = getchar(); 
		switch(wasd) {
			case 'w': 
				
			break;
			case 'a': 
				for(int i = 0; i < 4; i++) {
					newpieceX[i]--;
					if (map[newpieceY[i]][newpieceX[i]] != '#') { 
						collisionCheck++;
					}
				}
				if (collisionCheck == 4) {
					for(int i = 0; i < 4; i++) {
						pieceX[i] = newpieceX[i];
						pieceY[i] = newpieceY[i];
						map[pieceY[i]][pieceX[i]] = '@';
						printMap();
					}
				}
			break;	
			case 's': 
				for(int i = 0; i < 4; i++) {
					newpieceY[i]++;
					if (map[newpieceY[i]][newpieceX[i]] != '#') { 
						collisionCheck++;
					}
				}
				if (collisionCheck == 4) {
					for(int i = 0; i < 4; i++) {
						pieceX[i] = newpieceX[i];
						pieceY[i] = newpieceY[i];
						map[pieceY[i]][pieceX[i]] = '@';
						printMap();
					}
				}
			break;
			case 'd': 
				for(int i = 0; i < 4; i++) {
					newpieceX[i]++;
					if (map[newpieceY[i]][newpieceX[i]] != '#') { 
						collisionCheck++;
					}
				}
				if (collisionCheck == 4) {
					for(int i = 0; i < 4; i++) {
						pieceX[i] = newpieceX[i];
						pieceY[i] = newpieceY[i];
						map[pieceY[i]][pieceX[i]] = '@';
						printMap();
					}
				}
			break;
			case '~':
			system("stty cooked");
			break;
		}
		collisionCheck = 0;
		system("stty cooked");
		}
	}
}

void updatePos() {
	lock_guard<mutex> lock(mtx);
	int collisionCheck_delay;
	while(true) {
	for(int i = 0; i < 4; i++) {
		newpieceY_delay[i] = pieceY[i];
	}
	for(int i = 0; i < 4; i++) {
		newpieceY_delay[i]++;
		if (map[newpieceY_delay[i]][pieceX[i]] != '#') { 
			collisionCheck_delay++;
		}
	}
	if (collisionCheck_delay == 4) {
		for(int i = 0; i < 4; i++) {
			map[pieceY[i]][pieceX[i]] = '.';
			pieceY[i] = newpieceY_delay[i];
			map[pieceY[i]][pieceX[i]] = '@';
		}
	}
	collisionCheck_delay = 0;
	sleep_for(1s);
	printMap();
	}
}



// main ui function (literally just executes all the other functions)
int main() {
	mapInit();
	updatePiece(0);
	printMap();
	thread(updatePos).detach();
	updatePiece(1);
	return 0;
}
