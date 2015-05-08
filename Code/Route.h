//
//  Route.h
// FlightSystem
//
//  Created by Darryl Murphy on 5/04/15.
//

#ifndef ___FlightSystem__Route__
#define ___FlightSystem__Route__

#include <iostream>

class Route{
private:
    int ID;
    std::string srcAirport;
    std::string destAirport;
    char codeshare;
    int stops;
    
public:
    //constructors
    Route();
    Route(int i, std::string src, std::string dest,char cs,int s);
    
    //get functions
    int getID() const;
    std::string getSrc() const;
    std::string getDest() const;
    char getCodeshare() const;
    int getStops() const;
    
    //set Functions
    void setID(int);
    void setSrc(std::string);
    void setDest(std::string);
    void setCodeshare(char);
    void setStops(int);
    
    //other functions
    friend std::ostream &operator<<( std::ostream &output,const Route &R);
    
};

#endif /* defined(___FlightSystem__Route__) */
