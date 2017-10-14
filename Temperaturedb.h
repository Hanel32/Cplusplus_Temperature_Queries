#ifndef TEMP_DB
#define TEMP_DB

#include <string>
#include "linkedlist.h"

class TemperatureDatabase {
public:
	// Default constructor/destructor. Modify them if you need to.
	TemperatureDatabase() {}
	~TemperatureDatabase() {}
	double round(double data);
	void findMode(int loc, int start, int end);
	void findAVG(int loc, int start, int end);

	// The two functions below are required

	// Read the temperature records from the data file and populate the linked list
	void loadData(const std::string& data_file);

	// Read the queries from the query file and perform a series of queries
	void performQuery(const std::string& query_filename);

private:
	// Linked list to store the temperature records. You need to properly populate
	// this link list.
	LinkedList records;
	LinkedList queries;

	// You can add any private member variables/functions you feel useful in this class.
};

#endif  // TEMP_DB
