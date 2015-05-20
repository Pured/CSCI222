/*=============================================================
| Modified by: kb100
| Version: 1.01
| Modification: Connected the UI to the Controller.
|==============================================================*/

#ifndef SERVICEMANAGERUI_H
#define SERVICEMANAGERUI_H

#include <iostream>
#include "sqlite3.h"

using namespace std;

class ServiceManagerUI{
public:
	ServiceManagerUI(sqlite3*);

	bool run();
	void serviceItemUI();
private:
	sqlite3* db;
	string userType;
};

#endif // SERVICEMANAGERUI_H
