//
//  TravelAgent.h
//  FlightSystem
//
//  Created by Darryl Murphy on 5/04/15.
//

#ifndef ___FlightSystem__TravelAgent__
#define ___FlightSystem__TravelAgent__

#include <iostream>

class TravelAgent{
private:
    int ID;
    std::string name;
    std::string phone;
    std::string email;
    
public:
    //constructors
    TravelAgent();
    TravelAgent(int,std::string,std::string,std::string);
    
    //get functions
    int getID() const;
    std::string getName() const;
    std::string getPhone() const;
    std::string getEmail() const;

    //set functions
    void setID(int);
    void setName(std::string);
    void setPhone(std::string);
    void setEmail(std::string);

    //other functions
    friend std::ostream &operator<<( std::ostream &output, const TravelAgent &T);

};

#endif /* defined(___FlightSystem__TravelAgent__) */
