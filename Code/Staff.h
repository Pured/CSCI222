#ifndef STAFF_H
#define STAFF_H

#include <string>
#include <iostream>
#include "sqlite3.h"

class Staff
{
    private:
		sqlite3* db;
        std::string userType;
        std::string userName;
        std::string password;
    
    public:
        //constructors
        Staff(sqlite3* d);
        Staff(sqlite3*,std::string uType,std::string uName, std::string pw);
    
        //get functions
        std::string getUsername() const;
        std::string getPassword() const;
        std::string getType() const;
    
        //set functions
        void setUsername(std::string);
        void setPassword(std::string);
        void setType(std::string);
		std::string setByEmail(std::string e);
    
        //other functions
        friend std::ostream &operator<<( std::ostream &output,const Staff &S);

};

#endif // STAFF_H
