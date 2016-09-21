#ifndef _STATEHANDLER_H_
#define _STATEHANDLER_H_

#include <iostream>
using namespace std;
#include <sys/time.h>

/** Source file to set up neccessary data to collect
    @param timeC Double val to hold current time
    @param vibration Bool that holds if sensors are affected
    @return nothing
*/
class StateHandler {
  double timeC;
  bool vibration;
 public:
  /** Default Constructor of class, takes no arguments
      @return nothing
*/
  StateHandler(void);
  /** Constructor of class 
      @param v Vibdata in bool that tells if the sensor are activeated
      @return nothing
  */
  StateHandler( bool v);
  /** Sends Vibration data
      @return boolean value
  */
  bool sendViData(void);
  /** Recieves vibration data
      @param v Holds boolean value that sets the class' parameter
      @return nothing
  */
  void recieveViData(bool v);

};

#endif /* _STATEHANDLER_H_ */
