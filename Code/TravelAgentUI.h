/*=============================================================
| Modified by: kb100
| Version: 1.01
| Modification: Restyled the code.
|==============================================================*/

#ifndef TravelAgentUI_H_
#define TravelAgentUI_H_

#include <string>
#include "sqlite3.h"

class TravelAgentUI{
public:
    TravelAgentUI(sqlite3 *);

    bool run();
    //void bookFlights();
    void bookingsMade();
    void addCustomer();
    void editDetails();

private:
    sqlite3 *db;
    std::string userType;
};

#endif // TravelAgentUI_H_
