#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include <string>
#include <iostream>
#include "sqlite3.h"

class LoginController
{
    private:
		sqlite3* db;

    public:
        //constructors
        LoginController(sqlite3* d);
    
		//functions
		std::string validateLogin(std::string,std::string);
		std::string validateStaffLogin(std::string,std::string);
		std::string validateCustomerLogin(std::string,std::string);

};

#endif // LOGINCONTROLLER_H
