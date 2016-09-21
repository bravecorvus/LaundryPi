#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h> //stdin(), fgets
#include <stdlib.h> //atoi()
#include <string.h> //bzero()
#include <unistd.h> //write()
#include <iostream>
using namespace std;

#define BACKLOG 50

int main(int argc, char *argv[]) {
  
  int sock_fd, newsock_fd, portno;
  struct sockaddr_in serv_addr;
  struct sockaddr_in client_addr;
  socklen_t clilen;
  
  char buffer[50];
  portno = atoi(argv[1]);
  sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd < 0)
    cout << "Error in socket() call"<< endl;
  else
    cout << "Socket() is OK ..." <<endl;
  
  //REPLACE WITH FOR LOOP??
  bzero((char*)&serv_addr, sizeof(serv_addr));
  //?? CLEAR SYSTEM ??
  serv_addr.sin_family = AF_INET;
  //Fill with current host's IP
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  //CONVERT DATA TRANSFER TO BYTES
  serv_addr.sin_port = htons(portno);
  
  //REPLACE WITH C-STYLE STRING COPY LATER ?
  //strncpy(serv_addr.sin_path, SOCK_PATH, sizeof(struct sockaddr_in) -1);
  
  //SAVE ADRESS OF PORT WITH bind() SYSTEM CALL
  if (bind(sock_fd, (struct sockaddr *) &serv_addr, 
	   sizeof(serv_addr)) < 0)
    cout << "Error in bind()"<<endl;
  else
    cout << "bind() is OK..."<<endl;
  //WAIT FOR CLIENT WITH listen()
  if (listen(sock_fd, BACKLOG) == -1)
    cout<< "Error in listen()"<<endl;
  else
    cout << "listen() is ok..."<<endl;
  //ACCEPT CONNCETION WITH accept() 
  clilen = sizeof(client_addr);
  newsock_fd = accept(sock_fd, (struct sockaddr *) 
		      &client_addr, &clilen);
  if (newsock_fd < 0)
    cout<< "Error in accept()"<<endl;
  else
    cout<< "accept() is OK..."<<endl;
  cout<<"server got connection!!"<<endl;
  //DATA TRANSMISSION
  bzero(buffer, 50);
  //CONVERT STREAM INTO C-STRING
  fgets(buffer, 49, stdin);
  int n;
  n = write(newsock_fd, "Hello, world! \n", 13);
  if (n < 0)
    cout<< "Error in write()"<< endl;
  else 
    cout<< "write() is OK..."<<endl;
  //CLOSE SOCKETS
  close(newsock_fd);
  close(sock_fd);
  return 0;
}
