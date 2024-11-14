#include <iostream>
using namespace std;
int x, y, z, v;
/*
Write a program to print the sum of two numbers entered by user by defining your own function.
Define a function that returns the product of two numbers entered by user.
Write a program to print the circumference and area of a circle of radius entered by user by defining your own function.
Define two functions to print the maximum and the minimum number respectively among three numbers entered by user.
Define a program to find out whether a given number is even or odd.
A person is eligible to vote if his/her age is greater than or equal to 18. Define a function to find out if he/she is eligible to vote.
*/

// Write a program to print the sum of two numbers entered by user by defining your own function.
int sum(int a, int b) {
	return a + b;
}

// Define a function that returns the product of two numbers entered by user.
int product(int a, int b) {
	return a * b;
}

// Write a program to print the circumference and area of a circle of radius entered by user by defining your own function.
void circle(int a) {
	int circ = 2 * 3.14 * a;
	int area = 3.14 * a * a;
	cout << "area: " << area << endl << "circumference: " << circ << endl;
}

// Define two functions to print the maximum and the minimum number respectively among three numbers entered by user.
int max(int a, int b, int c) {
	int arr[3] = {a, b, c};
	int max = 0;
	for(int i = 0; i < 3; i++) {
		if (arr[i] >= max) max = arr[i];
	}
	return max;
}

int min(int a, int b, int c) {
	int arr[3] = {a, b, c};
	int min;
	for(int i = 0; i < 3; i++) {
		if (arr[i] <= min) min = arr[i];
	}
	return min;
}
// Define a program to find out whether a given number is even or odd.
bool is_even(int a) {
	if (a % 2 == 0) return true;
	else return false;
}	

// A person is eligible to vote if his/her age is greater than or equal to 18. Define a function to find out if he/she is eligible to vote.
bool vote(int a) {
	if (a >= 18) return true;
	else return false;
}



int main() {
	cout << "select a function:\n1 - sum\n2 - product\n3 - circle\n4 - max/min\n5 - even/odd\n6 - vote" << endl;
	cin >> x;
	switch(x) {
		case 1:
			cout << "enter number 1" << endl;
			cin >> y;
			cout << "enter number 2" << endl;
			cin >> z;
			cout << sum(y, z) << endl;
			return 0;
		break;
		case 2:
			cout << "enter number 1" << endl;
			cin >> y;
			cout << "enter number 2" << endl;
			cin >> z;
			cout << product(y, z) << endl;
			return 0;
		break;
		case 3:
			cout << "enter radius" << endl;
			cin >> y;
			circle(y);
			return 0;
		break;
		case 4:
			cout << "enter number 1" << endl;
			cin >> y;
			cout << "enter number 2" << endl;
			cin >> z;
			cout << "enter number 3" << endl;
			cin >> v;
			cout << "max: " << max(y,z,v) << endl << "min: " << min(y,z,v) << endl;
			return 0;
		break;
		case 5:
			cout << "enter a number" << endl;
			cin >> y;
			if(is_even(y)) cout << "even" << endl;
			else cout << "odd" << endl;
			return 0;
		break;
		case 6:
			cout << "enter age" << endl;
			cin >> y;
			if(vote(y)) cout << "eligible" << endl;
			else cout << "not eligible" << endl;
			return 0;
		break;
		default:
			cout << "invalid input" << endl;
			return 0;
		break;
	}
}
