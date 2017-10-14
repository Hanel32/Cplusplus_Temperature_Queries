#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "linkedlist.h"
using namespace std;

namespace patch
{
    template <typename T>std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}
LinkedList::LinkedList(): head(NULL), tail(NULL){return;}
LinkedList::~LinkedList() {
	cout << "Destructing : " << this->head << endl;
	Node* current = this->head;
	while (current != NULL) {
		Node* deleteNode = current;
		current = current->next;
		delete deleteNode;
	}
}
LinkedList::LinkedList(const LinkedList& source) {
	Node* newNode;
	Node* oldNode = source.head;
	
	this->head = NULL;
	if(oldNode != NULL){
		newNode = new Node;
		newNode->location = oldNode->location;
		newNode->year     = oldNode->year;
		newNode->month    = oldNode->month;
		newNode->temp     = oldNode->temp;
		newNode->query    = oldNode->query;
		newNode->next     = oldNode->next;
		this->head = newNode;
		Node* curr = this->head;
		oldNode = oldNode->next;
		while(oldNode != NULL){
			newNode = new Node;
			newNode->location = oldNode->location;
			newNode->year     = oldNode->year;
			newNode->month    = oldNode->month;
			newNode->temp     = oldNode->temp;
			newNode->query    = oldNode->query;
			newNode->next     = oldNode->next;
			curr->next = newNode;
			curr = curr->next;
			oldNode = oldNode->next;
		}
	}
}
LinkedList& LinkedList::operator=(const LinkedList& source) {
	Node* oldNode = source.head;
	Node* newNode;
	clear();
	cout << endl;
	if(oldNode != NULL){
		newNode = new Node;
		newNode->location = oldNode->location;
		newNode->year     = oldNode->year;
		newNode->month    = oldNode->month;
		newNode->temp     = oldNode->temp;
		newNode->query    = oldNode->query;
		newNode->next     = oldNode->next;
		this->head = newNode;
		Node* curr = this->head;
		oldNode = oldNode->next;
		while(oldNode != NULL){
			newNode = new Node;
			newNode->location = oldNode->location;
			newNode->year     = oldNode->year;
			newNode->month    = oldNode->month;
			newNode->temp     = oldNode->temp;
			newNode->query    = oldNode->query;
			newNode->next     = oldNode->next;
			curr->next = newNode;
			curr = curr->next;
			oldNode = oldNode->next;
		}
	}
	return *this;
}
void LinkedList::insert(int location, int year, int month, double temperature) {
	Node* n    = new Node(location, year, month, temperature);
	Node* temp;
	Node* curr = head;
	
	if(isEmpty()){head = n; tail = n; return;} //Assigns the node as head/tail of the list if the list is empty.
	if(n->location < curr->location){
		n->next = curr;
		head    = n;
	}
	while(n->location > curr->location){
		if(curr->next == NULL){
			curr->next = n;
			n->next = NULL;
			return;
		}
		temp = curr;
		curr = curr->next;
	}
	if(n->location == curr->location){
		while(n->year > curr->year){
			if(curr->next == NULL){
				curr->next = n;
				n->next = NULL;
				return;
			}
			temp = curr;
			curr = curr->next;
		}
		if(n->year == curr->year){
			while(n->month > curr->month){
				if(curr->next == NULL){
					curr->next = n;
					n->next = NULL;
					return;
				}
				temp = curr;
				curr = curr->next;
			}
			if(n->month == curr->month){
				while(n->temp > curr->temp){
					if(curr->next == NULL){
						curr->next = n;
						n->next = NULL;
						return;
					}
					temp = curr;
					curr = curr->next;
				}
			}
			else{
				temp->next = n;
				n->next = curr;
             	return;
			}
		}
		else{
			temp->next = n;
			n->next = curr;
         	return;
		}
	}
	else{
		temp->next = n;
		n->next = curr;
     	return;
	}
 return;
}
void LinkedList::insert_Q(int location, int startYear, int endYear, int type, double data){
	Node* temp  = new Node(location, startYear, endYear, data);
	temp->type  = type;
	
	if(data == -999){
		temp->query = "unknown";
	}
	else{
		temp->query = patch::to_string(data);
	}
	if(this->head == NULL && this->tail == NULL){
		this->head = temp;
		this->tail = temp;
		return;
	}
	else{
		Node* curr = head;
		while(curr->next != NULL){
			curr = curr->next;
		}
		curr->next = temp;
		return;
	}
}
void LinkedList::clear() {
	Node* current = this->head;
	while (current != NULL) {
		Node* deleteNode = current;
		current = current->next;
		delete deleteNode;
	}
return;
}

void LinkedList::print() const {
	/* Do not modify this function */
	print(cout);
 return;
}

void LinkedList::print(ostream& os) const {
	/* Do not modify this function */
	os << *this;
 return;
}

ostream& operator<<(ostream& os, const LinkedList& ll) {	
    Node *c;
        for(c = ll.head; c != 0; c = c -> next){
         	if(c->type != 0){
            	os << c -> location << ' ' << c -> year << ' ' << c->month << ' ';
            	if(c->type == 1){
            		os << "AVG" << ' ';
				}
				if(c->type == 2){
					os << "MODE" << ' ';
				}
				os << c->query << endl;
        	}
         	else{
            	os << c -> location << ' ' << c -> year << ' ' << c->month << ' ' << c->temp << endl;
            }
        }
        return os;
}
bool LinkedList::isEmpty(){
	if(this->head == NULL && this->tail == NULL){
		return true;
	}
	return false;
}
Node* LinkedList::getHead(){
	return this->head;
}
bool LinkedList::checkData(int loc, int start, int end){
	Node* curr = head;
	
	while(curr->location != loc && curr != NULL){
		curr = curr->next;
	}//Should be at right location
	while(curr->location == loc && curr->year > start && curr != NULL){
		curr = curr->next;
	}
	if(curr->location == loc && curr->year >= start && curr->year <= end){
		return true;
	}
	return false;
}
