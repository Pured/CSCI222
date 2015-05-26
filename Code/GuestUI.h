#ifndef GUESTUI_H
#define GUESTUI_H

#include "GuestUI.h"
#include <string>
#include "sqlite3.h"

class GuestUI
{
    public:
        GuestUI(sqlite3* d);
        
        std::string getType();
        int getNum();
        void setType(std::string type);
        void setNum(int num);
        int run();
        void login();
		void registerExistingCustomer();
		void guestSearch();
		std::string getPass(const char *);  //mask password input

    protected:
    private:
		sqlite3* db;
        std::string userType;
        int userNum;
};


#endif // GUESTUI_H
