

/* Implementation module for multithreaded server thread class
   RAB 5/2/16 */

#include <iostream>
#include <cstring>
#include "Worker.h"
#include <fstream>
int Worker::MAXBUFF = 100;

Worker::Worker(int i, Socket *sp, const ControlData *cdp) 
  : thread(&Worker::doWork, this, cdp), id(i), sockp(sp), state(RUNNING) {}


Worker::~Worker() {
  delete sockp;
  sockp = 0;
}

void Worker::doWork(const ControlData *cdp) {
  char buff[MAXBUFF];  /* message buffer */
  int ret;  /* return value from a call */

  cout << "[" << id << "] started" << endl;

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
    fi.open("logfile.txt", ios::app);
    fi<<buff<<'\n';
    fi.close();
    
    if (strcmp(buff, "DONE") == 0 || !cdp->contin) {
      strcpy(buff, "DONE");
    }
    
  }
  state = DONE;
}
