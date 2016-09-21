#ifndef _HARDWARE_
#define _HARDWARE_


#include "GPIOClass.h"
#include "QueryBuilder.h"



#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <vector>
#include <cstring>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <errno.h>
#include <fstream>
#include <sstream>


// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>





using namespace std;

class Vibration {
		string type;
		int PiID;
		vector<bool> boolvector;
		bool currentState;
		bool stateChange;
		int numTrue, numFalse;
		time_t starttime;
		time_t currentime;
		QueryBuilder shelobSender;
	public:
		GPIOClass *gpio;
		Vibration(GPIOClass*);
		Vibration(Vibration&);
		~Vibration();
		void vectorErase();
		void vectorPush(string);
		void updateNumVar();
		void updateStartTime();
		void updateCurrentTime();
		time_t ntpdate();
		void modCurrentState(bool);
		void HugosStatisticalAnalysis();
		void sendInformation();
		void display();
};



#endif // _HARDWARE_