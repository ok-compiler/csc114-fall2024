#include <iostream>
#include <stdio.h>
#include "engine.h" // game engine file
//#include "info.h" // info/data for enemies, items, buffs, etc
using namespace std;
char input;
int main() {
 //ui();
	title_screen();
	cout << "Type the number for the corresponding option:\n1 - Continue\n2 - New Game" << endl;
	while (!input) {
		system("stty raw"); 
    			input = getchar(); 
 		system("stty cooked"); 
		switch (input) {
		case '1':
			ui();
			//cout << "placeholder" << endl;
			break;
		case '2': 
			system("clear");
			opening_monologue();
			break;
		default:
			cout << "Invalid input | Try Again" << endl;
			input = '\0';
			cout << input << endl;
			break;
		}
	}
	return 0;
}
