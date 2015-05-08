#ifndef SERVICEMANAGERUI_H
#define SERVICEMANAGERUI_H

#include <iostream>
#include "sqlite3.h"

using namespace std;

class ServiceManagerUI
{
    public:
        ServiceManagerUI(sqlite3*);
        bool run();
    protected:
    private:
		sqlite3* db;
        string userType;
};

#endif // SERVICEMANAGERUI_H
