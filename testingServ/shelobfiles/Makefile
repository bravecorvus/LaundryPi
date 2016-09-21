all:	pimachine shelobmachine

pimachine:	pimachine.o QueryBuilder.o
	g++ -Wall -std=c++11 -o pimachine pimachine.o QueryBuilder.o

pimachine.o:	QueryBuilder.h pimachine.cpp
	g++ -g -Wall -std=c++11 -c pimachine.cpp

QueryBuilder.o:	QueryBuilder.cpp
	g++ -g -Wall -std=c++11 -c QueryBuilder.cpp


shelobmachine:	QueryParser.o shelobmachine.o
	g++ -g -Wall -std=c++11 -o shelobmachine shelobmachine.o QueryParser.o

QueryParser.o:	QueryParser.h QueryParser.cpp
	g++ -g -Wall -std=c++11 -c QueryParser.cpp

shelobmachine.o:	shelobmachine.cpp QueryParser.h
	g++ -g -Wall -std=c++11 -c shelobmachine.cpp

