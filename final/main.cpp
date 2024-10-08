#include <iostream>
#include "engine.h" // game engine file
//#include "info.h" // info/data for enemies, items, buffs, etc
using namespace std;
int title_input = -1;
int main() {
ui();
/*
	title_screen();
	cout << "Type the number for the corresponding option:\n1 - Continue\n2 - New Game" << endl;
	while (title_input == -1) {
		cin >> title_input;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(); 
		}
		switch (title_input) {
		case 1:
			cout << "placeholder" << endl;
			break;
		case 2: 
			system("clear");
			opening_monologue();
			break;
		default:
			cout << "Invalid input | Try Again" << endl;
			title_input = -1;
			break;
		}
	}*/
	return 0;
}
