#include <string>
#include <iostream>
#include "QueryBuilder.h"
using namespace std;

QueryBuilder::QueryBuilder() {
  cmd = "/usr/bin/curl";
  args = "--user laundry:3.1416Day";
  address = "http://devel.cs.stolaf.edu/laundry/A/write.exec";
  setup = cmd + " " + args + " " + address;
}
QueryBuilder::QueryBuilder(string ws, string ds, string b, string f) {
  cmd = "/usr/bin/curl";
  args = "--user laundry:3.1416Day";
  address = "http://devel.cs.stolaf.edu/laundry/A/write.exec";
  setup = cmd + " " + args + " " +address;
  append(ws, ds, b, f);
}

string QueryBuilder::get_str() {
  return full;
}

void QueryBuilder::append(string ws, string ds, string b, string f) {
  washS = ws.substr(0, 2);
  dryS = ds.substr(0, 2);
  build = b.substr(0, 3);
  full = setup + "\?was=" + washS + "\?dry=" + dryS + "\?bu=" + build + "\?f=" + f;
}
