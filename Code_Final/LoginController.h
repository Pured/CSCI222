/*=============================================================
| Modified by: kb100
| Version: 1.01
| Modification: Restyled the code.
|==============================================================*/

#ifndef LOGINCONTROLLER_H_
#define LOGINCONTROLLER_H_

#include <string>
#include "sqlite3.h"

class LoginController{
private:
    sqlite3 *db;

public:
    // Constructors.
    LoginController(sqlite3 *d);
    
    // Functions.
    std::string validateLogin(std::string, std::string);
    std::string validateStaffLogin(std::string, std::string);
    std::string validateCustomerLogin(std::string, std::string);
    std::string validateTravelAgentLogin(std::string, std::string);
};

#endif // LOGINCONTROLLER_H_
