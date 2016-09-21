#include <string>
#include<iostream>
using namespace std;
#include"laundry.h"

laundry::laundry(string f, string d, string w, string s) {
  floor = f;
  washerstate = w;
  dryerstate = d;
}
laundry::laundry(void) {
  floor = "0";
  washerstate = "off";
  dryerstate = "off";
}
void laundry::setfloor(string f) {
  floor = f;
}
void laundry::setdryerstate(string d) {
  dryerstate = d;
}
void laundry::setwasherstate(string w) {
  washerstate = w;
}

