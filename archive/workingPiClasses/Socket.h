/* Interface module for Internet communication using Berkeley sockets
   Magnus 5/8/16 */
#ifndef SOCKET_H_
#define SOCKET_H_

/** A class for socket communication */
class Socket {
 protected:
  int descrip;  /**< socket descriptor, or -1 if failed to allocate socket */
  int connected; /**< non-zero if connect() succeeded on this socket */

 public:
 
  /* Initialize a Socket
     @param sd Socket descriptor for an existing socket.
     With default argument, first create a socket and use that descriptor */
  Socket(int sd = -1); 
  ~Socket();

  /** initialize a socket and attempt to connect to a particular host and port
      @param host Internet name for a computer, e.g., rns202-1.cs.stolaf.edu
      @param port TCP port for server socket on host  */
  Socket(const char *host, int port);

  /** Connect this socket to a server 
      @pre State variable connected must be assigned before calling this method
      @param host Internet name for a computer, e.g., rns202-1.cs.stolaf.edu
      @param port TCP port for server socket on host
      @return 1 on success, 0 on failure */
  int connect(const char *host, int port);

  /** Send a message on this socket
      @param msg Message to be transmitted
      @param len Number of characters of msg to transmit
      @return Number of characters transmitted, or -1 on failure */
  int send(const char *msg, int len);

  /** Receive a message on this socket
      @param buff Array to receive message
      @param len Maximum number of characters to receive in buff
      @return Number of characters transmitted, or -1 on failure */
  int recv(char *msg, int len);
  /** Send a vector on this socket
      @param vec Vector to be transmitted
      @param len Number of characters of vec to transmit
      @return Number of characters transmitted, or -1 on failure */
  //int send(vector<int>& vec, int len);

  /** Receive a vector on this socket
      @param vec Vector to receive message
      @param len Maximum number of characters to receive in vec
      @return Number of characters transmitted, or -1 on failure */
  //int recv(vector<int>& vec, int len);
  

  /** Invalidate this socket for further use. 
      If connected, first shut down communication. */
  void close();

  /** @return Value of state variable descrip */
  int getDescriptor() { return descrip; } 

  /** @return Value of state variable connected */
  int getConnected() { return connected; } 

 protected:
  /** helper method for socket initialization
      @sc Initialize descrip, and assign 0 to connected */
  void create_socket(); 
};


class ServerSocket : public Socket {
 protected:
  int bound; /**< non-zero if bind() succeeded on this socket */

 public:
 ServerSocket() : Socket() { bound = 0; }
  /** initialize a socket and attempt to associate a port with it 
      @param port TCP port number */
  ServerSocket(int port);

  /** Associate a port with this server socket
      @pre State variable connected must be assigned before calling this method
      @param port TCP port number
      @return 1 on success, 0 on failure */
  int bind(int port);

  /** Wait for and accept one connection request from another process, 
      potentially on a different host
      @return Address of a newly allocated Socket for communication with 
      another process.  Return 0 if attempt to accept failed or if this 
      server socket is not bound */ 
  Socket *accept();

  /** @return Value of state variable bound */
  int getBound() { return bound; } 
}; 

#endif //SOCKET_H_
