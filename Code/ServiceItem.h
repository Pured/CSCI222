/*=============================================================
| Modified by: kb100
| Version: 1.01
| Modification: Restyled the code.
|==============================================================*/

#ifndef SERVICEITEM_H_
#define SERVICEITEM_H_

#include "sqlite3.h"

class ServiceItem{    
public:
	// Constructors.
	ServiceItem(sqlite3 *d);

	// Get functions.
	int getID() const;
	std::string getItem() const;
	float getCost() const;
	std::string getAvail() const;
	std::string getByID(int);

	// Set functions.
	void setID(int);
	void setItem(std::string);
	void setCost(float);
	void setAvail(std::string);
	int update();
	void displayAll(bool intl);  // intl is true if displaying international menu

	// Other functions.
	friend std::ostream &operator<<(std::ostream &output, const ServiceItem &S);

private:
	sqlite3 *db;
    int ID;
    std::string item;
    float cost;
    std::string avail;
};

#endif // SERVICEITEM_H_
