/*

A painting company has determined that for every 110 square feet of wall space, 1 gallon of paint and 8 hours of labor will be required. The company charges $25.00 per hour for labor. Write a C++ modular program (with functions) that allows the user to use a file for input for the following data: the number of rooms that are to be painted and the price of the paint per gallon. It should also ask for the square feet of wall space in each room. It should then display the following data:

The number of gallons of paint required

The hours of labor required

The cost of the paint

The labor charges

The total cost of the paint job

After the program is run, the program should prompt the user if you'd like to save the estimate to a file. if the answer is YES, you should save the estimate to a file. 

*/

#include <iostream>
#include <fstream>
#include <vector>

int rooms;
int ppg;
int sq_ft = 0;

using namespace std;

// # of gallons needed (rounded up)
int cgallons(int a) {
	return (a + 109) / 110;
}

// # of hours of labor required
int claborHours(int a) {
	return ((a * 8) + 109) / 110;
}

// cost of paint
int cpaint(int a, int b) {
	return a * b;
}

// calculates labor charges
int claborCost(int a, int b) {
	return a * b;
}

// total cost of the job
int ctotal(int a, int b) {
	return a + b;
}


int main() {
	vector<int> roomAreas;

	ifstream inputFile("input.txt");
		if (!inputFile) {
		cerr << "error opening file" << endl;
		return 1;
	}

	inputFile >> rooms >> ppg;
	roomAreas.resize(rooms);

	for (int i = 0; i < rooms; ++i) {
		inputFile >> roomAreas[i];
	}

	inputFile.close();
    
	for (int area : roomAreas) {
		sq_ft += area;
	}

	int gallons = cgallons(sq_ft);
	int laborHours = claborHours(sq_ft);
	int paint = cpaint(gallons, ppg);
	int laborCost = claborCost(laborHours, 25);
	int total = ctotal(paint, laborCost);

	cout << "# of gallons of paint required: " << gallons << endl;
	cout << "hours of labor required: " << laborHours << endl;
	cout << "cost of the paint: $" << paint << endl;
	cout << "labor charges: $" << laborCost << endl;
	cout << "total cost: $" << total << endl;

	char x;
	cout << "save the estimate to a file? (y/n): ";
	cin >> x;

	if (x == 'Y' || x == 'y') {
		ofstream outputFile("estimate.txt");
		if (!outputFile) {
			cerr << "error creating file" << endl;
			return 1;
		}
	        outputFile << "# of gallons of paint required: " << gallons << endl;
		outputFile << "hours of labor required: " << laborHours << endl;
		outputFile << "cost of the paint: $" << paint << endl;
		outputFile << "labor charges: $" << laborCost << endl;
		outputFile << "total cost: $" << total << endl;
	        outputFile.close();
	        cout << "estimate saved to estimate.txt" << endl;
	}

	return 0;
}
