all:	pimachine laundrytester

pimachine:	pimachine.o QueryBuilder.o
	g++ -Wall -std=c++11 -o pimachine pimachine.o QueryBuilder.o

pimachine.o:	QueryBuilder.h pimachine.cpp
	g++ -g -Wall -std=c++11 -c pimachine.cpp

QueryBuilder.o:	QueryBuilder.cpp
	g++ -g -Wall -std=c++11 -c QueryBuilder.cpp


laundrytester:	laundry.o laundrytester.o
	g++ -g -Wall -std=c++11 -o laundrytester laundrytester.o laundry.o

laundry.o:	laundry.cpp laundry.h
	g++ -g -Wall -std=c++11 -c laundry.cpp

laundrytester.o:	laundrytester.cpp laundry.h
	g++ -g -Wall -std=c++11 -c laundrytester.cpp
