/*=============================================================
| Modified by: kb100
| Version: 1.01
| Modification: Restyled the code.
|==============================================================*/

#ifndef SEARCHCONTROLLER_H_
#define SEARCHCONTROLLER_H_

#include <string>
#include "sqlite3.h"

class SearchController{
public:
	SearchController(sqlite3 *d);

	int search(std::string user_type, std::string username);
	void setType(std::string user_type);
	std::string getType();

private:
	sqlite3 *db;
	std::string userType;
};

#endif // SearchController_H_
