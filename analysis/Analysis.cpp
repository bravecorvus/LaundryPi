#include <vector>
#include "Analysis.h"
#include <fstream>
using namespace std;
using std::vector;

Analysis::Analysis(vector<bool>& da){
	d = da;
}

Analysis::Analysis(const char* filename){
	g.open(filename);
	for (int i = 0; i < 10000; ++i){
		g >> tmp;
		d.push_back(tmp);
	}
	g.close();
}

vector Analysis::perform(){
	for (int i = 0; i < 10000; ++i)
	{
		prob = ( (int) d1[i] + (int) d2[i] ) / 2;
		if(prob > 0.5){
			p.push_back(true);
		}else{
			p.push_back(false);
		}
	}
}

void Analysis::writeout() {
	k.open("t2out.txt");
	for (int i = 0; i < 10000; ++i)
	{
		prob = ( (int) d1[i] + (int) d2[i] ) / 2;
		if(prob > 0.5){
			k << p[i] << endl;
		}else{
			k << p[i] << endl;
		}
	}
	k.close();
}