/*=============================================================
| Modified by: kb100
| Version: 1.02
| Modification: Restyled the code.
|==============================================================*/

#ifndef ROUTE_H_
#define ROUTE_H_

#include "sqlite3.h"

class Route{
public:
	// Constructors.
	Route(sqlite3 *);
	Route();

	// Get functions.
	int getID() const;
	std::string getSrc() const;
	std::string getDest() const;
	char getCodeshare() const;
	int getStops() const;
	std::string getByID(int);
	int getByAirports(std::string,std::string);

	// Set Functions.
	void setID(int);
	void setSrc(std::string);
	void setDest(std::string);
	void setCodeshare(char);
	void setStops(int);

	// Other functions.
	friend std::ostream &operator<<(std::ostream &output, const Route &R);
	void createRoute();
	void updateRoute();
	void deleteRoute();
	bool isInternational(); // Returns true if route is international.
	
private:
	sqlite3 *db;
	int ID, stops;
	std::string srcAirport, destAirport;
	char codeshare;
};

#endif // ROUTE_H_
