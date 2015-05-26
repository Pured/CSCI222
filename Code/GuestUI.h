/*=============================================================
| Modified by: kb100
| Version: 1.01
| Modification: Restyled the code.
|==============================================================*/

#ifndef GUESTUI_H_
#define GUESTUI_H_

#include <string>
#include "sqlite3.h"

class GuestUI{
public:
        GuestUI(sqlite3 *d);
        
        std::string getType();
        int getNum();
        void setType(std::string type);
        void setNum(int num);
        int run();
        void login();
		void registerExistingCustomer();
		void guestSearch();
        std::string getPass(const char *);  // Mask password input.

private:
	sqlite3 *db;
	std::string userType;
	int userNum;
};

#endif // GUESTUI_H_
