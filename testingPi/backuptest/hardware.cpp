#include "hardware.h"
using namespace std;

#define WASHERGPIO "17"
#define DRYERGPIO "22"
#define MAXBUFF 100
#define RPIID 000


//FIX
Vibration::Vibration(GPIOClass* arg) {
	if(arg->get_gpionum() == WASHERGPIO) {
		type = "wash";
	} else if (arg->get_gpionum() == DRYERGPIO) {
		type = "dry";
	}
	gpio = arg;
	numTrue = 0; numFalse = 0;
	PiID = RPIID;
	shelobSender.append(type, "Mohn", "8");
}

Vibration::Vibration(Vibration& arg) {
	PiID = RPIID;
	starttime = arg.starttime;
	currentime = arg.currentime;
	gpio = arg.gpio;
	type = arg.type;
	numTrue = arg.numTrue;
	numFalse = arg.numFalse;
}

Vibration::~Vibration() {
	boolvector.erase(boolvector.begin(), boolvector.end());
}

void Vibration::vectorErase() {
	boolvector.erase(boolvector.begin(), boolvector.end());	
	updateNumVar();
}

void Vibration::vectorPush(string arg) {
	if(arg == "1") {
		boolvector.push_back(1);
	} else if (arg == "0") {
		boolvector.push_back(0);
	}
	updateNumVar();
}

void Vibration::updateNumVar() {
	numTrue -= numTrue;
	numFalse -= numFalse;
	for (vector<bool>::iterator z=boolvector.begin(); z !=boolvector.end(); ++ z) {
			if(*z == true) {
				++numTrue;
				if(trueIncreases.size() > 1) {
					trueIncreases.push_back(trueIncreases[trueIncreases.size()-1]-trueIncreases[trueIncreases.size()-2]);
				} else {
					trueIncreases.push_back(0);
				}
			} else if(*z == false) {
				++numFalse;
				if(falseIncreases.size() > 1) {
					falseIncreases.push_back(falseIncreases[falseIncreases.size()-1]-falseIncreases[falseIncreases.size()-2]);
				} else {
					falseIncreases.push_back(0);
				}
			}
	    }
	numTruevector.push_back(numTrue);
	numFalsevector.push_back(numFalse);
}

void Vibration::updateStartTime() {
	starttime = ntpdate();
}

void Vibration::updateCurrentTime() {
	currentime = ntpdate();
}





time_t Vibration::ntpdate() {
char *hostname=(char *)"200.20.186.76";
int portno=123;
int maxlen=1024;
unsigned char msg[48]={010,0,0,0,0,0,0,0,0};
unsigned long buf[maxlen];
struct protoent *proto;
struct sockaddr_in server_addr;
int s;
time_t tmit;
 
// open a UDP socket
proto=getprotobyname("udp");
s=socket(PF_INET, SOCK_DGRAM, proto->p_proto);
 
memset( &server_addr, 0, sizeof( server_addr ));
server_addr.sin_family=AF_INET;
server_addr.sin_addr.s_addr = inet_addr(hostname);
server_addr.sin_port=htons(portno);
 
/*
 * build message. Message is all zeros except for a one in the
 * protocol version field
*/
 
// send the data to the timing server
sendto(s,msg,sizeof(msg),0,(struct sockaddr *)&server_addr,sizeof(server_addr));
// get the data back
struct sockaddr saddr;
socklen_t saddr_l = sizeof (saddr);
// here we wait for the reply and fill it into our buffer
recvfrom(s,buf,48,0,&saddr,&saddr_l);
 
//We get 12 long words back in Network order
 
/*
 * The high word of transmit time is the 4th word we get back
 * tmit is the time in seconds not accounting for network delays which
 * should be way less than a second if this is a local NTP server
 */
 
 tmit = ntohl((time_t)buf[4]); //# get transmit time
 return tmit;
}


void Vibration::modCurrentState(bool arg) {
	currentState = arg;
	stateChange = true;
}

void Vibration::HugosStatisticalAnalysis() {
	
	bool checkBump = checkForBump();
	bool checkTrue = checkForTrue();
	bool justTOn = justTurnedOn();
	bool justTOff = justTurnedOff();

	if(numTruevector.size() > 100 && numFalsevector.size() > 100) {
		if(checkBump == true) {
			//checkBump will check if there was just a bump, if it was just a bump, it will treat it just as a continuation of 
			//currentState = false
			stateChange = false;
			currentState = false;
			numFalsevector.erase(numFalsevector.begin(), numFalsevector.end()-100);
			numTruevector.erase(numTruevector.begin(), numTruevector.end()-100);
		} else if (checkTrue == false && justTOff == false) {
			//checkTrue will sees if there are any increases in the numTruevector, 
			//checks if there is continual turn off
			stateChange = false;
			currentState = false;
			numFalsevector.erase(numFalsevector.begin(), numFalsevector.end()-100);
			numTruevector.erase(numTruevector.begin(), numTruevector.end()-100);
		} else if (justTOff == true) {
			// checks if the machine just got turned off
			stateChange = true;
			currentState = false;
			numFalsevector.erase(numFalsevector.begin(), numFalsevector.end()-100);
			numTruevector.erase(numTruevector.begin(), numTruevector.end()-100);
		} else if (justTOn == true) {
			stateChange = true;
			currentState = true;
			numFalsevector.erase(numFalsevector.begin(), numFalsevector.end()-100);
			numTruevector.erase(numTruevector.begin(), numTruevector.end()-100);
		} else if (justTOn == false && checkTrue == true) {
			stateChange = false;
			currentState = true;
			numFalsevector.erase(numFalsevector.begin(), numFalsevector.end()-100);
			numTruevector.erase(numTruevector.begin(), numTruevector.end()-100);
		}
	} else {
		//if the sizes of numTruevector and numFalsevector are both smaller than 100
		//fill out with empty values to avoid a seg fault;
		for (vector<int>::iterator z=numTruevector.begin(); z !=numTruevector.begin()+100; ++ z) {
			numTruevector.push_back(0);
		}
		for (vector<int>::iterator z=numFalsevector.begin(); z !=numFalsevector.begin()+100; ++ z) {
			numTruevector.push_back(0);
		}
	}

	

	// if(numTruevector[trueIndex] == numTruevector[trueIndex-20] && numFalsevector[falseIndex] > numFalsevector[falseIndex-20]) {
	// 	stateChange = true;
	// 	currentState = false;
	// 	numTruevector.erase(numTruevector.begin(), numTruevector.end());
	// } else if (numTruevector[trueIndex] > numTruevector[trueIndex-20] && numFalsevector[falseIndex] > numFalsevector[falseIndex-20]) {
	// 	stateChange = true;
	// 	currentState = true;
	// }
}

bool Vibration::checkForBump() {
	int tempX = 0; int tempY = 0;
	for (vector<bool>::iterator z=boolvector.end()-100; z !=boolvector.end(); ++ z) {
		if(*z == 1) {
			++ tempX;
		} else if(*z == 0) {
			++ tempY;
		}
	}
	if(5*tempX < tempY && tempX > 0) {
		return true;
	} else {
		return false;
	}
}

bool Vibration::checkForTrue() {
	int tempTrue = 0;
	for (vector<int>::iterator z=numTruevector.end()-100; z !=numTruevector.end(); ++ z) {
		if(*z == 1) {
			++tempTrue;
		}
	}
	if(tempTrue > 0) {
		return true;
	} else {
		return false;
	}
}

bool Vibration::justTurnedOn() {
	int tempTrueIncreaseFirstHalf= 0;
	int tempTrueNonIncreaseFirstHalf= 0;
	int tempTrueIncreaseLastHalf= 0;
	int tempTrueNonIncreaseLastHalf= 0;


	for (vector<int>::iterator z=trueIncreases.end()-100; z !=trueIncreases.end()-50; ++ z) {
			if(*z > 0){
				++tempTrueIncreaseFirstHalf;
			} else {
				++tempTrueNonIncreaseFirstHalf;
			}
	}
	for (vector<int>::iterator z=trueIncreases.end()-49; z !=trueIncreases.end(); ++ z) {
			if(*z > 0){
				++tempTrueIncreaseLastHalf;
			} else {
				++tempTrueNonIncreaseLastHalf;
			}
	}
	if(tempTrueIncreaseLastHalf > tempTrueIncreaseFirstHalf+5) {
		return true;
	} else {
		return false;
	}
}

bool Vibration::justTurnedOff() {
	int tempFalseIncreaseFirstHalf= 0;
	int tempFalseNonIncreaseFirstHalf= 0;
	int tempFalseIncreaseLastHalf= 0;
	int tempFalseNonIncreaseLastHalf= 0;


	for (vector<int>::iterator z=trueIncreases.end()-100; z !=trueIncreases.end()-50; ++ z) {
			if(*z > 0){
				++tempFalseIncreaseFirstHalf;
			} else {
				++tempFalseNonIncreaseFirstHalf;
			}
	}
	for (vector<int>::iterator z=trueIncreases.end()-49; z !=trueIncreases.end(); ++ z) {
			if(*z > 0){
				++tempFalseIncreaseLastHalf;
			} else {
				++tempFalseNonIncreaseLastHalf;
			}
	}
	if(tempFalseIncreaseLastHalf > tempFalseIncreaseFirstHalf+5) {
		return true;
	} else {
		return false;
	}
}




void Vibration::sendInformation() {

	if(stateChange == true) {
		if(type == "wash") {
		    if(currentState == true) {
		    	stateChange = false;
		    	shelobSender.append("on");
		    	system(shelobSender.get_str().c_str());
		    } else if(currentState == false) {
		    	stateChange = false;
		    	shelobSender.append("off");
		    	system(shelobSender.get_str().c_str());
		    	vectorErase();
		    }    
		} else if (type == "dry") {
		    if(currentState == true) {
		    	stateChange = false;
		    	shelobSender.append("on");
		    	system(shelobSender.get_str().c_str());
		    } else if(currentState == false) {
		    	stateChange = false;
		    	shelobSender.append("off");
		    	system(shelobSender.get_str().c_str());
		    	vectorErase();
		    }
		}
		display();
	}
}


void Vibration::display() {
	cout << "True: " << numTrue << " False: " << numFalse << " Vector Size: " << boolvector.size() << endl;
}