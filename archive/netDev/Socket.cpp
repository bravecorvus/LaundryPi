/* Implementation module for Internet communication using Berkeley sockets
   RAB 4/30/16 */

#include <iostream>
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include "Socket.h"

using namespace std;

void Socket::create_socket() {
  if ((descrip = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    cerr << "Socket::Socket():" << strerror(errno) << endl;
  connected = 0;
}

Socket::Socket(int sd) {
  if (sd == -1)
    create_socket();
  else {
    descrip = sd;
    struct sockaddr_in ca; // socket address structure for the new client
    socklen_t size = sizeof(struct sockaddr);
    if (!::getpeername(sd, (struct sockaddr*) &ca, &size)) 
      connected = 1;
    else {
      connected = 0;
      if (errno != ENOTCONN)
	cerr << "Socket::Socket() getpeername " << strerror(errno) << endl;
    }
  }
}

Socket::Socket(const char *host, int port) {
  create_socket();
  connect(host, port);
}

Socket::~Socket() {
  close();
}

void Socket::close() {
  if (connected and ::shutdown(descrip, SHUT_RDWR) < 0)
      cerr << "Socket::close() shutdown " << strerror(errno) << endl;
  connected = 0;
  if (::close(descrip) < 0) 
    cerr << "Socket::close() " << strerror(errno) << endl;
}

int Socket::connect(const char *host, int port) {
  if (connected) {
    cerr << "Socket::connect() - already marked as connected, skipping" << endl;
    return 0;
  }
  // connected == 0

  struct hostent *hp;
  struct sockaddr_in sa;
  if ((hp = gethostbyname(host)) == NULL) {
    cerr << "Socket::connect() gethostbyname() " << strerror(errno) << endl;
    return 0;
  }
  memset((char *) &sa, '\0', sizeof(sa));
  memcpy((char *) &sa.sin_addr.s_addr, hp->h_addr, hp->h_length);
  sa.sin_family = AF_INET;
  sa.sin_port = htons(port);
  
  if (::connect(descrip, (struct sockaddr *) &sa, sizeof(sa)) < 0) {
    cerr << "Socket::connect() " << strerror(errno) << endl;
    if (errno == EISCONN)
      connected = 1;
    return 0;
  }
  connected = 1;
  return 1;  
}


int Socket::send(const char *msg, int len) {
  if (!connected) {
    cerr << "Attempt to send() on a disconnected Socket" << endl;
    return -1;
  }

  int ret;
  if ((ret = ::send(descrip, msg, len, 0)) < 0) 
    cerr << "Socket::send() " << strerror(errno) << endl;
  return ret;
}

int Socket::recv(char *buff, int len) {
  if (!connected) {
    cerr << "Attempt to recv() on a disconnected Socket" << endl;
    return -1;
  }

  int ret;
  if ((ret = ::recv(descrip, buff, len, 0)) < 0) {
    cerr << "Socket::recv() " << strerror(errno) << endl;
    return -1;
  }
  return ret;
}
/**
int Socket::send(const vector<int> & vec, int len) {
  if (!connected) {
    cerr << "Attempt to send() on a disconnected Socket" << endl;
    return -1;
  }

  int ret;
  if ((ret = ::send(descrip, vec, len, 0)) < 0) 
    cerr << "Socket::send() " << strerror(errno) << endl;
  return ret;
}

int Socket::recv(vector <int>& vec, int len) {
  if (!connected) {
    cerr << "Attempt to recv() on a disconnected Socket" << endl;
    return -1;
  }

  int ret;
  if ((ret = ::recv(descrip, vec, len, 0)) < 0) {
    cerr << "Socket::recv() " << strerror(errno) << endl;
    return -1;
  }
  return ret;
}
*/

ServerSocket::ServerSocket(int port) : Socket() {
  bound = 0;
  bind(port);
}


int ServerSocket::bind(int port) {
  if (bound) {
    cerr << "ServerSocket::bind() - already marked as bound, skipping" << endl;
    return 0;
  }
  // bound == 0

  struct sockaddr_in sa;
  sa.sin_family = AF_INET;
  sa.sin_port = htons(port);
  sa.sin_addr.s_addr = INADDR_ANY;

  if (::bind(descrip, (struct sockaddr*) &sa, sizeof(sa)) < 0) {
    cerr << "ServerSocket::bind() bind " << strerror(errno) << endl;
    return 0;
  }
  if (::listen(descrip, 5) < 0) {
    cerr << "ServerSocket::bind() listen " << strerror(errno) << endl;
    return 0;
  }
  bound = 1;
  return 1;  
}

Socket *ServerSocket::accept() {
  if (!bound)
    return 0;

  struct sockaddr_in ca; // socket address structure for the new client
  socklen_t size = sizeof(struct sockaddr);
  int clientd;

  cout << "Waiting for a incoming connection..." << endl;
  if ((clientd = ::accept(descrip, (struct sockaddr*) &ca, &size)) < 0) {
    cerr << "ServerSocket::accept() " << strerror(errno) << endl;
    return 0;
  }
  // ::accept() attempt was successful
  /* Note:  Could retrieve the IP address of client from ca, size */

  return new Socket(clientd);
}
