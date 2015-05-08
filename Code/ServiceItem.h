//
//  ServiceItem.h
//  FlightSystem
//
//  Created by Darryl Murphy on 5/04/15.
//

#ifndef ___FlightSystem__ServiceItem__
#define ___FlightSystem__ServiceItem__

#include <iostream>

class ServiceItem{
private:
    int ID;
    std::string item;
    float cost;
    std::string avail;
    
public:
    //constructors
    ServiceItem();
    ServiceItem(int,std::string,float,std::string);
    
    //get functions
    int getID() const;
    std::string getItem() const;
    float getCost() const;
    std::string getAvail() const;

    //set functions
    void setID(int);
    void setItem(std::string);
    void setCost(float);
    void setAvail(std::string);

    //other functions
    friend std::ostream &operator<<( std::ostream &output,const ServiceItem &S);
};

#endif /* defined(___FlightSystem__ServiceItem__) */
