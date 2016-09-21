#include <wiringPi.h>
#include <stdio.h>    // Used for printf() statements
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int vibPin = 6; //BCM 6, Physical 31, WiringPi 22

int main (void) {
	wiringPiSetupGpio();

	pinMode(vibPin,INPUT);

	pullUpDnControl(vibPin, PUD_UP);

	printf("The Vib Sensor should be running\n");

	bool* vibData;
	vibData = new bool[10];
	ofstream g("hugo_logoutput.txt")

	for(int i=0; i<10; ++i) {
		if(digitalRead(vibPin)){
			cout << "Vibration!" << endl;
			vibData[i] = TRUE;
			g << vibData[i] << " ";
		}else{
			cout << "Nothing" << endl;
			vibData[i] = FALSE;
			g << vibData[i] << " ";
		}
	}
	g.close();
	return 0;
}