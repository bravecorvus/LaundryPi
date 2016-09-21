#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <fstream>
using namespace std;


// What GPIO input are we using?
//	This is a wiringPi pin number

#define	BUTTON_PIN 22

// globalCounter:
//	Global variable to count interrupts
//	Should be declared volatile to make sure the compiler doesn't cache it.

static volatile int globalCounter = 0 ;


/*
 * myInterrupt:
 *********************************************************************************
 */

void myInterrupt (void)
{
  ++globalCounter ;
}


/*
 *********************************************************************************
 * main
 *********************************************************************************
 */

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


  for (;;)
  {
	ofstream log_file("log_file.txt");
    printf ("Waiting ... ") ; fflush (stdout) ;
    while (myCounter == globalCounter)
      delay (100) ;

    printf (" Done. counter: %5d\n", globalCounter) ;
    myCounter = globalCounter ;
	log_file << (int) myCounter << " ";
	log_file.close();
  }
  
  return 0 ;
}

