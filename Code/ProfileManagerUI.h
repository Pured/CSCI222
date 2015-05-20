/*=============================================================
| Modified by: kb100
| Version: 1.01
| Modification: Added all of the functions.
|==============================================================*/

#ifndef PROFILEMANAGERUI_H
#define PROFILEMANAGERUI_H

#include <iostream>
#include "sqlite3.h"

using namespace std;

class ProfileManagerUI{
public:
	ProfileManagerUI(sqlite3*);
	bool run();
private:
	sqlite3* db;
	string userType;
};

#endif // PROFILEMANAGERUI_H
