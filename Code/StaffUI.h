#ifndef STAFFUI_H
#define STAFFUI_H

#include <iostream>
#include "sqlite3.h"

using namespace std;

class StaffUI
{
    public:
        StaffUI(sqlite3* d);
        bool run();

    protected:
    private:
		sqlite3* db;
        string userType;
        int userNum;
};

#endif // STAFFUI_H
