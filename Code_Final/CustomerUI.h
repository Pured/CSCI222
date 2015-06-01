/*=============================================================
| Modified by: kb100
| Version: 1.02
| Modification: Restyled the code.
|==============================================================*/

#ifndef CUSTOMERUI_H_
#define CUSTOMERUI_H_

#include <string>
#include "sqlite3.h"

class CustomerUI{
public:
	CustomerUI(sqlite3 *); // Constructor.

	bool run();
	void setUsername(std::string);
	void manageFlights();
	void manageServices();
	void manageDetails();
		
private:
	sqlite3 *db;

	std::string userType, username;
};

#endif // CUSTOMERUI_H_
