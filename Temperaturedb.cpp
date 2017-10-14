#include "Temperaturedb.h"

#include <string>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <sstream>
#include <math.h>
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
void TemperatureDatabase::findAVG(int loc, int start, int end){
	Node* curr = records.getHead();
	int    count = 0;
	double total = 0.;
	
	while(curr->location < loc && curr != NULL){
		curr = curr->next;
	}
	while(curr->location == loc && curr->year >= start && curr->year <= end){
		count++;
		total += curr->temp;
		curr = curr->next;
	}
	double average = 0.;
	if(count != 0){
		average = total / count;
		queries.insert_Q(loc, start, end, 1, average);
	}
}
void TemperatureDatabase::findMode(int loc, int start, int end){
	vector<int> pos (51, 0); //Includes 0
	vector<int> neg (50, 0); //All negative 
	Node* curr = records.getHead();
	
	while(curr->location != loc && curr != NULL){
		curr = curr->next;
	}
	while(curr->location == loc && curr->year >= start && curr->year <= end){
		double data = curr->temp;
		
		if(data >= 0){
			data = round(data);
			pos.at(data) += 1;
		}
		else{
			data = round(data);
			neg.at(-data - 1) += 1;
		}
		curr = curr->next;
	}
	int iter = 0;
	int mode = 0;
	
	for(int i = 0; i < pos.size();i++){
		if(pos.at(i) > iter){
			mode = i;
			iter = pos.at(i);
		}
	}
	for(int i = 0; i < neg.size();i++){
		if(neg.at(i) > iter){
			mode = -i -1;
			iter = neg.at(i);
		}
	}
	queries.insert_Q(loc, start, end, 2, mode);
}
double TemperatureDatabase::round(double data){
	double temp = data;
	if(data >= 0){
		if((temp - floor(data)) >= .5){
			return ceil(data);
		}
		else{
			return floor(data);
		}
	}
	else{
		if(-(temp) - -(floor(data)) >= .5){
			return ceil(data);
		}
		else{
			return floor(data);
		}
	}
}
void TemperatureDatabase::loadData(const string& filename) {
	int currYear = 2017;
	int count    = 0;
	
	ifstream inFS("s050_TX-2000-2015.dat");
		if(!inFS.is_open()){
			cout << "Could not open file." << endl;
		}
		else{
			while(!inFS.eof()){
				try{
					int loca, year, mont;
					double data;
					inFS >> loca >> year >> mont >> data;
                 if(loca > 99999 && loca < 1000000){ 
					if(year > 1799 && year < currYear){
						if(mont > 0 && mont < 13){
							if(data > -51 && data < 51){
								records.insert(loca, year, mont, data);
								count++;
							}
							else
								throw runtime_error("Invalid data. Node not created.");
						}
						else
							throw runtime_error("Invalid month. Node not created.");
					}
					else
						throw runtime_error("Invalid year. Node not created.");
				}
                 else{
                  	throw runtime_error("Invalid location. Node not created.");
                }
			}
            catch(const runtime_error& e){
				cout << e.what() << endl;
			} 
		}
        }
	inFS.close();
	return;
}
void TemperatureDatabase::performQuery(const string& filename) {	
	ifstream inFS("queries-2000s.dat");
	if(!inFS.is_open()){
		cout << "Could not open file." << endl;
	}
	else{
		while(!inFS.eof()){
			try{
				int loca, start, end;
				string type;
				inFS >> loca >> type >> start >> end;
             	if(!(loca > 99999 && loca < 999999)){
                	throw runtime_error("Invalid format");
                }
             	if(!(start > 1799 && start < 2018) || !(end > 1799 && end < 2019) || (end < start)){
                	throw runtime_error("Invalid format");
             	}
                bool good = records.checkData(loca, start, end);
				if(!good){
					if(type == "AVG"){
						queries.insert_Q(loca, start, end, 1, -999);
					}
					else{
						queries.insert_Q(loca, start, end, 2, -999);
					}
				}
				if((type == "AVG" || type == "MODE") && good){
					if(type == "AVG"){
						findAVG(loca, start, end);
					}
					if(type == "MODE"){
						findMode(loca, start, end);
					}
				}
			}
			catch(const runtime_error& e){
				cout << e.what() << endl;
			}
		}
	}
 	ofstream oFS("results.dat");
	if (!oFS.is_open()) {
		cout << "Could not open output stream" << endl;
	}
	oFS << this->queries; 
	return;
}
