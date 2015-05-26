/*=============================================================
| Modified by: kb100
| Version: 1.01
| Modification: Restyled the code.
|==============================================================*/

#include <iostream>
#include <sstream>
#include "ServiceItem.h"
#include "callback.h"

using namespace std;

// Constructors.
ServiceItem::ServiceItem(sqlite3 *d){
	db = d;
	ID = -1;
	item = "No Item";
	cost = 0;
	avail = "No Availability";
}

// Get functions.
int ServiceItem::getID() const{
	return ID;
}

string ServiceItem::getItem() const{
	return item;
}

float ServiceItem::getCost() const{
	return cost;
}

string ServiceItem::getAvail() const{
	return avail;
}

string ServiceItem::getByID(int id){
	stringstream convert;

	convert << id;
	string convid = convert.str();
	convert.str(string()); // Clear ss.

	string sqlCreate = "SELECT * FROM SERVICEITEM WHERE ID = '" + convid + "';";
	const char *sql = sqlCreate.c_str();

	sqlite3_stmt *stmt;
    int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	int SVCID = -1;
	float COST;
	const char *ITEM, *AVAIL;

	if(err != SQLITE_OK){
		cout << "SELECT failed: " << sqlite3_errmsg(db) << endl;
	}
	else{
		while(sqlite3_step(stmt) == SQLITE_ROW){
			SVCID = sqlite3_column_int(stmt, 0);
			ITEM = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)); //get col 0
			COST = sqlite3_column_double(stmt, 2); 
			AVAIL= reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3)); // get col 1

			cout << SVCID << " " << ITEM << " " << COST << " " << AVAIL << "\n";

			if(ITEM == NULL){
				item = "";
			}
			else{
				item = string(ITEM);
			}

			if(AVAIL == NULL){
				avail = "";
			}
			else{
				avail = string(AVAIL);
			}

			ID = SVCID;
			cost = COST;
		}
	}

	sqlite3_finalize(stmt);

	if(ID == -1){
		return "NOT FOUND";
	}

	return "FOUND";
}

// Set functions.
void ServiceItem::setID(int i){
	ID = i;
}
void ServiceItem::setItem(string i){
	item = i;
}
void ServiceItem::setCost(float i){
	cost = i;
}
void ServiceItem::setAvail(string i){
	avail = i;
}

int ServiceItem::update(){
	if(ID != -1){
		// Convert any numeric attributes to string.
		stringstream convert;

		convert << ID;
		string convID = convert.str();
		convert.str(string()); //Clear ss.

		convert << cost;
		string convCost = convert.str();
		convert.str(string()); //Clear ss.

		string createSql = "UPDATE SERVICEITEM SET ID = '" + convID + "' WHERE ID = " + convID + ";" + "UPDATE SERVICEITEM SET ITEM = '" + item + "' WHERE ID = " + convID + ";" + "UPDATE SERVICEITEM SET COST = '" + convCost + "' WHERE ID = " + convID + ";" + "UPDATE SERVICEITEM SET AVAILABILITY = '" + avail + "' WHERE ID = " + convID + ";";

		const char *sql = createSql.c_str();

		// Execute SQL statement.
		char *errMsg = 0;
		int err = sqlite3_exec(db, sql, callback, 0, &errMsg);

		if(err != SQLITE_OK){
			cout << "SQL error: " << errMsg << endl;

			return 1;
		}
	}
	else{
		cout << "ServiceItem not initialised in UPDATE." << endl;

		return 1;
	}

	return 0;
}

// Other functions.
ostream &operator<<(ostream &os, const ServiceItem &S){
	os << "Service Item ID: " << S.getID() << "\nItem: " << S.getItem() << "\nCost: " << S.getCost() << "\nAvailability: " << S.getAvail() << "\n";

	return os;
}
