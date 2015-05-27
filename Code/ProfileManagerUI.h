/*=============================================================
| Modified by: kb100
| Version: 1.03
| Modification: Added customerAccessMenu().
|==============================================================*/

#ifndef PROFILEMANAGERUI_H_
#define PROFILEMANAGERUI_H_

#include "sqlite3.h"

class ProfileManagerUI{
public:
	ProfileManagerUI(sqlite3 *);

	bool run();
	void customerAccessMenu();

private:
	sqlite3 *db;
	std::string userType;
};

#endif // PROFILEMANAGERUI_H_
