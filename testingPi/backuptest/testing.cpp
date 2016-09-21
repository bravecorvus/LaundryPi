#include <iostream>
using namespace std;
#include <vector>

int main() {
	vector<int> yolo;
	yolo.push_back(20);
	yolo.push_back(2);
	yolo.push_back(3);
	yolo.push_back(4);


	// for (vector<int>::iterator z=yolo.end()-3; z !=yolo.end(); ++ z) {
	// 		cout << *z << endl;
	// }
	int num = 0;
	for (vector<int>::iterator z=yolo.begin()+1; z !=yolo.end(); ++ z) {
		if(*z > *(z-1)) {
			++num;
		}
	}

	cout << num << endl;
}