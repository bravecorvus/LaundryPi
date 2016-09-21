AnalysisDriver:  Analysis.o AnalysisDriver.o
	g++ -g -Wall -std=c++11 -o AnalysisDriver Analysis.o AnalysisDriver.o

Analysis.o:  Analysis.cpp Analysis.h
	g++ -g -Wall -std=c++11 -c Analysis.cpp

AnalysisDriver.o: AnalysisDriver.cpp
	g++ -g -Wall -std=c++11 -c AnalysisDriver.cpp