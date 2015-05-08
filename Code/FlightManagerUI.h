#ifndef FLIGHTMANAGERUI_H
#define FLIGHTMANAGERUI_H

#include <iostream>
#include "sqlite3.h"

using namespace std;

class FlightManagerUI
{
    public:
        FlightManagerUI(sqlite3*);
        bool run();
    protected:
    private:
		sqlite3* db;
        string userType;
};

#endif // FLIGHTMANAGERUI_H
