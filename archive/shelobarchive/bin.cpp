#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <streambuf>
#include <unistd.h>
#include <dirent.h> 
#include <stdio.h>
#include <cstring>

using namespace std;

string read_entire_file(string path) {
	std::ifstream t(path.c_str());
	std::string str;

	t.seekg(0, std::ios::end);   
	str.reserve(t.tellg());
	t.seekg(0, std::ios::beg);

	str.assign((std::istreambuf_iterator<char>(t)),
        	std::istreambuf_iterator<char>());

	return str;
}

std::string getcwd() {
    char buf[FILENAME_MAX];
    char* succ = getcwd(buf, FILENAME_MAX);
    if( succ ) return std::string(succ);
    return "";  // raise a flag, throw an exception, ...
}

bool get_status() {
        string status = read_entire_file("status.txt");
	if (status[7] == 'o' && status[8] == 'n') 
		return true;
	else
		return false;
	//return(status[0] == 'o' && status[1] == 'n') ? true : false;
}

void listdir() {
DIR           *d;
  struct dirent *dir;
  d = opendir(".");
  if (d)
  {
    while ((dir = readdir(d)) != NULL)
    {
      printf("%s\n", dir->d_name);
    }

    closedir(d);
  }
}

int main() {
	cout << "Content-type: text/html; charset=UTF-8\n" << endl;
	string query = getenv("QUERY_STRING");
	cout<<query;
	bool status = get_status();
	if (status) {
		cout << read_entire_file("green.html") << endl;
	}
	else {
		cout << read_entire_file("red.html") << endl;
	}
	//std::string line;
	//while (std::getline(std::cin, line)) {
	//	std::cout << line << std::endl;
	//}
	return 0;
}

