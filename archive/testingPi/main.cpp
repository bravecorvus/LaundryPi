#include <chrono>
#include <thread>
#include <ctime>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "GPIOClass.h"
#include <vector>
#include "Socket.h"
#include <cstring>

using namespace std;
vector <bool> boolvector;
#define MAXBUFF 100
#define piID = "demo"



void sendTrue(char buff[], char buff2[], Socket &sock, int &ret, bool &laundryTurnedOn) {
	strcpy(buff, "Date + time ");
    strcpy(buff2, "PiID Laundry Turned On ");
    strcat(buff2, buff);
    sock.send(buff2, MAXBUFF-1);
    ret = sock.recv(buff, MAXBUFF-1);
    buff[ret] = '\0';
    laundryTurnedOn = false;
}

void sendFalse(char buff[], char buff2[], Socket &sock, int &ret, bool &laundryTurnedOff) {
	strcpy(buff, "Date + time ");
    strcpy(buff2, "PiID Laundry Turned Off");
    strcat(buff2, buff);
    sock.send(buff2, MAXBUFF-1);
    ret = sock.recv(buff, MAXBUFF-1);
    buff[ret] = '\0';
    laundryTurnedOff = false;
}

int main(int argc, char **argv)
{
	char *prog = argv[0];
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






	string inputstate;
	GPIOClass* gpio4 = new GPIOClass("4"); //create new GPIO object to be attached to  GPIO4
	GPIOClass* gpio17 = new GPIOClass("17"); //create new GPIO object to be attached to  GPIO17

	gpio4->export_gpio(); //export GPIO4
	gpio17->export_gpio(); //export GPIO17

	cout << " GPIO pins exported" << endl;

	gpio17->setdir_gpio("in"); //GPIO4 set to output
	gpio4->setdir_gpio("out"); // GPIO17 set to input







    std::chrono::milliseconds interval( 10 ) ; // 10 milliseconds
    
    bool laundryTurnedOn = false;
    bool laundryTurnedOff = false;
    for(;;)
    {
    	gpio17->getval_gpio(inputstate);
    	if(inputstate=="1") {
    		boolvector.push_back(true);
    		laundryTurnedOff = false;
    	} else if (inputstate == "0") {
    		boolvector.push_back(false);
    	}

    	double True = 0;
		double False = 0;
		for (vector<bool>::iterator z=boolvector.begin(); z !=boolvector.end(); ++ z) {
			if(*z == true) {
				++True;
			} else if(*z == false) {
				++False;
			}
	    }  
	    cout << "true: " << True << ' ' << " false " << False << endl;
	    if(False > True*3) {
	    	boolvector.erase(boolvector.begin(), boolvector.end());
	    	False -= False;
	    	True -= True;
	    }
	    if(boolvector.size() > 0 && boolvector.size() < 10) {
	    	laundryTurnedOn = true;
	    }
	    if(False > 1 && False < 10) {
	    	laundryTurnedOff = true;
	    }
	    if(laundryTurnedOn == true) {
			sendTrue(buff, buff2, sock, ret, laundryTurnedOn);
	    }
	    if (laundryTurnedOff == true) {
	    	sendFalse(buff, buff2, sock, ret, laundryTurnedOff);
	    }
	    std::this_thread::sleep_for( interval ) ;
	}

	return 0;
}