#ifndef CUSTOMERPROFILECONTROLLER_H
#define CUSTOMERPROFILECONTROLLER_H

#include <string>
#include <iostream>
#include "sqlite3.h"

class CustomerProfileController
{
    private:
		sqlite3* db;

    public:
        //constructors
        CustomerProfileController(sqlite3* d);
    
		//functions
		std::string registerExistingCustomer(std::string,std::string);
		void findCustomer();
		void createCustomer();
		void editCustomer(std::string,std::string);
		void deleteCustomer();

};

#endif // CUSTOMERPROFILECONTROLLER_H
