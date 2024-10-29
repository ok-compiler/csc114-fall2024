#include <iostream>
#include <string>

using namespace std;

int x;
int main() {
	cout << "here's 1-10" << endl;
	for(int i = 1; i < 11; i++) {
		cout << i << " ";
		x += i;
	}
	cout << endl << "the sum is: " << x << endl;
	return 0;
}
