#ifndef _QUERY_H_
#define _QUERY_H_

#include <string>
#include <iostream>
using namespace std;
/** Class to prepare strings for cURL to transfer to server */
class QueryBuilder {
  string cmd;
  string args;
  string address;
  string setup;
  string full;
  string washS;
  string dryS;
  string build;
  string f;
 public:
  QueryBuilder(void);
  //washer status, dryer status, building, floor
  QueryBuilder(string ws, string ds, string b, string f);

  void append(string ws, string ds, string b, string f);
  string get_str(void);
};

#endif
