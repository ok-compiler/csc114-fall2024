#include <iostream>
#include <fstream> // allow file opening
#include <stdio.h> //allow inputs without pressing enter
#include <string>
#include "engine.h" // game engine file
//#include "info.h" // info/data for enemies, items, buffs, etc
using namespace std;

// time/sleep_for() stuff
#include <chrono>
#include <thread>
using namespace std::this_thread;
using namespace std::chrono_literals;
using std::chrono::system_clock;

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
bool newm;

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
	}
}

void printMap(){
	char minimap[5][5];

	for (int y = 0; y < 5; y++) {
        	for (int x = 0; x < 5; x++) {
			minimap[y][x] = ' '; 
        	}
   	}

	if (locX >= 0 && locX < 5 && locY >= 0 && locY < 5) {
		minimap[locY][locX] = 'P'; 
 	}
	system("clear");
    for (int y = 0; y < mapY; y++) { 
        for (int x = 0; x < mapX; x++) { 
            if (x == mapX - 1) {
           	 if (y == 0){
            		cout << map[y][x];
            		cout << "\t\tMinimap:" << endl;	
            	}
            	else if (y < 5 && y > 0) {
            	int newY = 5-y-1;
            	cout << map[y][x];
            		cout << "\t\t";	
        for (int i = 0; i < 5; i++) {
            if (minimap[newY][i] == 'P') {
                cout << "\033[42m" << minimap[newY][i] << "\033[0m"; 
            } else {
                cout << "\033[44m" << minimap[newY][i] << "\033[0m"; 
            }
        } 
        cout << endl;
            	} else cout << map[y][x] << endl;
            }
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
