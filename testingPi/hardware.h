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
		vector<bool> analysisvector;
		bool currentState;
		bool stateChange;
		int numTrue, numFalse;
		time_t starttime;
		time_t currentime;
		time_t timer;
		struct tm y2k;
		double seconds;
		QueryBuilder shelobSender;
	public:
		GPIOClass *gpio;
		int tempVecSize=0;
		int countAnOne=0;
		int startT;
		Vibration(GPIOClass*);
		Vibration(Vibration&);
		~Vibration();
		void vectorErase();
		void vectorPush(string);
		void updateNumVar();
		int updateStartTime();
		int updateCurrentTime();
		time_t ntpdate();
		void modCurrentState(bool);
		void readAnalIn(const char* filename);
		void HugosStatisticalAnalysis();
		int getVecSize();
		void sendInformation();
		void display();
};



#endif // _HARDWARE_