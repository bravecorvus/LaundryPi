#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <fstream>
using namespace std;


// What GPIO input are we using?
//	This is a wiringPi pin number

#define	BUTTON_PIN 0

static volatile int globalCounter = 0 ;
static volatile int globalCounterF = 0 ;

void myInterrupt (void)
{
	++globalCounter ;
}

int main (void)
{
	int myCounter = 0 ;

	if (wiringPiSetup () < 0)
	{
		fprintf (stderr, "Unable to setup wiringPi: %s\n", strerror (errno)) ;
		return 1 ;
	}

	if (wiringPiISR (BUTTON_PIN, INT_EDGE_RISING, &myInterrupt) < 0)
	{
		fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno)) ;
		return 1 ;
	}

	ofstream log_file;
	log_file.open("log_file4.txt");

	for (;;)
	{
		log_file.open("log_file4.txt" , ios::out|ios::app);
		printf ("Waiting ... ") ; fflush (stdout) ;
		while (myCounter == globalCounter){
			++globalCounterF;
			//printf("False: %5d\n", globalCounterF);
			delay (100);
		}

		printf (" Done. counter: %5d\n", globalCounter) ;
		myCounter = globalCounter ;
		log_file << (int) myCounter << " ";
		log_file.close();
	}

	return 0 ;
}

