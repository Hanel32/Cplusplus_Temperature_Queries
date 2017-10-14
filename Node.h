#ifndef NODE
#define NODE

#include <string>
// Include the header file for the data struct/class if you use one.
// For example, if you have a data class in data.h, put
//  #include "data.h"
// below.

struct Node {
	Node*  next;
	int    location;
	int    year;    //Aka Start
	int    month;   //Aka Stop
	double temp;
	std::string query;
	int    type;

	Node() : next(NULL) {}
	Node(int location, int year, int month, double temp) : next(NULL), location(location),
		year(year), month(month), temp(temp), type(0) {}
	virtual ~Node() {}
};

#endif
