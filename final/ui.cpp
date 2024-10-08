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
int mapNumber = 23;
void mapInit() {
	ifstream file("map/chapter1/" + to_string(mapNumber) + ".txt");
	 if (!file.is_open()) {
        // print error message and return
        cerr << "failed to open file" << endl;
    	}
	string line;
	
		for(int y = 0; y < mapY; y++){
			for(int x = 0; x < mapX; x++) {
				if (!map[y][x]) {
					file >> map[y][x];
				}
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
				newplayerY--; 
			break;
			case 'a': 
				newplayerX--; 
			break;	
			case 's': 
				newplayerY++; 
			break;
			case 'd': 
				newplayerX++; 
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
