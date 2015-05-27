/*=============================================================
| Modified by: kb100
| Version: 1.03
| Modification: Restyled the code.
|==============================================================*/

#ifndef AIRCRAFT_H_
#define AIRCRAFT_H_

#include "sqlite3.h"

class Aircraft{
private:
	sqlite3 *db;

    int ID, inService, fClass, bClass, peClass, eClass, totalSeats;
    std::string name;

public:
    Aircraft(sqlite3 *); // Constructor.

    // Get functions.
	int getID() const;
	std::string getName() const;
	int getInService() const;
	int getFClass() const;
	int getBClass() const;
	int getPEClass() const;
	int getEClass() const;
	int getTotalSeats() const;
	std::string getByID(std::string);

	// Set functions.
	void setID(int);
	void setName(std::string);
	void setInService(int i);
	void setFClass(int);
	void setBClass(int);
	void setPEClass(int);
	void setEClass(int);
	void setTotalSeats();
	
	// Other functions.
	friend std::ostream &operator<<(std::ostream &os, const Aircraft &A);
	void createAircraft();
	void update();
	void deleteAircraft();
	int round(float num); //rounds up or down depending on decimal.
	int getSClassStartPoint(std::string sClass, int& rowStart);
};

#endif // AIRCRAFT_H_
