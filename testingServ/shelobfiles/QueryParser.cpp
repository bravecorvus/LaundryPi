#include <string>
#include <fstream>
#include <iostream>
using namespace std;
#include "QueryParser.h"

//Parses the query and logs the status into appropriate text file
QueryParser::QueryParser(string query) {

	parse(query);
	log_status();
}

//expected input -- ?status=on?machine=washer?building=Mohn?floor=8
void QueryParser::parse(string q) {
	int n = 0;
	bool equalsign = 0;
	if (q[n] == '?') {
		n++;
		while (q[n] != '?') {
			if (equalsign)
				state += q[n];
			if (q[n] == '=')
				equalsign = 1;
			n++;
		}
		n++;
		equalsign = 0;
		while (q[n] != '?') {
			if (equalsign)
				machine += q[n];
			if (q[n] == '=')
				equalsign = 1;
			n++;
		}
		n++;
		equalsign = 0;
		while (q[n] != '?') {
			if (equalsign)
				building += q[n];
			if (q[n] == '=')
				equalsign = 1;
			n++;
		}
		n++;
		equalsign = 0;
		while (q[n] != '\0') {
			if (equalsign)
				fl += q[n];
			if (q[n] == '=')
				equalsign = 1;
			n++;
		}
	}
	else
		cout<< "Parser error"<<endl;
	//cout<< state <<' '<< machine<<' '<<building<<' ' << fl <<endl;
}
// opens appropriate text file and prints its status
void QueryParser::log_status() {
	string m;
	if (machine == "washer")
		m = 'w';
	else
		m = 'd';
	ofstream f;
	f.open("logfiles/" + building + fl + m + ".txt");
	if (f.is_open()) {
		f << state << endl;
		f.close();
	}
	else
		cout<< "log_status: error"<<endl;
}

//building, floor, machine
string QueryParser::get_status(string build, string f, string mach) {
	ifstream x;
	string file = build + f + mach + ".txt";
	x.open(("logfiles/" + file).c_str());
	if (x.is_open()) {
		string w;
		x>> w;
		if (w == "on") 
			return "In use";
		else
			return "Vacant";
	}
	else
		return "location not implemented";
}
