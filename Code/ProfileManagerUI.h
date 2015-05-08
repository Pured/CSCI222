#ifndef PROFILEMANAGERUI_H
#define PROFILEMANAGERUI_H

#include <iostream>
#include "sqlite3.h"

using namespace std;

class ProfileManagerUI
{
    public:
        ProfileManagerUI(sqlite3*);
        bool run();
    protected:
    private:
		sqlite3* db;
        string userType;

};

#endif // PROFILEMANAGERUI_H
