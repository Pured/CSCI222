/*=============================================================
| Modified by: kb100
| Version: 1.01
| Modification: Restyled the code.
|==============================================================*/

#ifndef GUESTUI_H_
#define GUESTUI_H_

#include <string>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
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
#ifdef __unix__
	std::string getpass_lin(const char *);  // Mask password input.
    int getch();    //getch() function, references structs in termios.h, called by getpass()
#endif
#ifdef _WIN32
    std::string getpass_win(const char *);  // Mask password input.
#endif
    
private:
	sqlite3 *db;
	std::string userType;
	int userNum;
};

#endif // GUESTUI_H_
