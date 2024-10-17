#include <iostream>
#include <string>

using namespace std;

string x;
bool quit = false;
int main() {
	while (!quit) {
		cout << "enter an input:" << endl;
		cin >> x;
		if (x == "rock") {
			cout << "paper! you lose LLLLLLLL" << endl;
		}
		else if (x == "paper") {
			cout << "scissors! you lose LLLLLLLL" << endl;
		}
		else if (x == "scissors") {
			cout << "rock! you lose LLLLLLLL" << endl;
		}
		else if (x == "quit") {
			cout << "fine" << endl;
			quit = true;
		}
		else {
			cout << "you dont even know how to play rock paper scissors" << endl;
		}
	}	
	return 0;
}
