#ifndef _ANALYSIS_H_
#define _ANALYSIS_H_
#include <fstream>
#include <vector>
using std::vector;

class Analysis {
	vector<bool> d;
	vector<bool> p;
	int prob;
	bool tmp;
	ifstream g;
	ofstream k;
public:
	Analysis(vector<bool>& da);
	Analysis(const char* filename);
	vector perform(); //performs the prediciton and returns the vector
	void writeout(); //writes out the results into a file
};

#endif /* _ANALYSIS_H_ */