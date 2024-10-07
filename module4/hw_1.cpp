#include <iostream>
using namespace std;

int x; // input

int main() {
	cout << "enter a year" << endl;
	
	while (!x || x < 0) {
		cin >> x;
		if (x > 0) {
			if ((x % 100 == 0 && x % 400 == 0) || (x % 4 == 0 && x % 100 != 0)) {
				cout << "yup thats a leap year" << endl;
			}
			/*else if (x % 4 == 0 && ) {
				cout << "yup thats a year" << endl;
			}*/
			else cout << "nah not a leap year" << endl;
		} else cout << "try again" << endl;
	}

return 0;
}
