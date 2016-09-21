/* Client-side use of Berkeley socket calls -- send one message to server
   Requires two command line args:  
     1.  name of host to connect to (use  localhost  to connect to same host)
     2.  port number to use. 
   RAB 5/16 */

#include <iostream>
#include <cstring>
#include "Socket.h"

using namespace std;

#define MAXBUFF 100

int main(int argc, char **argv) {
  char *prog = argv[0];
  char *host;
  int port;
  int ret;  /* return value from a call */

  if (argc < 3) {
    cout << "Usage:  " << prog << " host port" << endl;
    return 1;
  }
  host = argv[1];
  port = atoi(argv[2]);

  Socket sock(host, port);
  if (sock.getConnected()) 
    cout << "Connected." << endl;
  else {
    cout << "Could not connect, aborting" << endl;
    return 1;
  }
  
  char buff[MAXBUFF];  /* message buffer */
  char buff2[MAXBUFF+10];  /* message buffer with prepended message type */

  if ((ret = sock.recv(buff, MAXBUFF-1)) < 0) {
    cout << "Could not receive welcome message from server, aborting" << endl;
    return 1;
  } 
  buff[ret] = '\0';
  if (strcmp(buff, "NACK") == 0) {
    cout << "Server rejected new connection, aborting" << endl;
    return 1;
  }
  // assert:  welcome message received and connection to server completed

  while (strcmp(buff2, "DONE") != 0) {
    if (!cin.getline(buff, MAXBUFF)) {
      cout << "Error or end of input -- aborting" << endl;
      return 1;
    }
    strcpy(buff2, buff);
    if ((ret = sock.send(buff2, strlen(buff2))) < 0)
      return 1;
  }

  return 0;

}
