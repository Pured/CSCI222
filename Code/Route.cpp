/*=============================================================
| Modified by: kb100
| Version: 1.01
| Modification: Restyled the code.
|==============================================================*/

#include <iostream>
#include <sstream>
#include "Route.h"
#include "callback.h"
#include "sqlite3.h"
#include "Airport.h"

using namespace std;

// Constructors.
Route::Route(sqlite3 *d){
	db = d;
	ID = -1;
	srcAirport = "No Source Airport";
	destAirport = "No Destination Airport";
	codeshare = "No Codeshare";
	stops = 999;
}

Route::Route(){
	db = NULL;
	ID = -1;
	srcAirport = "No Source Airport";
	destAirport = "No Destination Airport";
	codeshare = "No Codeshare";
	stops = 999;
}

// Get functions.
int Route::getID() const{
	return ID;
}

string Route::getSrc() const{
	return srcAirport;
}

string Route::getDest() const{
	return destAirport;
}

string Route::getCodeshare() const{
	return codeshare;
}

int Route::getStops() const{
	return stops;
}

string Route::getByID(int id){
	stringstream convert;

	convert << id;

	string convid = convert.str();
	convert.str(string()); // Clear ss.
	
	string sqlCreate = "SELECT  * FROM ROUTE WHERE ID = '" + convid + "';";
	const char *sql = sqlCreate.c_str();
	
	sqlite3_stmt *stmt;
	int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	
	int ROUTEID = -1 , STOPS = 0;
	const char *SRC, *DEST, *CODE;
	
	if(err != SQLITE_OK){
		cout << "SELECT failed: " << sqlite3_errmsg(db) << endl;
	}
	else{
		while(sqlite3_step(stmt) == SQLITE_ROW){
			ROUTEID = sqlite3_column_int(stmt, 0);

			SRC = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
			DEST = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
			CODE = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));

			STOPS = sqlite3_column_int(stmt, 4);

			if(SRC == NULL){
				srcAirport = "";
			}
			else{
				srcAirport = string(SRC);
			}

			if(DEST == NULL){
				destAirport = "";
			}
			else{
				destAirport = string(DEST);
			}

			if(CODE == NULL){
				codeshare = "";
			}
			else{
				codeshare = string(CODE);
			}

			ID = ROUTEID;
			stops = STOPS;
		}
	}

	sqlite3_finalize(stmt);
	
	if(ID == -1){
		return "NOT FOUND";
	}

	return "FOUND";
}

// Set Functions.
void Route::setID(int i){
	ID = i;
}

void Route::setSrc(string i){
	srcAirport = i;
}

void Route::setDest(string i){
	destAirport = i;
}

void Route::setCodeshare(string i){
	codeshare = i;
}

void Route::setStops(int i){
	stops = i;
}

int Route::update(){
	if(ID != -1){
		// Convert any numeric attributes to string.
		stringstream convert;

		convert << ID;

		string convID = convert.str();
		convert.str(string()); // Clear ss.
	
		convert << stops;

		string convStops = convert.str();
		convert.str(string()); // Clear ss.

		string createSql = "UPDATE ROUTE SET ID = '" + convID + "' WHERE ID = " + convID + ";" + "UPDATE ROUTE SET SRC = '" + srcAirport + "' WHERE ID = "+ convID + ";" + "UPDATE ROUTE SET DEST = '" + destAirport + "' WHERE ID = " + convID + ";" + "UPDATE ROUTE SET CODESHARE = '" + codeshare + "' WHERE ID = " + convID + ";" + "UPDATE ROUTE SET STOPS = '" + convStops + "' WHERE ID = " + convID + ";";

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
		cout << "ROUTE  not initialised in UPDATE.\n";

		return 1;
	}

	return 0;
}

int Route::getByAirports(string leaving, string arriving){
	string sqlCreate = "SELECT  * FROM ROUTE WHERE SRC='" + leaving + "' AND DEST='" + arriving + "';";

	const char *sql = sqlCreate.c_str();
	
	sqlite3_stmt *stmt;
    int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	
	int ROUTEID = -1 , STOPS = 0;
	const char* SRC, *DEST, *CODE;
	
	if(err != SQLITE_OK){
        cout << "SELECT failed: " << sqlite3_errmsg(db) << endl;
    }
    else{
		while(sqlite3_step(stmt) == SQLITE_ROW){
			ROUTEID = sqlite3_column_int(stmt, 0);

            SRC = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
			DEST = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
            CODE = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));

			STOPS = sqlite3_column_int(stmt, 4);

			if(SRC == NULL){
				srcAirport = "";
			}
			else{
				srcAirport = string(SRC);
			}

			if(DEST == NULL){
				destAirport = "";
			}
			else{
				destAirport = string(DEST);
			}

			if(CODE == NULL){
				codeshare = "";
			}
			else{
				codeshare = string(CODE);
			}

			ID = ROUTEID;
			stops = STOPS;
		}
	}

	sqlite3_finalize(stmt);

	return ID;
}

bool Route::isInternational(){

	Airport SRC(db);
	Airport DEST(db);

	SRC.getByIata(srcAirport);
	DEST.getByIata(destAirport);

	if (SRC.getID() != -1 && DEST.getID() != -1){
		if (SRC.getCountry() == "Australia"  && DEST.getCountry() == "Australia"){
			//cout << "not intl" << endl;
			return false; //route is not international
		}
	}

	return true;
}

ostream &operator<<(ostream &output, const Route &R){
	output << R.getID() << " " << R.getSrc() << " " << R.getDest() << " " << R.getCodeshare() <<"  " << R.getStops() << endl;

	return output;
}
