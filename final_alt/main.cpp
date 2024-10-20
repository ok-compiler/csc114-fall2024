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
int pieceX[4] = {4, 5, 6, 7};
int pieceY[4] = {1, 1, 1, 1};
int newpieceX_spawn[4] = {4, 5, 6, 7};
int newpieceY_spawn[4] = {1, 1, 1, 1};
int newpieceX_spawn_copy[4] = {4, 5, 6, 7};
int newpieceY_spawn_copy[4] = {1, 1, 1, 1};
int newpieceX[4], newpieceY[4], newpieceY_delay[4];
int pieceValue = 0;
int collisionCheck;

// map values
const int mapX = 12;
const int mapY = 22;
char map[mapY][mapX];
int color[mapY][mapX];
bool topOut = false;
char wasd;


//initializes map
void mapInit() {
	for(int y = 0; y < mapY; y++){ //for each mapY value
		for(int x = 0; x < mapX; x++){ // and then each mapX value
				if (x == mapX - 1 || x == 0) { // if x value is 0 or 99, set border
					map[y][x] = '#';
					color[y][x] = 7;
				}
				else if (y == mapY - 1 || y == 0) { // if y value is 0 or 99, set border
					map[y][x] = '#';
					color[y][x] = 7;
				}
				else if (map[y][x] != '#') {
					map[y][x] = ' ';
					color[y][x] = 8;
				}
		}
	}
}

//assigns next piece w/ "random" number generator
void initPiece() {
	auto time = system_clock::now().time_since_epoch() / 1ns;
	cout << time << endl;
	time ^= time << 13;
    	time ^= time >> 17;
    	time ^= time << 5;
    	time ^= time << 9;
    	cout << time << endl;
    	time %= 7;
	pieceValue = abs(time);
}

void checkColor(int a, char b) {
	string c = string(&b, &b + 1);
	switch (a) { // check color number
		case 0: // I piece (cyan)
			cout << "\033[106m" + c + "\033[0m";
		break;
		case 1: // L piece (blue)
   			cout << "\033[44m" + c + "\033[0m";
    		break;
    		case 2: // T piece (purple)
    			cout << "\033[45m" + c + "\033[0m";
    		break;
    		case 3: // J piece (orange)
    			cout << "\033[43m" + c + "\033[0m";
    		break;
    		case 4: // Z piece (green/lime)
    			cout << "\033[102m" + c + "\033[0m";
    		break;
    		case 5: // R piece (red)
    			cout << "\033[41m" + c + "\033[0m";
    		break;
    		case 6: // square piece (yellow)
    			cout << "\033[103m" + c + "\033[0m";
    		break;
		case 7: // white
			cout << "\033[107m" + c + "\033[0m";
		break;
		case 8: // gray
			cout << "\033[100m" + c + "\033[0m";
		break;
		default: cerr << "error" << endl;
	}
}

//clears console and prints new map
void printMap(){
	lock_guard<mutex> lock(mtx);
	string out;
	system("clear");
	system("stty cooked");
	cout << pieceValue << endl;
	for(int y = 0; y < mapY; y++){ //for each mapX value
		for(int x = 0; x < mapX; x++){ // and then each mapY value
			checkColor(color[y][x], map[y][x]);
			if (x == mapX - 1) cout << "\033[0m" << endl;
		}
	}
	system("stty raw");
}

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
		
	bool validRotation = true;
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
	//}
}

void spawnNewPiece() {
	lock_guard<mutex> lock(mtx);
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
    			newpieceY_spawn[0]++;
    			newpieceY_spawn[1]++;
    		break;
    		case 5: // R piece (red)
    			newpieceX_spawn[2]--;
    			newpieceX_spawn[3]--;
    			newpieceY_spawn[2]++;
    			newpieceY_spawn[3]++;
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
	//mapInit();
}

//updates player position within map
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
		initPiece();
		for(int i = 0; i < 4; i++) {
			map[pieceY[i]][pieceX[i]] = '#';
		}
		spawnNewPiece();
	}
	collisionCheck_delay = 0;
	sleep_for(1s);
	}
}



// main ui function (literally just executes all the other functions)
int main() {
	//system("gsettings set org.gnome.desktop.interface monospace-font-name 'Crisp 12'");
	mapInit();
	updatePiece(0);
	
	thread t1(updatePos);
	thread t2(updatePiece, 1);
	
	t1.join();
	t2.join();
	return 0;
}
