#ifndef BOOKINGMANAGERUI_H
#define BOOKINGMANAGERUI_H

#include <string>
#include "sqlite3.h"

using namespace std;

class BookingManagerUI
{
    public:
        BookingManagerUI(sqlite3*);
        bool run();
    protected:
    private:
		sqlite3* db;
        string userType;
};

#endif // BOOKINGMANAGERUI_H
