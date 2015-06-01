/*=============================================================
| Modified by: kb100
| Version: 1.01
| Modification: Restyled the code.
|==============================================================*/

#ifndef STAFFUI_H_
#define STAFFUI_H_

#include "sqlite3.h"

using namespace std;

class StaffUI{
public:
	StaffUI(sqlite3 *d);

bool run();

private:
	sqlite3 *db;
	string userType;
	int userNum;
};

#endif // STAFFUI_H_
