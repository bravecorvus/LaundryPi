#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include <vector>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <fstream>
using namespace std;


bool checkHardware() {
	cout << "Checks to see if hardware is on of off" << endl;
	return true;
}

bool checkForFalseStart() {
	//Will return true if laundry is indeed on, return false if no further vibrations are detected 
	return true;
}

void initiateHardwareLoop() {
	//Begins the hardware event loop to analyze whether to start the timer
	//creates new hardware object, send data to central server
	if (checkHardware()==true) {
		cout << "initializing hardware";
	} else {
		exit(0);
	}

}

void timeLoop() {
	std::chrono::milliseconds interval(1);
	// checks for vibrations from the vibration sensor every milliseconds, and initiates the
	for(;;) {
    	if(checkHardware()) {
    		initiateHardwareLoop();
    	}
		std::this_thread::sleep_for( interval ) ;
	}	
}

int main() {
	timeLoop();
}