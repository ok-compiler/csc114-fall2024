#include <iostream>
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
				playerY--; 
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
		playerX = newplayerX;
		playerY = newplayerY;
		}
		map[playerY][playerX] = '@';
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
