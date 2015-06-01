/*=============================================================
| Modified by: kb100
| Version: 1.01
| Modification: Restyled the code.
|==============================================================*/

#ifndef TRAVELAGENT_H_
#define TRAVELAGENT_H_

#include "sqlite3.h"

class TravelAgent{
public:
	// Constructors.
	TravelAgent(sqlite3 *d);

	// Get functions.
	int getID() const;
	std::string getName() const;
	std::string getPhone() const;
	std::string getEmail() const;
	std::string getByName(std::string);
	std::string getPassword() const;

	// Set functions.
	void setID(int);
	void setName(std::string);
	void setPhone(std::string);
    void setPassword(std::string);
	std::string setByEmail(std::string);
	int update();

	// Other functions.
	friend std::ostream &operator<<(std::ostream &output, const TravelAgent &T);

private:
	sqlite3 *db;
	int ID;
	std::string name;
	std::string phone;
	std::string email;
	std::string password;
};

#endif // TRAVELAGENT_H_
