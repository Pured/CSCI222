/*=============================================================
| Modified by: kb100
| Version: 1.01
| Modification: Restyled the code.
|==============================================================*/

#ifndef CUSTOMERPROFILECONTROLLER_H_
#define CUSTOMERPROFILECONTROLLER_H_

#include <string>
#include "sqlite3.h"

class CustomerProfileController{
private:
	sqlite3 *db;

public:
	CustomerProfileController(sqlite3 *d); // Constructor.

	// Functions.
	std::string registerExistingCustomer(std::string, std::string);
	void findCustomer();
	void createCustomer();
	void editCustomer(std::string, std::string);
	void deleteCustomer();
};

#endif // CUSTOMERPROFILECONTROLLER_H_
