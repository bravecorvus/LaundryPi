#include <stdio.h> //stdin(), fgets()
#include <stdlib.h> //atoi()
#include <unistd.h> //write()
#include <string.h> //bzero()
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>  //gethostbyname()
#include <iostream>
using namespace std;
#define BACKLOG 50
int main(int argc, char *argv[]) {
  
  int sock_fd, newsock_fd, portno;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  struct sockaddr_in client_addr;
  socklen_t clilen;
  
  char buffer[50];
  portno = atoi(argv[1]);
  sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd < 0)
    cout << "Error in socket() call"<< endl;
  else
    cout << "Socket() is OK ..." <<endl;
  server = gethostbyname(argv[1]);
  if (server = NULL)
    cout<< "Error in finding host"<<endl;
  else
    cout<< "Found host..."<<endl;
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,
	server->h_length);
  serv_addr.sin_port = htons(portno);
  if (connect(sock_fd,(struct sockaddr *) &serv_addr,
	      sizeof(serv_addr)) < 0) 
    cout<< "Error in connect() "<<endl;
  else
    cout<< "connect() is OK.."<<endl;
  cout<< "Please enter the message: "<<endl;
  bzero(buffer,256);
  cin>>buffer;
  int intromess;
  intromess = read(sock_fd, buffer, strlen(buffer)-1);
  if (intromess < 0)
    cout<< "Error in intromessage()"<<endl;
  else
    cout<<intromess<<endl;
  int n;
  n = write(sock_fd,buffer,strlen(buffer));
  if (n < 0) 
    cout<< "Error in write()"<<endl;
  bzero(buffer,256);
  n = read(sock_fd,buffer,255);
  if (n < 0) 
    cout<< "Error in read()"<<endl;
  printf("%s\n",buffer);
  close(sock_fd);
  return 0;
}


/**
int main(int argc, char *argv[])
{
  int sock_fd, portno;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  
  char buffer[50];
  portno = atoi(argv[2]);
  sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd < 0) 
    cout<< "Error in socket() call" <<endl;
  else
    cout<< "socket() is OK..."<<endl;
  server = gethostbyname(argv[1]);
  if (server == NULL)
    cout<< "Error in finding host"<<endl;
  else
    cout<< "Found host"<<endl;
  
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,
	server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sock_fd,(struct sockaddr *) &serv_addr,
		sizeof(serv_addr)) < 0) 
      cout<< "Error in connect() "<<endl;
    else
      cout<< "connect() is OK.."<<endl;
    cout<< "Please enter the message: "<<endl;
    bzero(buffer,256);
    cin>>buffer;
    int intromess;
    intromess = read(sock_fd, buffer, strlen(buffer)-1);
    if (intromess < 0)
      cout<< "Error in intromessage()"<<endl;
    else
      cout<<intromess<<endl;
    int n;
    n = write(sock_fd,buffer,strlen(buffer));
    if (n < 0) 
      cout<< "Error in write()"<<endl;
    bzero(buffer,256);
    n = read(sock_fd,buffer,255);
    if (n < 0) 
      cout<< "Error in read()"<<endl;
    printf("%s\n",buffer);
    close(sock_fd);
    return 0;
}
*/
