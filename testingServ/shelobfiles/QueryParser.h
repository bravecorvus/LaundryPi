#ifndef _QUERY_H_
#define _QUERY_H_

#include <string>
#include <iostream>
using namespace std;

/** Class to parse strings from cURL transfer to logfiles */
class QueryParser {
  string state;
  string machine;
  string building;
  string fl;
 public:
  QueryParser(string);

  void parse(string);
  void log_status();

  string get_status(string, string, string);
};

#endif
