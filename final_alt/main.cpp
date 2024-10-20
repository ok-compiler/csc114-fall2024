#include <iostream>
#include <fstream> // allow file opening
#include <stdio.h> //allow inputs without pressing enter
#include <string>
using namespace std;

#include <mutex> // mutes threads so my map doesnt break
mutex mtx;

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
	lock_guard<mutex> lock(mtx);
	for(int y = 0; y < mapY; y++){ //for each mapY value
		for(int x = 0; x < mapX; x++){ // and then each mapX value
				if (x == mapX - 1 || x == 0) { // if x value is 0 or 99, set border
					map[y][x] = '#';
				}
				else if (y == mapY - 1 || y == 0) { // if y value is 0 or 99, set border
					map[y][x] = '#';
				}
				else if (map[y][x] != '#') {
					map[y][x] = ' ';
				}
		}
	}
}

//assigns next piece w/ "random" number generator
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
    		case 0: // i piece (cyan)
    			return 0;
    		break;
    		case 1: // L piece (blue)
    			pieceValue = 2;
    			return 1;
    		break;
    		case 2: // T piece (purple)
    			pieceValue = 2;
    			return 2;
    		break;
    		case 3: // J piece (orange)
    			return 3;
    		break;
    		case 4: // Z piece (green/lime)
    			return 4;
    		break;
    		case 5: // R piece (red)
    			return 5;
    		break;
    		case 6: // square piece (yellow)
    			return 6;
    		break;
    		
    	}
	return 0;
}

//clears console and prints new map
void printMap(){
	lock_guard<mutex> lock(mtx);
	string out;
	system("clear");
	string color;
	for(int y = 0; y < mapY; y++){ //for each mapX value
		for(int x = 0; x < mapX; x++){ // and then each mapY value
			color = map[y][x];
			if (map[y][x] == '#') out = "\033[107m" + color + "\033[0m";
			else if (map[y][x] == ' ') out = "\033[100m" + color + "\033[0m";
			else out = "\033[146m" + color + "\033[0m";
			if (x == mapX - 1) cout << out << endl;
			else cout << out;
		}
	}
}
void rotatePiece() {
	
}

void spawnNewPiece() {
	int newpieceX_spawn[4] = {10, 11, 12, 13};
	int newpieceY_spawn[4] = {2, 2, 2, 2};
	for(int i = 0; i < 4; i++) {
		pieceX[i] = newpieceX_spawn[i];
		pieceY[i] = newpieceY_spawn[i];
	}
}

//updates player position within map
void updatePiece(int init) {
	if (init == 0) {
		for(int i = 0; i < 4; i++) {
		map[pieceY[i]][pieceX[i]] = '@';
		}
		system("stty cooked");
		printMap();
		system("stty raw");
	}
	else {
	while(true) {
		for(int i = 0; i < 4; i++) {
			newpieceX[i] = pieceX[i];
			newpieceY[i] = pieceY[i];
		}
		wasd = getchar(); 
		switch(wasd) {
			case 'w': 
				exit(1);
			break;
			case 'a': 
				for(int i = 0; i < 4; i++) {
					newpieceX[i]--;
					if (map[newpieceY[i]][newpieceX[i]] != '#') { 
						collisionCheck++;
					}
				}
				if (collisionCheck == 4) {
					mapInit();
					for(int i = 0; i < 4; i++) {
						pieceX[i] = newpieceX[i];
						pieceY[i] = newpieceY[i];
						map[pieceY[i]][pieceX[i]] = '@';
						
					}
					system("stty cooked");
					printMap();
					system("stty raw");
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
					mapInit();
					for(int i = 0; i < 4; i++) {
						pieceX[i] = newpieceX[i];
						pieceY[i] = newpieceY[i];
						map[pieceY[i]][pieceX[i]] = '@';
					}
					system("stty cooked");
					printMap();
					system("stty raw");
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
					mapInit();
					for(int i = 0; i < 4; i++) {
						mapInit();
						pieceX[i] = newpieceX[i];
						pieceY[i] = newpieceY[i];
						map[pieceY[i]][pieceX[i]] = '@';
					}
					system("stty cooked");
					printMap();
					system("stty raw");
				}
			break;
			case '~':
				exit(1);
			break;
		}
		collisionCheck = 0;
		system("stty cooked");
	}
	}
}

void updatePos() {
	int collisionCheck_delay;
	while(true) {
	sleep_for(1s);
	for(int i = 0; i < 4; i++) {
		newpieceY[i] = pieceY[i];
	}
	for(int i = 0; i < 4; i++) {
		newpieceY[i]++;
		if (map[newpieceY[i]][pieceX[i]] != '#') { 
			collisionCheck_delay++;
		}
		else collisionCheck_delay--;
	}
	if (collisionCheck_delay >= 4) {
		mapInit();
		for(int i = 0; i < 4; i++) {
			pieceY[i] = newpieceY[i];
			map[pieceY[i]][pieceX[i]] = '@';
		}
		system("stty cooked");
		printMap();
		system("stty raw");
	}
	else {
		pieceValue = initPiece();
		for(int i = 0; i < 4; i++) {
			map[pieceY[i]][pieceX[i]] = '#';
		}
		spawnNewPiece();
	}
	collisionCheck_delay = 0;
	}
}



// main ui function (literally just executes all the other functions)
int main() {
	mapInit();
	updatePiece(0);
	thread(updatePos).detach();
	updatePiece(1);
	return 0;
}
