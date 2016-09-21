#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main (){
	//input datasets - vectors
	vector<bool> d1;
	vector<bool> d2;
	vector<bool> p; //final vector with results based on prediction from input

	bool tmp,tmp2; //temporary storage for individual vector elements
	int prob; // temporary for individual probabilities

	//declare streams for data read-in
	ifstream g("tinp1.txt");
	ifstream g2("tinp2.txt");

	//output final predicted data
	ofstream k("tout.txt");

	//read in data from text files
	for (int i = 0; i < 10000; ++i)
	{
		g >> tmp;
		d1.push_back(tmp);
		g2 >> tmp2;
		d2.push_back(tmp2);
	}

	//finalize inputs by closing the streams
	g.close();
	g2.close();

	//machine learning - calculate the average number of 'true' booleans
	//in a specific index location, therefore get the probability of
	//the indicidence of a 'true'. If the probability is higher than
	// 50% (0.50) then predict 'true' in that spot in the final vector
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
	
	//close the output stream
	k.close();

	cout << "d1 has size: " << d1.size() << endl;
	cout << "d2 has size: " << d2.size() << endl;
	cout << "Done!" << endl;
	return 0;
}