#include <iostream>
#include <fstream>
#include <string>
#include "engine.h" // game engine file
//#include "info.h" // info/data for enemies, items, buffs, etc
using namespace std;

// player pos
int playerX = 23;
int playerY = 13;

// map values
const int mapX = 50;
const int mapY = 25;
char map[mapY][mapX]; // map interface
int inBattle = 0;
char wasd;
int locX = 2;
int locY = 0;

void mapInit() {
	cout << locX << locY << endl;
	ifstream file("map/chapter1/" + to_string(locX) + to_string(locY) + ".txt");
	 if (!file.is_open()) {
        // print error message and return
        cerr << "failed to open file" << endl;
    	}
	string line;
	
		for(int y = 0; y < mapY; y++){
			for(int x = 0; x < mapX; x++) {
					file >> map[y][x];
			}
		}
	file.close();
}

void updatePlayer(int init) {
	int newplayerX = playerX;
	int newplayerY = playerY;
	if (init == 0) {
		map[playerY][playerX] = '@';
	}
	else {
		cin >> wasd;
		switch(wasd) {
			case 'w': 
				if (newplayerY == 0) {
					newplayerY = 24;
					locY++;
					mapInit();
				}
				else newplayerY--; 
			break;
			case 'a': 
				if (newplayerX == 0) {
					newplayerX = 49;
					locX--;
					mapInit();
				}
				else newplayerX--; 
			break;	
			case 's': 
				if (newplayerY == 24) {
					newplayerY = 0;
					locY--;
					mapInit();
				}
				else newplayerY++; 
			break;
			case 'd': 
				if (newplayerX == 49) {
					newplayerX = 0;
					locX++;
					mapInit();
				}
				else newplayerX++; 
			break;
		}
		if (map[newplayerY][newplayerX] != '#') {
		map[playerY][playerX] = '.';
		map[newplayerY][newplayerX] = '@';
		playerX = newplayerX;
		playerY = newplayerY;
		}
	}
}

void printMap(){
	system("clear");
	for(int y = 0; y < mapY; y++){ //for each mapX value
		for(int x = 0; x < mapX; x++){ // and then each mapY value
			if (x == mapX - 1) cout << map[y][x] << endl;
			else cout << map[y][x];
		}
	}
}

int ui() {
	mapInit();
	updatePlayer(0);
	printMap();
	while(true) {
		mapInit();
		updatePlayer(1);
		printMap();
	}
	return 0;
}
