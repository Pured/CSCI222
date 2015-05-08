#ifndef CUSTOMERUI_H
#define CUSTOMERUI_H

#include <iostream>
#include "sqlite3.h"

using namespace std;

class CustomerUI
{
    public:
        CustomerUI(sqlite3*);
        bool run();
        void manageFlights();
        void manageServices();
        void manageDetails();
		
    private:
		sqlite3* db;
        string userType;
};

#endif // CUSTOMERUI_H
