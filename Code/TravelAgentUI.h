
#ifndef TravelAgentUI_H
#define TravelAgentUI_H

#include <iostream>
#include <string>
#include "sqlite3.h"

using namespace std;


class TravelAgentUI
{
public:
    TravelAgentUI(sqlite3*);
    bool run();
    //void bookFlights();
    void bookingsMade();
    void addCustomer();
    void editDetails();
protected:
private:
    sqlite3* db;
    std::string userType;
};

#endif /* defined(____TravelAgentUI__) */
