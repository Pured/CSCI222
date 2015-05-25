#ifndef SEARCHCONTROLLER_H
#define SEARCHCONTROLLER_H

#include "SearchController.h"
#include <string>
#include "sqlite3.h"


class SearchController
{
public:
	SearchController(sqlite3* d);
	int search(std::string user_type,std::string username);
	void setType(std::string user_type);
	std::string getType();
	



protected:
private:
	sqlite3* db;
	std::string userType;

};

#endif // SearchController_H
