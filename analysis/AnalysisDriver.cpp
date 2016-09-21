#include <iostream>
#include <fstream>
#include <vector>
#include "Analysis.h"
using namespace std;

int main(){
	const char* fnme="tinp1.txt";
	Analysis first(fnme);
	fnme.perform();
	cout << "Analysis done!";
	fnme.writeout();
	cout << "Written out!";
	return 0;
}