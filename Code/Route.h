/*=============================================================
| Modified by: kb100
| Version: 1.01
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
	std::string getCodeshare() const;
	int getStops() const;
	std::string getByID(int);
	int getByAirports(std::string,std::string);

	// Set Functions.
	void setID(int);
	void setSrc(std::string);
	void setDest(std::string);
	void setCodeshare(std::string);
	void setStops(int);
	int update();

	// Other functions.
	friend std::ostream &operator<<(std::ostream &output, const Route &R);
	bool isInternational(); //returns true if route is international.
	
private:
	sqlite3 *db;
	int ID;
	std::string srcAirport;
	std::string destAirport;
	std::string codeshare;
	int stops;
};

#endif // ROUTE_H_
