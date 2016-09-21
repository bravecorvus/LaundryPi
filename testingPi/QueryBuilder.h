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
  string machineState;
  string machineType;
  string build;
  string f;
 public:
  QueryBuilder(void);
  //washer status, dryer status, building, floor
  QueryBuilder(string, string, string, string);
  QueryBuilder(string, string, string);

  void append(string, string, string, string);
  void append(string, string, string);
  void append(string);
  string get_str(void);

};

#endif
