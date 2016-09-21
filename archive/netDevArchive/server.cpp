
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <iostream>
using namespace std;

#define PORT "2001"  // the port users will be connecting to
#define MAXDATASIZE 100 // max number of bytes we can get at once 
#define BACKLOG 10   // how many pending connections queue will hold

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(void) {
  int sockfd, new_fd, numbytes;  // listen on sock_fd, new connection on new_fd
  struct addrinfo hints, *servinfo, *p;
  struct sockaddr_storage their_addr; // connector's address information
  socklen_t sin_size;
  int yes=1;
  char s[INET6_ADDRSTRLEN];
  int rv;
  char buf[MAXDATASIZE];
  
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC; //handle both IPv4 and IPv6
  hints.ai_socktype = SOCK_STREAM; //UDP
  hints.ai_flags = AI_PASSIVE; // use my IP
  
  if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
    cout<< "getaddrinfo: " <<rv<<endl;
    return 1;
  }
  
  // loop through all the results and bind to the first we can
  for(p = servinfo; p != NULL; p = p->ai_next) {
    if ((sockfd = socket(p->ai_family, p->ai_socktype,
			 p->ai_protocol)) == -1) {
      cout<< "server: socket error"<<endl;
      continue;
    }
    
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
		   sizeof(int)) == -1) {
      cout<< "setsockopt error" <<endl;
      exit(1);
    }
    
    if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
      close(sockfd);
      cout<< "server: bind error"<<endl;
      continue;
    }
    break;
  }
  freeaddrinfo(servinfo); // all done with this structure
  
  if (p == NULL)  {
    cout<< "server: failed to bind"<<endl;
    exit(1);
  }
  
  if (listen(sockfd, BACKLOG) == -1) {
    cout<< "listen error"<<endl;
    exit(1);
  }
  cout<< "server: waiting for connections..."<<endl;
  
  while(1) {  // INFINITE loop
    sin_size = sizeof their_addr;
    new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
    if (new_fd == -1) {
      cout<< "accept error"<<endl;
      continue;
    }
    inet_ntop(their_addr.ss_family,
	      get_in_addr((struct sockaddr *)&their_addr), s, sizeof(s));
    cout<< "server: got connection from "<< s<<endl;

    int Val= 1;
    const char* bytesofVal = (const char*)&Val;
    int lengthofVal = sizeof(Val);

    if (send(new_fd, bytesofVal, lengthofVal, 0) == -1) {
      cout<< "send error"<<endl;
      close(sockfd);
      exit(0);
    }
  }
  close(new_fd);
}


