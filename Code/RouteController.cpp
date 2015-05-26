/*=============================================================
| Modified by: kb100
| Version: 1.01
| Modification: Restyled the code.
|==============================================================*/

#include <iostream>
#include <sstream>
#include "RouteController.h"
#include "Route.h"
#include "sqlite3.h"

using namespace std;

RouteController::RouteController(sqlite3 *d){
	db = d;
}
