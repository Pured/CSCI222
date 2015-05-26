/*=============================================================
| Modified by: kb100
| Version: 1.02
| Modification: Restyled the code.
|==============================================================*/

#ifndef SERVICEMANAGERUI_H_
#define SERVICEMANAGERUI_H_

#include "sqlite3.h"

class ServiceManagerUI{
public:
	ServiceManagerUI(sqlite3 *);

	bool run();
	void serviceItemUI();

private:
	sqlite3 *db;
	string userType;
};

#endif // SERVICEMANAGERUI_H_
