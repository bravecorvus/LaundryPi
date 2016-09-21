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

using namespace std;
vector <bool> boolvector;




bool lasttwentytrue(vector<bool> a) {
	vector<bool>checker;
	int Trues = 0;
	for (vector<bool>::iterator z=a.end()-20; z !=a.end(); ++ z) {
		checker.push_back(*z);
	}
	for (vector<bool>::iterator z=checker.begin(); z !=checker.end(); ++ z) {
		if(*z == true) ++Trues;
	}
	if(Trues > 0) {
		return true;
	} else {
		return false;
	}
}



int main()
{

	string inputstate;
	GPIOClass* gpio4 = new GPIOClass("4"); //create new GPIO object to be attached to  GPIO4
	GPIOClass* gpio17 = new GPIOClass("17"); //create new GPIO object to be attached to  GPIO17

	gpio4->export_gpio(); //export GPIO4
	gpio17->export_gpio(); //export GPIO17

	cout << " GPIO pins exported" << endl;

	gpio17->setdir_gpio("in"); //GPIO4 set to output
	gpio4->setdir_gpio("out"); // GPIO17 set to input







    std::chrono::milliseconds interval( 10 ) ; // 10 milliseconds
    for(;;)
    {
    	gpio17->getval_gpio(inputstate);
    	if(inputstate=="1") {
    		boolvector.push_back(true);
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
	    std::this_thread::sleep_for( interval ) ;
	}

	return 0;
}