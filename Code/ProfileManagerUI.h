/*=============================================================
| Modified by: kb100
| Version: 1.02
| Modification: Restyled the code.
|==============================================================*/

#ifndef PROFILEMANAGERUI_H_
#define PROFILEMANAGERUI_H_

#include "sqlite3.h"

class ProfileManagerUI{
public:
	ProfileManagerUI(sqlite3 *);

	bool run();
private:
	sqlite3 *db;
	std::string userType;
};

#endif // PROFILEMANAGERUI_H_
