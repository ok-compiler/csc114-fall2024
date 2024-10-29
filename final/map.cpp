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


int score = 0;
const int mapX = 12;
const int mapY = 22;
char map[mapY][mapX];
int color[mapY][mapX];
int nextPiecePrint[7][2][4] = { 
{{'@', '@', '@', '@'}, {' ', ' ', ' ', ' '}}, // I piece
{{'@', '@', '@', ' '}, {'@', ' ', ' ', ' '}}, // L piece
{{'@', '@', '@', ' '}, {' ', '@', ' ', ' '}}, // T piece
{{'@', '@', '@', ' '}, {' ', ' ', '@', ' '}}, // J piece
{{'@', '@', ' ', ' '}, {' ', '@', '@', ' '}}, // Z piece
{{' ', '@', '@', ' '}, {'@', '@', ' ', ' '}}, // R piece
{{'@', '@', ' ', ' '}, {'@', '@', ' ', ' '}} // square piece
};


void mapInit() {
    for (int y = 0; y < mapY; y++) {
        for (int x = 0; x < mapX; x++) {
            if (x == mapX - 1 || x == 0 || y == mapY - 1 || y == 0) {
                map[y][x] = '#';
                color[y][x] = 7;
            } else if (map[y][x] != '#') {
                map[y][x] = ' ';
                color[y][x] = 8;
            }
        }
    }
}

void checkColor(int a, char b) {
    string c = string(&b, &b + 1);
    switch (a) {
        case 0: cout << "\033[106m" + c + "\033[0m"; break;
        case 1: cout << "\033[44m" + c + "\033[0m"; break;
        case 2: cout << "\033[45m" + c + "\033[0m"; break;
        case 3: cout << "\033[43m" + c + "\033[0m"; break;
        case 4: cout << "\033[102m" + c + "\033[0m"; break;
        case 5: cout << "\033[41m" + c + "\033[0m"; break;
        case 6: cout << "\033[103m" + c + "\033[0m"; break;
        case 7: cout << "\033[107m" + c + "\033[0m"; break;
        case 8: cout << "\033[100m" + c + "\033[0m"; break;
        default: cerr << "error" << endl;
    }
}

void printMap() {
    lock_guard<mutex> lock(mtx);
    system("clear");
    system("stty cooked");
    for (int y = 0; y < mapY; y++) {
        for (int x = 0; x < mapX; x++) {
            checkColor(color[y][x], map[y][x]);
            if (x == mapX - 1) {
            	switch (y){ // displays on right side of map
            		case 0:
            			for (int i = 0; i < 13; i++) {
            				checkColor(7, '#');
            			}
            			cout << endl;
            		break;
            		case 1: 
            			cout << "Score: " << score; 
            			cout << "    ";
    	     	   		checkColor(7, '#');
    	     	   		cout  << endl;
            		break;
    	     		case 2: 
    	     			cout << "Next Piece: ";
    	     	 	  	checkColor(7, '#');
    	     	   		cout  << endl; 
    	     	   	break;
    	     	   	case 3:
    	     	   		cout << "\t\t";
    	     	   		checkColor(7, '#');
    	     	   		cout  << endl;
    	     	   	break;
    	     	   	case 4: 
    	     	   		cout << "\t";
    	     	   		for (int i = 0; i < 4; i++) {
    	     	   			if (nextPiecePrint[nextPiece][0][i] == '@') checkColor(nextPiece, nextPiecePrint[nextPiece][0][i]);
    	     	  			else cout << string(&nextPiecePrint[nextPiece][0][i], &nextPiecePrint[nextPiece][0][i] + 1);
    	     	   		}
    	     	   		cout << "    ";
    	     	   		checkColor(7, '#');
    	     	   		cout << endl;
    	     	   	break;
    	     	   	case 5:
    	     	   		cout << "\t";
    	     	   		for (int i = 0; i < 4; i++) {
    	     	   			if (nextPiecePrint[nextPiece][1][i] == '@') checkColor(nextPiece, nextPiecePrint[nextPiece][1][i]);
    	     	   			else cout << string(&nextPiecePrint[nextPiece][1][i], &nextPiecePrint[nextPiece][1][i] + 1);
    	     	   		}
    	     	   		cout << "    ";
    	     	   		checkColor(7, '#');
    	     	   		cout  << endl;
    	     	   	break;
    	     	   	case 6:
    	     	   		cout << "\t\t";
    	     	   		checkColor(7, '#');
    	     	   		cout  << endl;
    	     	   	break;
    	     	   	case 7:
            			for (int i = 0; i < 13; i++) {
            				checkColor(7, '#');
            			}
            			cout << endl;
            		break;
            		case 8:
            			cout << "Controls:\t";
            			checkColor(7, '#');
    	     	   		cout  << endl;
            		break;
            		case 9:
            			cout << "A: Left\t";
            			checkColor(7, '#');
    	     	   		cout  << endl;
            		break;
            		case 10:
            			cout << "S: Down\t";
            			checkColor(7, '#');
    	     	   		cout  << endl;
            		break;
            		case 11:
            			cout << "D: Right\t";
            			checkColor(7, '#');
    	     	   		cout  << endl;
            		break;
            		case 12:
            			cout << "W: Rotate(R)";
            			checkColor(7, '#');
    	     	   		cout  << endl;
            		break;
            		case 13:
            			cout << "E: Rotate(L)";
            			checkColor(7, '#');
    	     	   		cout  << endl;
            		break;
            		case 14:
            			cout << "~: Exit\t";
            			checkColor(7, '#');
    	     	   		cout  << endl;
            		break;
            		case 15:
            			for (int i = 0; i < 13; i++) {
            				checkColor(7, '#');
            			}
            			cout << endl;
            		break;
            		case 16:
            			cout << "Made by:\t";
            			checkColor(7, '#');
            			cout << endl;
            		break;
            		case 17:
            			cout << "Owen Webster";
            			checkColor(7, '#');
            			cout << endl;
            		break;
            		case 18:
            			cout << "\t\t";
            			checkColor(7, '#');
            			cout << endl;
            		break;
            		case 19:
            			cout << "CSC114 Final";
            			checkColor(7, '#');
            			cout << endl;
            		break;
            		case 20:
            			cout << "enjoy :)\t";
            			checkColor(7, '#');
            			cout << endl;
            		break;
            		case 21:
            			for (int i = 0; i < 13; i++) {
            				checkColor(7, '#');
            			}
            			cout << endl;
            			cout << "to reset font: run \"sh resetFont.txt\" :)" << endl;
            		break;
    	      	 	default: cout << endl; break;
            	}
            }
    	}
    }
    //cout << "Controls:\n~: Quit\ta: move left\ts: move down\td: move right\tw: rotate clockwise\te: rotate counterclockwise";
    system("stty raw");
}

void lineClear() {
    int collisionCheck_clear = 0;
    int lineClears = 0;
    for (int y = 0; y < mapY; y++) {
        for (int x = 0; x < mapX; x++) {
            if (map[y][x] == '#' && y != 0 && y != mapY - 1) collisionCheck_clear++;
        }
        if (collisionCheck_clear == mapX) {
            lineClears++;
            for (int row = y; row > 1; row--) {
                for (int col = 1; col < mapX - 1; col++) {
                    map[row][col] = map[row - 1][col];
                    color[row][col] = color[row - 1][col];
                }
            }
            for (int col = 1; col < mapX - 1; col++) {
                map[1][col] = ' ';
                color[1][col] = 8;
            }
        }
        collisionCheck_clear = 0;
    }
    switch (lineClears) {
        case 1: score += 40; break;
        case 2: score += 100; break;
        case 3: score += 300; break;
        case 4: score += 1200; break;
    }
}

