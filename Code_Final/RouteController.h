/*=============================================================
| Modified by: kb100
| Version: 1.01
| Modification: Restyled the code.
|==============================================================*/

#ifndef ROUTECONTROLLER_H_
#define ROUTECONTROLLER_H_

#include <iostream>
#include "sqlite3.h"
#include "Route.h"

class RouteController{
public:
	RouteController(sqlite3 *d);

	Route *alphabeticList(int &resSize);

private:
	sqlite3* db;
};

#endif // ROUTECONTROLLER_H_
