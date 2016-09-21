/* Client-side use of Berkeley socket calls -- send one message to server
   Requires two command line args:  
     1.  name of host to connect to (use  localhost  to connect to same host)
     2.  port number to use. 
   RAB 5/16 */

#include <iostream>
#include <cstring>
#include "Socket.h"
#include <vector>

using namespace std;

#define MAXBUFF 100
#define piID = "demo"

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
    cout << "Client: Connected." << endl;
  else {
    cout << "Client: Error, could not connect, aborting" << endl;
    return 1;
  }
  
  char buff[MAXBUFF];  /* message buffer */
  char buff2[MAXBUFF+10];  /* message buffer with prepended message type */

  if ((ret = sock.recv(buff, MAXBUFF-1)) < 0) {
    cout << "Client: Error, could not receive welcome message" << endl;
    return 1;
  } 
  buff[ret] = '\0';
  if (strcmp(buff, "NACK") == 0) {
    cout << "Client: Error, Server send NACK" << endl;
    return 1;
  }

  int counter = 0;
  while (counter<10) {

    //STUFF TO SEND TO SERVER
    
    strcpy(buff, "Date + time ");
    strcpy(buff2, "PiID Boolean ");
    strcat(buff2, buff);
    //DONE

    cout<<buff2<<endl;
    if (strcmp(buff, "DONE") == 0) {
      strcpy(buff2, buff);
      if ((ret = sock.send(buff2, strlen(buff2))) < 0) {
	cout<< "Client: Error in send()"<<endl;
	return 1;
      }
    }
    if ((ret = sock.send(buff2, strlen(buff2))) < 0)
      return 1;
    cout << ret << " characters sent" << endl;
    
    if ((ret = sock.recv(buff, MAXBUFF-1)) < 0)
      return 1;
    else {
      buff[ret] = '\0';
      cout << "acknowledged " << buff << endl;
    }
    counter++;
  }
  
  cout << "Termination message received" << endl;
  sock.send("END", 3);
  return 0;
}
