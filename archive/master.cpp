#include <wiringPi.h>
#include <string.h>
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
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

#define PORT "2001"  // the port users will be connecting to
#define MAXDATASIZE 10000 // max number of bytes we can get at once 
#define BACKLOG 100   // how many pending connections queue will hold

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}


// HARDWARE CODE
#define BUTTON_PIN 22

// globalCounter:
//  Global variable to count interrupts
//  Should be declared volatile to make sure the compiler doesn't cache it.

static volatile int globalCounter = 0 ;


void myInterrupt (void)
{
  ++globalCounter ;
}
vector<int> intvector;
//END





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
  
  if (p == NULL)  {
    cout<< "server: failed to bind"<<endl;
    exit(1);
  }
  
  if (listen(sockfd, BACKLOG) == -1) {
    cout<< "listen error"<<endl;
    exit(1);
  }
  cout<< "server: waiting for connections..."<<endl;
  


 vector<int> intvector;
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
  ofstream log_file;
  log_file.open("log_file.txt");








  for (;;)
  {
    log_file.open("log_file.txt" , ios::out|ios::app);
    printf ("Waiting ... ") ; fflush (stdout) ;
    while (myCounter == globalCounter){
      delay (100);
    }

    printf (" Done. counter: %5d\n", globalCounter) ;
    myCounter = globalCounter ;
    intvector.push_back(myCounter);
    log_file << (int) myCounter << " ";
    log_file.close();
  for (vector<int>::iterator z=intvector.begin(); z !=intvector.end(); ++ z)
    {
     cout << *z << ' ';
    }  


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



  string temp;
 // for (vector<int>::iterator z=intvector.begin(); z !=intvector.end(); ++ z)
 //    {
 //      std::ostringstream ss;
 //      ss << *z;
 //      temp.append(ss.str());
 //      temp.append(" ");
 //    }
int vecsize;
for (vector<int>::iterator z=intvector.begin(); z !=intvector.end(); ++ z){++vecsize}++vecsize;
char array[vecsize];
 for (vector<int>::iterator z=intvector.begin(); z !=intvector.end(); ++ z)
    {
      array[z] = *z;
    }



        const char* bytesoftemp = (const char*)&temp;
         int lengthoftemp = temp.size();
        if (send(new_fd, bytesoftemp, lengthoftemp, 0) == -1) {
         cout<< "send error"<<endl;
      close(sockfd);
      exit(0);
    }
  }
}
close(new_fd);
return 0;
    
}