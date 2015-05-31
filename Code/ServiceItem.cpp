/*=============================================================
| Modified by: kb100
| Version: 1.03
| Modification: Implemented the create/update/delete functions.
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

string ServiceItem::getByID(string e){
	string sqlCreate = "SELECT * FROM SERVICEITEM WHERE ID = '" + e + "';";
	const char *sql = sqlCreate.c_str();

	sqlite3_stmt *stmt;
    int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	const char *ITEM, *AVAIL;
	int SVCID = -1;
	float COST = 0;

	if(err != SQLITE_OK){
		cout << "SELECT failed: " << sqlite3_errmsg(db) << endl;
	}
	else{
		while(sqlite3_step(stmt) == SQLITE_ROW){
			SVCID = sqlite3_column_int(stmt, 0);

			ITEM = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));

			COST = sqlite3_column_double(stmt, 2); 

			AVAIL = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));

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

// Other functions.
ostream &operator<<(ostream &os, const ServiceItem &S){
	os << "Service Item ID: " << S.getID() << "\nItem: " << S.getItem() << "\nCost: " << S.getCost() << "\nAvailability: " << S.getAvail() << "\n";

	return os;
}

void ServiceItem::createServiceItem(){
	// Add object details to DB.
	stringstream convert;

	convert << cost;
	string convCOST = convert.str();
	convert.str(string()); // Clear ss.

	string createSql = "INSERT INTO SERVICEITEM VALUES(NULL,'" + item + "'," + convCOST + ",'" + avail + "');";

	const char* sql = createSql.c_str();

	// Execute SQL statement.
	char *errMsg = 0;
	int err = sqlite3_exec(db, sql, callback, 0, &errMsg);

	if(err != SQLITE_OK){
		cout << "SQL error: " << errMsg << endl;
	}
}

void ServiceItem::updateServiceItem(){
		// Convert any numeric attributes to string.
		stringstream convert;

		convert << ID;
		string convID = convert.str();
		convert.str(string()); //Clear ss.

		convert << cost;
		string convCost = convert.str();
		convert.str(string()); //Clear ss.

		string createSql = "UPDATE SERVICEITEM SET ITEM = '" + item + "' WHERE ID = " + convID + ";" + "UPDATE SERVICEITEM SET COST = '" + convCost + "' WHERE ID = " + convID + ";" + "UPDATE SERVICEITEM SET AVAILABILITY = '" + avail + "' WHERE ID = " + convID + ";";

		const char *sql = createSql.c_str();

		// Execute SQL statement.
		char *errMsg = 0;
		int err = sqlite3_exec(db, sql, callback, 0, &errMsg);

		if(err != SQLITE_OK){
			cout << "SQL error: " << errMsg << endl;
		}
}

void ServiceItem::deleteServiceItem(){
	stringstream convert;

	convert << ID;
	string convID = convert.str();

	string sqlCreate = "DELETE FROM SERVICEITEM WHERE ID = '" + convID + "';";
	const char *sql = sqlCreate.c_str();

	// Execute SQL statement.
	char *errMsg = 0;
	int err = sqlite3_exec(db, sql, callback, 0, &errMsg);

	if(err != SQLITE_OK){
		cout << "SQL error: " << errMsg << endl;
	}
}

void ServiceItem::displayAll(bool intl){
	string sqlCreate = "";

	if(intl == false){
		//do not display international items
		sqlCreate = "SELECT ID,ITEM,COST FROM SERVICEITEM WHERE AVAILABILITY = 'all';";
	}
	else{
		//display all items
		sqlCreate = "SELECT ID,ITEM,COST FROM SERVICEITEM;";
	}

	const char* sql = sqlCreate.c_str();

	sqlite3_stmt *stmt;
	int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	int SVCID = -1;
	const char* ITEM;
	float COST;

	if(err != SQLITE_OK){
		cout << "SELECT failed: " << sqlite3_errmsg(db) << endl;
	}
	else{
		while(sqlite3_step(stmt) == SQLITE_ROW){
			SVCID = sqlite3_column_int(stmt, 0);
			ITEM = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)); //get col 0
			COST = sqlite3_column_double(stmt, 2);

			cout <<SVCID << ") " << ITEM << " Cost: $" << COST << "\n";

			if(ITEM == NULL){
				item = "";
			}
			else{
				item = string(ITEM);
			}

			ID = SVCID;
			cost = COST;
		}
	}

	sqlite3_finalize(stmt);
}
