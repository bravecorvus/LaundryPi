#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;
string get_status(string status) {
        if (status[14] == 'o' && status[15] == 'n')
                return "available";


	else
                return "occupied";
        //return(status[0] == 'o' && status[1] == 'n') ? true : false;
        //
        }
int main() {
  /* cout << "Content-type: text/plain; charset=UTF-8\n" << endl;
        const char* query = getenv("QUERY_STRING");
        string qs;
        if (query != NULL)
                qs = query;
        cout << query << endl;
        string status = get_status(query);*/
        ofstream f;
        f.open("test.html");
        //f<<qs<<endl;
	f << "<!DOCTYPE html>" << endl;
	f << "<html>" << endl;

	f << "<head>" << endl;
	f << "<link href=\"http://s3.amazonaws.com/codecademy-content/courses/ltp/css/shift.css\" rel=\"stylesheet\">" << endl;
    
	f << " <link rel=\"stylesheet\" href=\"http://s3.amazonaws.com/codecademy-content/courses/ltp/css/bootstrap.css\">" << endl;
	f << "<link rel=\"stylesheet\" href=\"main.css\">" << endl;
	f << "<style>" << endl;
	f<< "ul#menu {" << endl;
        f<< "padding: 0;"<< endl;
	f << "}" << endl;

        f<< "ul#menu li {" << endl;
        f << "display: inline;" << endl;
	f<< "}" << endl;

	f << "ul#menu li a {background-color: black;color: white;padding: 10px 20px;text-decoration: none;border-radius: 4px 4px 0 0;}ul#menu li a:hover {background-color: orange;}</style>" << endl;
	f <<"</head>"<< endl;
	f <<"<body>" << endl;
	f << "<div class = \"nav\">" << endl;
        f << "<ul id = \"menu\">" << endl;
	f << "<li><a href=\"#Ellingson\">Ellingson</a></li><li><a href=\"#Hoyme\">Hoyme</a></li><li><a href=\"#Larson\">Larson</a></li>"<<  endl;
	f << "<li><a href=\"#Thorson\">Thorson</a></li><li><a href=\"#Kildal\">Kildal</a></li>"<< endl;
	f << "<li><a href=\"#Rand\">Rand</a></li>"<< endl;
	f << "<li><a href=\"#Ytterboe\">Ytterboe</a></li>" << endl;
	f << "<li><a href=\"#Hillboe\">Hillboe</a></li>" << endl;
	f << "<li><a href=\"#Kittelsby\">Kittelsby</a></li>" << endl;
	f << "<li><a href=\"#Mohn\">Mohn</a></li>" << endl;
	f << "<li><a href=\"#Melby\">Melby</a></li>" << endl;
	f << "</ul>" << endl;
	f << "<div class=\"jumbotron\">" << endl;
        f << "<div class=\"container\">" << endl;
        f << "<h1>Washer Status Indicator</h1>" << endl;
        f << "<p>Making laundry easier since 2016.</p>" << endl;
	f << "</div>" << endl;
	f << "</div>" << endl;

	  /*	
    <div class=\"Dorms\">
         <div class="container">
            <h2>Dorms</h2>
            <p>Choose your dorm below.</p>
            <div class="row">
                <div class="col-md-4">
                  <div class="thumbnail">
                      <img width=300 src="http://wp.stolaf.edu/map/files/2013/11/Ellingson1.gif" >
                  </div>
                    <div class="thumbnail">
                      <img width=300 src="http://pages.stolaf.edu/admissionsblog/files/2013/07/Photo1.jpg" >
                    </div>
                </div>
                <div class="col-md-4">
                    <div class="thumbnail">
                      <img width=200 src="larson.jpg" >
                    </div>
                    <div class="thumbnail">
                      <img width=300 src="http://wp.stolaf.edu/map/files/2013/11/Thorson2.gif" >
                    </div>
                </div>
                <div class="col-md-4">
                    <div class="thumbnail">
                      <img  width=300 src="http://pages.stolaf.edu/admissionsblog/files/2013/07/Photo1-2-300x225.jpg" >
                    </div>
                </div>
            </div>
         </div>
    </div>
	  */
	f << "<div class=\"learn-more\">" << endl;
	f << "<div class=\"container\">" << endl;
	f << "<div class=\"row\">" << endl;
	f << "<div class=\"col-md-4\">" << endl;
	f << "<h3>How it Works</h3>" << endl;
	f << "<p>...</p>" << endl;
	f << "</div>" << endl;
	f << "<div class=\"col-md-4\">" << endl;
	f << "<h3>Future Updates</h3>" << endl;
	f << "<p>...</p>" << endl;
	f << "</div>" << endl;
	f << "<div class=\"col-md-4\">"<< endl;
	f << "<h3>The Team</h3>" << endl;
	f << "<p>...</p>" << endl;
	f << "</div>" << endl;
	f << "</div>" << endl;
	f << "</div>" << endl;
	f << "</div>" << endl;	
	f << "<div class=\"dorm list\">" << endl;
	f << "<h2 id=\"Ellingson\">Ellingson</h2>" << endl;
        f << "<h4>Washer 1- </h4>" << endl;
	f << "<h4>Dryer 1- </h4>" << endl;
	f << "<h2 id=\"Hoyme\">Hoyme</h2>" << endl;
        f << "<h4>Washer 1- </h4>" << endl;
	f << "<h4>Dryer 1- </h4>" << endl;
	f << "<h2 id=\"Larson\">Larson</h2>"<< endl;
        f << "<h4>Washer 1- </h4>" << endl;
	f << "<h4>Dryer 1- </h4>" << endl;
	f << "<h2 id=\"Thorson\">Thorson</h2>" << endl;
        f << "<h4>Washer 1- </h4>" << endl;
	f << "<h4>Dryer 1- </h4>" << endl;
	f << "<h2 id=\"Rand\">Rand</h2>" << endl;
        f << "<h4>Washer 1- </h4>" << endl;
	f << "<h4>Dryer 1- </h4>" << endl;
	f << "<h2 id=\"Ytterboe\">Ytterboe</h2>" << endl;
        f << "<h4>Washer 1- </h4>" << endl;
	f << "<h4>Dryer 1- </h4>" << endl;
	f << "<h2 id=\"Hilleboe\">Hillboe</h2>" << endl;
        f << "<h4>Washer 1- </h4>" << endl;
	f << "<h4>Dryer 1- </h4>" << endl;
	f << "<h2 id=\"Kittelsby\">Kittelsby</h2>" << endl;
        f << "<h4>Washer 1- </h4>" << endl;
	f << "<h4>Dryer 1- </h4>" << endl;
	f << "<h2 id=\"Mohn\">Mohn</h2>" << endl;
        f << "<h4>Washer 1- </h4>" << endl;
	f << "<h4>Dryer 1- </h4>" << endl;
	f << "<h2 id=\"Melby\">Melby</h2>" << endl;
        f << "<h4>Washer 1- </h4>" << endl;
	f << "<h4>Dryer 1- </h4>" << endl;
	f << "</div>" << endl;
	f << "</body>" << endl;
	f << "</html>" << endl;




	/*
	f << "<h2>An HTML file printed from C++</h2>\n";
        f << "<h1>This is a test</h1>\n";
        f << "<h3>The washing machine is " <<status<<" </h3>\n";
	*/
        f.close();

        return 0;
}
    
