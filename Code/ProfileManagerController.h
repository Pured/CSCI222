/*=============================================================
| Modified by: kb100
| Version: 1.00
| Modification: Added all of the functions.
|==============================================================*/

#ifndef PROFILEMANAGERCONTROLLER_H
#define PROFILEMANAGERCONTROLLER_H

#include <iostream>
#include "sqlite3.h"

using namespace std;

class ProfileManagerController{
public:
	ProfileManagerController(sqlite3*);

	void findCustomer();
	void profileReport();
private:
	sqlite3* db;
	string userType;
};

#endif // PROFILEMANAGERCONTROLLER_H
