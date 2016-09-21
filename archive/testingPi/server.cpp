

/** @file
    @brief Main program for multithreaded file server
    @par Usage Requires one command line arg:  
     1.  port number to use (on this machine). 

    @par Protocol (rules for correct communication)
    @parblock
     - <em>Server initialization</em>
       -# Server starts
       -# Server starts Servers' control thread
       -# Server initializes server socket, then blocks on accept()

     - <em>Client initialization</em>
       -# Server must be running and blocking on accept()
       -# Client starts and calls connect() (perhaps within a constructor)
       -# (Server's accept generates server's client socket)
       -# Server sends welcome message to Client
          - \c ACK indicates success
          - \c NACK indicates failure, too many clients
          - \c DONE indicates client should terminate
       -# Client receives welcome message;  \n
          on success, Server allocates and records client thread 

     - <em>Service operation</em>
       -# Client sends request message to Server\n
          Supported service(s): 
          - \c MSG followed by text
       -# Server performs service, then sends response to Client
          - \c DONE indicates that Client should terminate

     - <em>Client termination</em>
       -# Client sends \c END message to Server
       -# Client ends;\n  Server performs join() on client thread, then 
          deallocates and forgets it.

     - <em>Server termination</em>
       -# Server's control thread detects EXIT condition (e.g., from stdin),
          then marks Server for termination (contin = 0)
       -# Server's control thread performs <em>Client initialization</em>
       -# Server (main thread) detects termination and performs 
          <em>Client termination</em> on every recorded Client
       -# Server's control thread performs <em>Client termination</em>; 
          Server (main thread) performs join() on Server's control thread
       -# Server ends

    @endparblock

   RAB 5/16 */

#include <iostream>
#include <cstring>
#include <thread>
#include "Worker.h"
using namespace std;

#define MAXWORKERS 10

/** code for control thread
    @param cdp points to shared data structure for controlling server */
void doControl(ControlData *cdp, int port) {
  const int maxbuff = 100;
  char buff[maxbuff];
  while (cin.getline(buff, maxbuff-1)) {
    if (strcmp(buff, "EXIT") == 0) 
      break;
    else
      cerr << "[control thread] unrecognized command: " << buff << endl;
  }
  // assert:  buff == "EXIT"
  cout << "[control thread] EXIT encountered" << endl;
  cdp->contin = 0;
  
  // initialize as a Client, to unblock [main] accept()
  Socket sock("localhost", port);
  sock.recv(buff, maxbuff-1); // welcome message
  
  // 
  sock.send("DONE", 4);
}

int main(int argc, char **argv) {
  char *prog = argv[0];
  int port;

  if (argc < 2) {
    cout << "Usage:  " << prog << " port" << endl;
    return 1;
  }
  port = atoi(argv[1]);

  ServerSocket ssock(port);
  if (ssock.getBound())
    cout << "[main] port " << port << " bound to server socket" << endl;
  else {
    cout << "[main] could not bind port " << port << " to server socket, aborting"
	 << endl;
    return 1;
  }
  // server socket ssock is now set up

  /* Define shared data structure for controlling server */
  ControlData controlData;

  /* Create a thread for handling control input */
  thread controlThread(doControl, &controlData, port);
  
  /* main loop: */
  Socket *csockp;  // to hold new client socket
  Worker *workers[MAXWORKERS];  
  for (int i = 0; i < MAXWORKERS;  i++)
    workers[i] = 0;
  int workerCount = 0;
  while (controlData.contin) {
    csockp = ssock.accept();

    int indx;  // loop control for finding unused element in workers[] 
    while (indx < MAXWORKERS) {
      if (workers[indx] != 0 && 
	  workers[indx]->getState() == ThreadState::DONE) {
	cout << "[main] joining on [" << workers[indx]->getId() << "]" << endl;
	workers[indx]->join();
	cout << "[main] join on [" << workers[indx]->getId() << "] accomplished" 
	     << endl;
	delete workers[indx];
	workers[indx] = 0;
      }
      if (workers[indx] == 0)
	break;
      indx++;
    }
    if (indx == MAXWORKERS) {
      cout << "[main] workers[] overfull, rejecting a new client" << endl;
      csockp->send("NACK", 4);
      continue;
    }
    // assert:  workers[indx] is available
    workers[indx] = new Worker(workerCount++, csockp, &controlData);
  }

  for (int i = 0;  i < MAXWORKERS;  i++)
    if (workers[i]) {
      cout << "[main] joining on [" << workers[i]->getId() << "]" << endl;
	workers[i]->join();
	cout << "[main] join on [" << workers[i]->getId() << "] accomplished" 
	     << endl;
	delete workers[i];
	workers[i] = 0;
    }
  
  controlThread.join();
  cout << "[main] control thread join accomplished" << endl;

  return 0;
}

