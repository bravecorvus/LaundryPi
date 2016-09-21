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
			} else if(*z == false) {
				++numFalse;
			}
	    }
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
	// Analyze the this.boolvector, and see if the machine was just started or turned off.
	// If the machine was turned off in the most recent cycle, set:
	// stateChange = true;
	// currentState = false;
	// If the machine was recently turned on set:
	// stateChange = true;
	//  currentState = true;

	//For now I will throw in a inaccurate if(numFalse > 3*numTrue) conditional to determine this;
	if(numFalse > 3*numTrue) {
		stateChange = true;
		currentState = false;
	}
	if (boolvector.size() < 100 && numTrue > 10) {
		stateChange = true;
		currentState = true;
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