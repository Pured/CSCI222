//
//  ServiceItem.h
//  FlightSystem
//
//  Created by Darryl Murphy on 5/04/15.
//

#ifndef ___FlightSystem__ServiceItem__
#define ___FlightSystem__ServiceItem__

#include <iostream>
#include "sqlite3.h"

class ServiceItem{
private:
	sqlite3* db;
    int ID;
    std::string item;
    float cost;
    std::string avail;
    
public:
    //constructors
    ServiceItem(sqlite3* d);
    
    //get functions
    int getID() const;
    std::string getItem() const;
    float getCost() const;
    std::string getAvail() const;
	std::string getByID(int);

    //set functions
    void setID(int);
    void setItem(std::string);
    void setCost(float);
    void setAvail(std::string);
	int update();

    //other functions
    friend std::ostream &operator<<( std::ostream &output,const ServiceItem &S);
};

#endif /* defined(___FlightSystem__ServiceItem__) */
