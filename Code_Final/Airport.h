/*=============================================================
| Modified by: kb100
| Version: 1.03
| Modification: Added createAirport(), updateAirport(), deleteAirport() and setCountry().
|==============================================================*/

#ifndef AIRPORT_H_
#define AIRPORT_H_

#include "sqlite3.h"

class Airport{
public:
	// Constructors.
	Airport(sqlite3 *);
	Airport();

	// Get functions.
	int getID() const;
	std::string getName() const;
	std::string getCity() const;
	std::string getCountry() const;
	std::string getIATA() const;
	float getLat() const;
	float getLong() const;
	int getAlt() const;
	int getTimezone() const;
	char getDST() const;
	std::string getTZ() const;
	std::string getByIata(std::string i);
	std::string getByName(std::string);

	// Set functions.
	void setDB(sqlite3 *);
	void setID(int);
	void setName(std::string);
	void setCity(std::string);
	void setCountry(std::string);
	void setIATA(std::string);
	void setLat(float);
	void setLong(float);
	void setAlt(int);
	void setTimezone(int);
	void setDST(char);
	void setTZ(std::string);

	// Other functions.
	friend std::ostream &operator<<(std::ostream &os, const Airport &A);
	void createAirport();
	void updateAirport();
	void deleteAirport();
	Airport *alphabeticList();

private:
	sqlite3 *db;

	int ID, altitude, timezone;
	float latitude, longitude;
	std::string name, city, country, iata, tz;
	char dst;
};

#endif //AIRPORT_H_
