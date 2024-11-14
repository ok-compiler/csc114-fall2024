#include <iostream>
using namespace std;

int arr[10] = {1,2,3,4,5,6,7,8,9,10};
int x;
int main() {
	cout << "enter a number" << endl;
	cin >> x;
	for(int i = 0; i < 10; i += x){
		cout << arr[i] << " ";	
	}
}
