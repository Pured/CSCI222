/*=============================================================
| Modified by: kb100
| Version: 1.00
| Modification: Added all of the functions.
|==============================================================*/

#ifndef SERVICEMANAGERCONTROLLER_H
#define SERVICEMANAGERCONTROLLER_H

#include <iostream>
#include "sqlite3.h"

using namespace std;

class ServiceManagerController{
public:
	ServiceManagerController(sqlite3*);

	void findFlight();
	void findService();
	void createService();
	void editService();
	void deleteService();
	void serviceReport();
private:
	sqlite3* db;
	string userType;
};

#endif // SERVICEMANAGERCONTROLLER_H
