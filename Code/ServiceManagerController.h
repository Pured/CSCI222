/*=============================================================
| Modified by: kb100
| Version: 1.02
| Modification: Restyled the code.
|==============================================================*/

#ifndef SERVICEMANAGERCONTROLLER_H_
#define SERVICEMANAGERCONTROLLER_H_

#include "sqlite3.h"

class ServiceManagerController{
public:
	ServiceManagerController(sqlite3 *);

	void findFlight();
	void findService();
	void createService();
	void editService();
	void deleteService();
	void serviceReport();

private:
	sqlite3 *db;
	string userType;
};

#endif // SERVICEMANAGERCONTROLLER_H_
