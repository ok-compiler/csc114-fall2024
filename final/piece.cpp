#include "piece.h"
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

int pieceX[4] = {4, 5, 6, 7};
int pieceY[4] = {1, 1, 1, 1};
int newpieceX_spawn[4] = {4, 5, 6, 7};
int newpieceY_spawn[4] = {1, 1, 1, 1};
int newpieceX_spawn_copy[4] = {4, 5, 6, 7};
int newpieceY_spawn_copy[4] = {1, 1, 1, 1};
int newpieceX[4], newpieceY[4];

int pieceValue = 0;
int nextPiece = 1;
int pieceBank[7] = {0, -1, 2, 3, 4, 5, 6};
bool spawnNew = true;
int collisionCheck = 0;
char wasd;

void rotatePiece(bool clockwise) {
    int collisionCheck_rotation = 0;
    int pivotX = pieceX[1];
    int pivotY = pieceY[1];
    int newpieceX_rotation[4];
    int newpieceY_rotation[4];

    for (int i = 0; i < 4; i++) {
        if (clockwise) {
            newpieceX_rotation[i] = pivotX - (pieceY[i] - pivotY);
            newpieceY_rotation[i] = pivotY + (pieceX[i] - pivotX);
        } else {
            newpieceX_rotation[i] = pivotX + (pieceY[i] - pivotY);
            newpieceY_rotation[i] = pivotY - (pieceX[i] - pivotX);
        }
    }

    for (int i = 0; i < 4; i++) {
        if (map[newpieceY_rotation[i]][newpieceX_rotation[i]] != '#') {
            collisionCheck_rotation++;
        }
    }

    if (collisionCheck_rotation >= 4) {
        for (int i = 0; i < 4; i++) {
            pieceX[i] = newpieceX_rotation[i];
            pieceY[i] = newpieceY_rotation[i];
        }
    }
}

void gameOver() {
	//system("clear");
	system("stty cooked");
	system("gsettings reset org.gnome.desktop.interface monospace-font-name");
	cout << R"( ░▒▓██████▓▒░ ░▒▓██████▓▒░░▒▓██████████████▓▒░░▒▓████████▓▒░       ░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓████████▓▒░▒▓███████▓▒░  )" << endl;
	sleep_for(500ms);
	cout << R"(░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░             ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░ )" << endl;
	sleep_for(500ms);
	cout << R"(░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░             ░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒▒▓█▓▒░░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░ )" << endl;
	sleep_for(500ms);
	cout << R"(░▒▓█▓▒▒▓███▓▒░▒▓████████▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓██████▓▒░        ░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒▒▓█▓▒░░▒▓██████▓▒░ ░▒▓███████▓▒░  )" << endl;
	sleep_for(500ms);
	cout << R"(░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░             ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▓█▓▒░ ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░ )" << endl;
	sleep_for(500ms);
	cout << R"(░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░             ░▒▓█▓▒░░▒▓█▓▒░ ░▒▓█▓▓█▓▒░ ░▒▓█▓▒░      ░▒▓█▓▒░░▒▓█▓▒░ )" << endl;
	sleep_for(500ms);
	cout << R"( ░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓████████▓▒░       ░▒▓██████▓▒░   ░▒▓██▓▒░  ░▒▓████████▓▒░▒▓█▓▒░░▒▓█▓▒░ )" << endl;
	sleep_for(500ms);
	cout << "\nwomp womp lol" << endl;
	sleep_for(1s);
	system("stty cooked");
}

void initPiece() {
	while (spawnNew) {
		nextPiece = rand() % 7; //new random int
		if (nextPiece != pieceBank[nextPiece]) spawnNew = true; // if used, restart
		else  {
			spawnNew = false;
			pieceBank[nextPiece] = -1;
			for (int i = 0; i < 7; i++) {
				if (pieceBank[i] != -1) break; //check if all slots are used
				else if (i == 6) { // if they are, reset array
					for (int i = 0; i < 7; i++) {
						pieceBank[i] = i;
					}
				}
			}	
		}
	}
	spawnNew = true;
}

void spawnNewPiece() {
	pieceValue = nextPiece;
	initPiece();
	//lock_guard<mutex> lock(mtx);
	switch(pieceValue) { // dont need i piece since its default 
		case 1: // L piece (blue)
   			newpieceX_spawn[0]++;
			newpieceY_spawn[0]++;
    		break;
    		case 2: // T piece (purple)
    			newpieceX_spawn[0]++;
    			newpieceX_spawn[2]--;
    			newpieceX_spawn[3]--;
    			newpieceY_spawn[1]++;
    			newpieceY_spawn[2] += 2;
    			newpieceY_spawn[3]++;
    		break;
    		case 3: // J piece (orange)
    			newpieceX_spawn[3]--;
    			newpieceY_spawn[3]++;
    		break;
    		case 4: // Z piece (green/lime)
    			newpieceX_spawn[2]--;
    			newpieceX_spawn[3]--;
    			newpieceY_spawn[2]++;
    			newpieceY_spawn[3]++;
    		break;
    		case 5: // R piece (red)
    			newpieceX_spawn[2]--;
    			newpieceX_spawn[3]--;
    			newpieceY_spawn[0]++;
    			newpieceY_spawn[1]++;
    		break;
    		case 6: // square piece (yellow)
    			newpieceX_spawn[0]++;
    			newpieceX_spawn[3]--;
    			newpieceY_spawn[1]++;
    			newpieceY_spawn[3]++;
    		break;
    		default: cerr << "error" << endl;
    	}
   	for(int i = 0; i < 4; i++) {
		pieceX[i] = newpieceX_spawn[i];
		pieceY[i] = newpieceY_spawn[i];
		newpieceY[i] = pieceY[i];
		newpieceX[i] = pieceX[i];		
		newpieceY_spawn[i] = newpieceY_spawn_copy[i];
		newpieceX_spawn[i] = newpieceX_spawn_copy[i];
		color[pieceY[i]][pieceX[i]] = pieceValue;
	}
}

void updatePiece(int init) {
	if (init == 0) {
		{
			lock_guard<mutex> lock(mtx);
			for(int i = 0; i < 4; i++) {
				map[pieceY[i]][pieceX[i]] = '@';
				color[pieceY[i]][pieceX[i]] = pieceValue;
			}
		}
		printMap();
	}
	else {
	while(true) {
		system("stty raw");
		{
			lock_guard<mutex> lock(mtx);
			for(int i = 0; i < 4; i++) {
				newpieceX[i] = pieceX[i];
				newpieceY[i] = pieceY[i];
			}
		}
		wasd = getchar(); 
		switch(wasd) {
			case 'w': 
				rotatePiece(true);
				printMap();
			break;
			case 'e': 
				rotatePiece(false);
				printMap();
			break;
			case 'a': 
				for(int i = 0; i < 4; i++) {
					newpieceX[i]--;
					if (map[newpieceY[i]][newpieceX[i]] != '#') { 
						collisionCheck++;
					}
				}
				if (collisionCheck == 4) {
						//lock_guard<mutex> lock(mtx);
						mapInit();
						for(int i = 0; i < 4; i++) {
							pieceX[i] = newpieceX[i];
							pieceY[i] = newpieceY[i];
							map[pieceY[i]][pieceX[i]] = '@';
							color[pieceY[i]][pieceX[i]] = pieceValue;
						}
						printMap();
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
						//lock_guard<mutex> lock(mtx);
						mapInit();
						for(int i = 0; i < 4; i++) {
							pieceX[i] = newpieceX[i];
							pieceY[i] = newpieceY[i];
							map[pieceY[i]][pieceX[i]] = '@';
							color[pieceY[i]][pieceX[i]] = pieceValue;
						}
						printMap();
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
					//lock_guard<mutex> lock(mtx);
					mapInit();
					for(int i = 0; i < 4; i++) {
						pieceX[i] = newpieceX[i];
						pieceY[i] = newpieceY[i];
						map[pieceY[i]][pieceX[i]] = '@';
						color[pieceY[i]][pieceX[i]] = pieceValue;
					}
					printMap();
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
	srand(time(0));
	int collisionCheck_delay;
	while(true) {
	{
	lock_guard<mutex> lock(mtx);
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
	}
	if (collisionCheck_delay >= 4) {
		mapInit();
		{
		lock_guard<mutex> lock(mtx);
		for(int i = 0; i < 4; i++) {
			pieceY[i] = newpieceY[i];
			map[pieceY[i]][pieceX[i]] = '@';
			color[pieceY[i]][pieceX[i]] = pieceValue;
		}
		}
		printMap();
	}
	else {
		for(int i = 0; i < 4; i++) {
			map[pieceY[i]][pieceX[i]] = '#';
			if (pieceY[i] == 1) {
				gameOver(); // if topout, game over (womp womp)
				exit(0);
			}
		}
		lineClear();
		spawnNewPiece();
		printMap();
		
	}
	collisionCheck_delay = 0;
	sleep_for(500ms);
	}
}

