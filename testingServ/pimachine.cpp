#include <iostream>
#include <string>
#include <cstdlib>
#include "QueryBuilder.h"
using namespace std;

int main() {
  QueryBuilder qb("off", "on", "Mohn", "8");
  //cout<< qb.get_str()<<endl;
  system(qb.get_str().c_str());
}
//"\?dryer_status=" + dryer_status + 
