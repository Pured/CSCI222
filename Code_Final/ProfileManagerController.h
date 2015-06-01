/*=============================================================
| Modified by: kb100
| Version: 1.01
| Modification: Restyled the code.
|==============================================================*/

#ifndef PROFILEMANAGERCONTROLLER_H_
#define PROFILEMANAGERCONTROLLER_H_

#include "sqlite3.h"

class ProfileManagerController{
public:
	ProfileManagerController(sqlite3 *);

	void findCustomer();
	void profileReport();
private:
	sqlite3 *db;
	std::string userType;
};

#endif // PROFILEMANAGERCONTROLLER_H_
