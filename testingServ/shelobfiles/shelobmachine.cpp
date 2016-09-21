#include <iostream>
#include <fstream>
#include "QueryParser.h"
using namespace std;

int main() {
	QueryParser query("?status=off?machine=washer?building=Mohn?floor=8");

	string Mohn8D = query.get_status("Mohn", "8", "d");
	string Mohn8W = query.get_status("Mohn", "8", "w");
	//string WMoh8 = get_status("Mohn", "8", "w");
	//string DMoh8 = get_status("Mohn", "8", "d");
}