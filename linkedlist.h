#ifndef LINKEDLIST
#define LINKEDLIST

#include <iostream>
#include <string>
#include "Node.h"

class LinkedList {
private:
	Node* head;
	Node* tail;

public:
	LinkedList();
	~LinkedList();
	LinkedList(const LinkedList& other);
	LinkedList& operator=(const LinkedList& other);
	void insert(int location, int year, int month, double temperature);
	void insert_Q(int location, int startYear, int endYear, int type, double data);
	bool checkData(int loc, int start, int end);
	void clear();
	bool isEmpty();
	Node* getHead();
	friend std::ostream& operator<<(std::ostream&, const LinkedList&);

	// The functions below are written already. Do not modify them.
	void print() const;
	void print(std::ostream&) const;
};

#endif
