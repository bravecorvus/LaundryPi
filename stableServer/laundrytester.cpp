#include <string>
#include <iostream>
#include "laundry.h"
using namespace std;

int main() {
  laundry Ellingson;
    //Hoyme, Larson, Thorson, Kildahl, Ytterboe, Hilboe, Kittelsby, Mohn, Rand, Melby, Tomson;
  Ellingson.setfloor("4");
  cout<< Ellingson.getfloor()<<endl;
}
