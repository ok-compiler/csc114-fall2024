// owen webster, csc114-404, 9/26/24, vars/data types
// i wrote all the code in this file

#include <iostream>
using namespace std;

// array w/ list of ingredients
string ingr[4] = {"flour", "salt", "yeast", "water"};

// array w/ measurements for each ingredient per 1 bread 
// (idk how to do object arrays to keep this in a single one)
int count[4];

// starting input values
int x = -1;
int y;
int z = 0;
int main() {
	cout << "list amounts needed for each ingr" << endl;
	while (z < 4) { // loop to take ingr count
		cout << ingr[z] << ": ";
		cin >> y; // count input
		if (y <= 0) { // if input is less than/equal 0, loop code 
			cout << "try again" << endl;
		}
		else {	
			count[z] = y; // set ingr count to input	
			z++; // add to z so that the loop can end	
		}	
	}
	cout << "\nhow many loafs ";
	while (x <= 0) { // while input is less than/equal to 0, loop code
		cin >> x;
		
		//if input is less than/equal 0, restart while loop
		
		if (x > 0) { // if input is positive int, perform loop to output bread ingredients and count * input
			cout << endl;
			
			for (int i = 0; i < 4; i++) {
			// every time loop finishes, int i increases by 1 until i reaches amount in array (4)
				cout << "grams of " << ingr[i] << ": " << count[i] * x << endl;
			}
		}
		else { // if not, restart loop
			cout << "try again ";
			x = 0;
		}
	}
	return 0;
}
