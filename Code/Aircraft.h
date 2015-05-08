//
//  Aircraft.h
// CSCI222 FlightDB
//

#ifndef ___FlightSystem__Aircraft__
#define ___FlightSystem__Aircraft__

#include <iostream>
#include "sqlite3.h"

class Aircraft{
private:
	sqlite3* db;
    int ID;
    std::string name;
    int inService;
    int fClass;
    int bClass;
    int peClass;
    int eClass;
    int totalSeats;
    
public:
    //Constructors
    Aircraft(sqlite3*);
    
    //get functions
    int getID() const;
    std::string getName() const;
    int getInService() const;
    int getFClass() const;
    int getBClass() const;
    int getPEClass() const;
    int getEClass() const;
    int getTotalSeats() const;
	std::string getByID(std::string);

    //set functions
    void setID(int);
    void setName(std::string);
    void setInService(int i);
    void setFClass(int);
    void setBClass(int);
    void setPEClass(int);
    void setEClass(int);
    void setTotalSeats();
	int update();
	
	//other functions
	friend std::ostream &operator<<( std::ostream &os,const Aircraft &A);
};

#endif /* defined(___FlightSystem__Aircraft__) */
