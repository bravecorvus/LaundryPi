#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>
#include <string.h>
#include <vector>
#include "GPIOClass.h"
#include "Socket.h"
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
using namespace std;




#define WASHERGPIO "17"
#define DRYERGPIO "22"
#define MAXBUFF 100
#define RPIID 000

enum type{wash, dry};

class Vibration {
		type machine;
		int PiID;
		vector<bool> boolvector;
		bool currentState;
		bool stateChange;
		int numTrue, numFalse;
		time_t starttime;
		time_t currentime;
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
		void sendInformation(char[], char[], Socket&, int&);
		void display();
};








Vibration::Vibration(GPIOClass* arg) {
	updateStartTime();
	updateCurrentTime();
	if(arg->get_gpionum() == WASHERGPIO) {
		machine = wash;
	} else if (arg->get_gpionum() == DRYERGPIO) {
		machine = dry;
	}
	gpio = arg;
	numTrue = 0; numFalse = 0;
	PiID = RPIID;
}

Vibration::Vibration(Vibration& arg) {
	PiID = RPIID;
	starttime = arg.starttime;
	currentime = arg.currentime;
	gpio = arg.gpio;
	machine = arg.machine;
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
	numTrue = 0; numFalse = 0;
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
long tmit;
 
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
 
 tmit=ntohl((time_t)buf[4]); //# get transmit time
 // tmit-= 2208988800U;
 return tmit;
}


void Vibration::modCurrentState(bool arg) {
	currentState = arg;
	stateChange = true;
}

void Vibration::HugosStatisticalAnalysis() {
send the vector to HugoClass


	//For now I will throw in a inaccurate if(numFalse > 3*numTrue) conditional to determine this;
	if(numFalse > 3*numTrue) {
		stateChange = true;
		currentState = false;
		vectorErase();
		updateNumVar();
	} else if (boolvector.size() < 100 && numTrue > 10) {
		stateChange = true;
		currentState = true;
		updateNumVar();
	}
}





void Vibration::sendInformation(char buff[], char buff2[], Socket &sock, int &ret) {
	strcpy(buff, asctime(localtime(&currentime)));

	if(stateChange == true) {
		if(machine == wash) {
		    if(currentState == true) {
		    	stateChange = false;
		    	strcpy(buff2, "PiID Laundry Turned On ");	
		    	strcat(buff2, buff);
		    } else if(currentState == false) {
		    	stateChange = false;
		    	strcpy(buff2, "PiID Laundry Turned Off");
		    	strcat(buff2, buff);
		    	vectorErase();
		    	updateNumVar();
		    }    
		} else if (machine == dry) {
		    if(currentState == true) {
		    	stateChange = false;
		    	strcpy(buff2, "PiID Dryer Turned On ");	
		    	strcat(buff2, buff);
		    } else if(currentState == false) {
		    	stateChange = false;
		    	strcpy(buff2, "PiID Dryer Turned Off");
		    	strcat(buff2, buff);
		    	vectorErase();
		    	updateNumVar();
		    }
		}
	    sock.send(buff2, MAXBUFF-1);
	    ret = sock.recv(buff, MAXBUFF-1);
	    buff[ret] = '\0';
	}
}


void Vibration::display() {
	cout << "True: " << numTrue << " False: " << numFalse << " Vector Size: " << boolvector.size() << endl;
}






int main(int argc, char **argv) {
	// char *prog = argv[0];
	char *host;
	int port;
	int ret;  /* return value from a call */
	host = argv[1];
	port = atoi(argv[2]);
	Socket sock(host, port);
	sock.getConnected();
	char buff[MAXBUFF];  /* message buffer */
	char buff2[MAXBUFF+10];
	ret = sock.recv(buff, MAXBUFF-1);

	GPIOClass* washer = new GPIOClass("WASHERGPIO"); //create new GPIO object to be attached to  GPIOWASHER
	GPIOClass* dryer = new GPIOClass("DRYERGPIO"); //create new GPIO object to be attached to  GPIODRYER
	washer->export_gpio(); //export GPIO WASHER
	dryer->export_gpio(); //export GPIO DRYER
	cout << " GPIO pins exported" << endl;
	washer->setdir_gpio("in"); //set GPIO to input
	dryer->setdir_gpio("in"); // set GPIO to input
	Vibration washerhardware(washer);
	Vibration dryerhardware(dryer);




	//Running this for the first time
	int counter;
	for(counter = 0; counter < 10; ++counter) {
		//run the initial testing, use statistical tools to run the initial analysis, store it in a textfile
		// for later use in HugoStatisticalAnalysisTool()
	}


	string inputstatewasher;
	string inputstatedryer;
	std::chrono::milliseconds interval( 10 ) ; // 10 milliseconds
	for(;;) {
		washerhardware.gpio->getval_gpio(inputstatewasher);
		dryerhardware.gpio->getval_gpio(inputstatedryer);
		washerhardware.vectorPush(inputstatewasher);
		dryerhardware.vectorPush(inputstatedryer);
		
		washerhardware.sendInformation(buff, buff2, sock, ret);
		dryerhardware.sendInformation(buff, buff2, sock, ret);
		std::this_thread::sleep_for( interval ) ;
	}
	return 0;
}