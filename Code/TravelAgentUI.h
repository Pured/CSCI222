/*=============================================================
| Modified by: kb100
| Version: 1.01
| Modification: Restyled the code.
|==============================================================*/

#ifndef TravelAgentUI_H_
#define TravelAgentUI_H_

#include <string>
#include <stdlib.h>
#include "sqlite3.h"

class TravelAgentUI{
public:
    TravelAgentUI(sqlite3 *);
    TravelAgentUI(sqlite3 *, std::string e);
    bool run();
    //void bookFlights();
    void bookingsMade();
    void editDetails();
    void viewDetails();

private:
    sqlite3 *db;
    std::string userType;
    std::string email;
};

#endif // TravelAgentUI_H_
