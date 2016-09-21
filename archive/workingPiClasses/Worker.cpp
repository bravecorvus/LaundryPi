

/* Implementation module for multithreaded server thread class
   RAB 5/2/16 */

#include <iostream>
#include <cstring>
#include "Worker.h"
#include <fstream>
int Worker::MAXBUFF = 100;

Worker::Worker(int i, Socket *sp, const ControlData *cdp) 
  : thread(&Worker::doWork, this, cdp), id(i), sockp(sp), state(RUNNING) {}

/* NOTE about thread constructor call above:  
   methods have an implicit first argument, namely, the object whose state 
   variables they act on.  That object argument must be explicitly passed 
   for this 2-argument thread constructor */

Worker::~Worker() {
  delete sockp;
  sockp = 0;
}

void Worker::doWork(const ControlData *cdp) {
  char buff[MAXBUFF];  /* message buffer */
  int ret;  /* return value from a call */

  cout << "[" << id << "] started" << endl;
  // cout << "[" << id << "] socket <" << sockp->getDescriptor() << ">" << endl; //DEBUG


  // send welcome message
  if (cdp->contin) 
    strcpy(buff, "ACK");
  else
    strcpy(buff, "DONE");
  sockp->send(buff, strlen(buff));  

  while (strcmp(buff, "DONE") != 0) {
    ret = sockp->recv(buff, MAXBUFF-1);

    buff[ret] = '\0';
    cout << buff << endl;
    
    ofstream fi;
    fi.open("logfile.txt");
    fi<<buff;
    fi.close();
    
    if (strcmp(buff, "DONE") == 0 || !cdp->contin) {
      strcpy(buff, "DONE");
      sockp->send(buff, 4);
      cout << "[" << id << "] sent termination message" << endl;

    } else {
      //cout<<buff<<endl;
      sockp->send("ACK", 4);
      //cout << "[" << id << "] sent negative acknowledgment" << endl;
    }
  }
  state = DONE;
}
