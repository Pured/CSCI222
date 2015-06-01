/*=============================================================
| Modified by: kb100
| Version: 1.02
| Modification: Restyled the code.
|==============================================================*/

#ifndef STAFF_H_
#define STAFF_H_

#include <string>
#include "sqlite3.h"

class Staff{
public:
	// Constructors.
	Staff(sqlite3 *d);
	Staff(sqlite3 *, std::string uType, std::string uName, std::string pw);

	// Get functions.
	std::string getUsername() const;
	std::string getPassword() const;
	std::string getType() const;

	// Set functions.
	void setUsername(std::string);
	void setPassword(std::string);
	void setType(std::string);
	std::string setByEmail(std::string e);

	// Other functions.
	friend std::ostream &operator<<(std::ostream &output, const Staff &S);

private:
	sqlite3 *db;
	std::string userType;
	std::string userName;
	std::string password;
};

#endif // STAFF_H_
