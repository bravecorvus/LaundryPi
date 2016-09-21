#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main (){
	vector<bool> d1;
	//vector<bool> d2;
	vector<bool> p;

	bool tmp;
	int prob;
	char * file = "tinp1.txt";
	/*
	ifstream g("tinp1.txt");
	ifstream g2("tinp2.txt");
	ofstream k("tout.txt");
	*/

	for(int i=1; i<6; ++i){
		file[5] = (char) i;
		ifstream g(file);
		for (int i = 0; i < 10000; ++i)
		{
			g >> tmp;
			d1.push_back(tmp);
		}
		g.close();

		for (int i = 0; i < 10000; ++i)
		{
			prob = ( (int) d1[i] + (int) d2[i] ) / 2;
			if(prob > 0.5){
				p.push_back(true);
				k << p[i] << endl;
			}else{
				p.push_back(false);
				k << p[i] << endl;
			}
		}
	}
	k.close();

	cout << "d1 has size: " << d1.size() << endl;
	cout << "d2 has size: " << d2.size() << endl;
	cout << "Done!" << endl;
	return 0;
}