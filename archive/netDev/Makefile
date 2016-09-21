CFLAGS = -Wall -std=c++11

all: client server

Socket.o:  Socket.cpp Socket.h
	g++ $(CFLAGS) -c Socket.cpp

CLIENT_OBJS = client.o Socket.o
client: $(CLIENT_OBJS)
	g++ $(CFLAGS) -o client $(CLIENT_OBJS)

client.o:  client.cpp Socket.h
	g++ $(CFLAGS) -c client.cpp

SERVER_OBJS = server.o Socket.o Worker.o
server: $(SERVER_OBJS)
	g++ $(CFLAGS) -pthread -o server $(SERVER_OBJS)

server.o:  server.cpp Socket.h Worker.h
	g++ $(CFLAGS) -c server.cpp

Worker.o: Worker.cpp Socket.h Worker.h 
	g++ $(CFLAGS) -c Worker.cpp
