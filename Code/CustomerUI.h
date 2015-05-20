#ifndef CUSTOMERUI_H
#define CUSTOMERUI_H

#include <iostream>
#include "sqlite3.h"
#include <string>

using namespace std;

class CustomerUI
{
    public:
        CustomerUI(sqlite3*);
        bool run();
		void setUsername(std::string);
        void manageFlights();
        void manageServices();
        void manageDetails();
		
    private:
		sqlite3* db;
        string userType;
		string username;
};

#endif // CUSTOMERUI_H
