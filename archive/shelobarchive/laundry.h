#ifndef _LAUNDRY_H_
#define _LAUNDRY_H_

#include <string>
#include <iostream>
using namespace std;

class laundry {
  string floor;
  string washerstate;
  string dryerstate;
  
 public:
  laundry(string f, string d, string w, string s);
  laundry(void);
  
  void setfloor(string f);
  void setdryerstate(string d);
  void setwasherstate(string w);

  string getfloor() {return floor;}
  string getdryerstate() {return dryerstate;}
  string getwasherstate() {return washerstate;}
  
};

     
#endif


