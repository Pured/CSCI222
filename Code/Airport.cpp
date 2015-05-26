/*=============================================================
| Modified by: kb100
| Version: 1.01
| Modification: Restyled the code.
|==============================================================*/

#include <iostream>
#include <cstring>
#include <sstream>
#include "Airport.h"
#include "callback.h"

using namespace std;

Airport::Airport(sqlite3* d){
	db = d;
	ID = -1;
	name = "No name";
	city = "No City";
	country = "No Country";
	iata = "No IATA";
	latitude = 0;
	longitude = 0;
	altitude = 0;
	timezone = -1;
	dst = "No DST";
	tz = "No TZ";
};

Airport::Airport(){
	db = NULL;
	ID = 0;
	name = "No name";
	city = "No City";
	 country = "No Country";
	iata = "No IATA";
	latitude = 0;
	longitude = 0;
	altitude = 0;
	timezone = -1;
	dst = "No DST";
	tz = "No TZ";
}

// Get functions.
int Airport::getID() const{
	return ID;
}

string Airport::getName() const{
	return name;
}

string Airport::getCity() const{
	return city;
}

string Airport::getCountry() const{
	return country;
}

string Airport::getIATA() const{
	return iata;
}

float Airport::getLat() const{
	return latitude;
}

float Airport::getLong() const{
	return longitude;
}

int Airport::getAlt() const{
	return altitude;
}

int Airport::getTimezone() const{
	return timezone;
}

string Airport::getDST() const{
	return dst;
}

string Airport::getTZ() const{
	return tz;
}

string Airport::getByIata(string e){
	string sqlCreate = "SELECT  * FROM AIRPORT WHERE IATA = '" + e +"';";
	const char *sql = sqlCreate.c_str();

	sqlite3_stmt *stmt;
	int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	int AIRID = 0, ALT = 0, TIMEZONE = 0;
	float LAT = 0, LONG = 0;
	const char *NAME, *CITY, *COUNTRY, *IATA, *DST, *TZ;

	if(err != SQLITE_OK){
		cout << "SELECT failed: " << sqlite3_errmsg(db) << endl;
	}
	else{
		while (sqlite3_step(stmt) == SQLITE_ROW ) {
			AIRID = sqlite3_column_int(stmt, 0);

			NAME = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
			CITY = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
			COUNTRY = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
			IATA = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));

			LAT = sqlite3_column_double(stmt, 5);
			LONG = sqlite3_column_double(stmt, 6);
			ALT = sqlite3_column_int(stmt, 7);
			TIMEZONE = sqlite3_column_int(stmt, 8);

			DST = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 9));
			TZ = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 10));

			if(IATA == NULL){
				iata = "";
			}
			else{
				iata = string(IATA);
			}

			ID = AIRID;

			if(NAME == NULL){
				name = "";
			}
			else{
				name = string(NAME); 
			}

			if(CITY == NULL){
				city = "";
			}
			else{
				city = string(CITY); 
			}

			if(COUNTRY == NULL){
				country = "";
			}
			else{
				country = string(COUNTRY); 
			}

			latitude = LAT;
			longitude = LONG;
			altitude = ALT;
			timezone = TIMEZONE;

			if(DST == NULL){
				dst = "";
			}
			else{
				dst = string(DST);  
			}

			if(TZ == NULL){
				tz = "";
			}
			else{
				tz = string(TZ); 
			}
		}
	}

	sqlite3_finalize(stmt);

	if(iata == ""){
		return "NOT FOUND";
	}

	return "FOUND";
}

string Airport::getByName(string e){
	string sqlCreate = "SELECT * FROM AIRPORT WHERE NAME = '" + e +"';";
	//cout<<sqlCreate<<endl;
	const char* sql = sqlCreate.c_str();
	
	sqlite3_stmt *stmt;
    int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	
	int AIRID = -1;
	const char* NAME;
    const char* CITY; 
	const char* COUNTRY;
	const char* IATA;
	float LAT;
	float LONG;
	int ALT;
	int TIMEZONE;
	const char* DST;
	const char* TZ;
	
	if(err != SQLITE_OK){
        cout << "SELECT failed: " << sqlite3_errmsg(db) << endl;
    }
    else{
		while(sqlite3_step(stmt) == SQLITE_ROW ) {
			AIRID = sqlite3_column_int(stmt, 0);
            NAME = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1)); //get col 0
			CITY= reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2)); // get col 1
            COUNTRY= reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3)); // get col 1
            IATA= reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4)); // get col 2
            LAT = sqlite3_column_double(stmt, 5); 
            LONG= sqlite3_column_double(stmt, 6); 
            ALT= sqlite3_column_int(stmt, 7); 		
            TIMEZONE= sqlite3_column_int(stmt, 8);
            DST= reinterpret_cast<const char *>(sqlite3_column_text(stmt, 9)); // get col 1
			TZ = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 10)); // get col 1
			
		
			
			//cout<<AIRID<<" "<<NAME<<" "<<CITY<<" "<<COUNTRY<<" "<<IATA<<" "<<LAT<<" "
						//<<LONG<<" "<<ALT<<" "<<TIMEZONE<<" "<<DST<<" "<<TZ<<"\n";
						
		
		
			if(IATA == NULL){
				iata = "";
			}
			else{
				iata = string(IATA);
			}
			
			ID = AIRID;
		
			if(NAME == NULL){
				name = "";
			}
			else{
				name = string(NAME); 
			}
		
			if(CITY == NULL){
				city = "";
			}
			else{
				city = string(CITY); 
			}
		
			if(COUNTRY == NULL){
				country = "";
			}
			else{
				country = string(COUNTRY); 
			}
			
			latitude = LAT;
			longitude = LONG;
			altitude = ALT;
			timezone = TIMEZONE;
			
		
			if(DST == NULL){
				dst = "";
			}
			else{
				//strcpy(dst,DST[0]);
				dst = string(DST);  
			}
		
			if(TZ == NULL){
				tz = "";
			}
			else{
				tz = string(TZ); 
			}
		
		}
		
	}
	
	sqlite3_finalize(stmt);
	
	if(AIRID == -1){
		return "NOT FOUND";
	}
	
	return "FOUND";
}

// Set functions.
void Airport::setDB(sqlite3 *d){
	db = d;
}

void Airport::setID(int i){
	ID = i;
}
void Airport::setName(string i){
	name = i;
}

void Airport::setCity(string i){
	city = i;
}

void Airport::setIATA(string i){
	iata = i;
}

void Airport::setLat(float i){
	latitude = i;
}

void Airport::setLong(float i){
	longitude = i;
}

void Airport::setAlt(int i){
	altitude = i;
}

void Airport::setTimezone(int i){
	timezone = i;
}

void Airport::setDST(string i){
	dst = i;
}

void Airport::setTZ(string i){
	tz = i;
}

int Airport::update(){
	// Convert any numeric attributes to string.
	stringstream convert;

	convert << ID;
	string convID = convert.str();
	convert.str(string()); // Clear ss.

	convert << latitude;
	string convLat = convert.str();
	convert.str(string()); // Clear ss.

	convert << longitude;
	string convLong = convert.str();
	convert.str(string()); // Clear ss.

	convert << altitude;
	string convAlt = convert.str();
	convert.str(string()); // Clear ss.

	convert << timezone;
	string convTimezone = convert.str();
	convert.str(string()); // Clear ss.

	string createSql = "UPDATE AIRPORT SET ID = '" + convID + "' WHERE ID = " + convID + ";" + "UPDATE AIRPORT SET NAME = '" + name + "' WHERE ID = " + convID + ";" + "UPDATE AIRPORT SET CITY = '" + city + "' WHERE ID = " + convID + ";" +	"UPDATE AIRPORT SET COUNTRY = '" + country + "' WHERE ID = "+ convID + ";" + 	"UPDATE AIRPORT SET IATA = '" + iata + "' WHERE ID = " + convID + ";" + "UPDATE AIRPORT SET LATITUDE = '" + convLat + "' WHERE ID = " + convID + ";" + "UPDATE AIRPORT SET LONGITUDE = '" + convLong + "' WHERE ID = " + convID + ";" + "UPDATE AIRPORT SET ALTITUDE = '" + convAlt + "' WHERE ID = " + convID + "; " + "UPDATE AIRPORT SET TIMEZONE = '" + convTimezone + "' WHERE ID = " + convID + ";" + "UPDATE AIRPORT SET DST = '" + dst + "' WHERE ID = " + convID + ";" + "UPDATE AIRPORT SET TZ = '" + tz + "' WHERE ID = " + convID + ";";

	const char *sql = createSql.c_str();

	// Execute SQL statement.
	char *errMsg = 0;
	int err = sqlite3_exec(db, sql, callback, 0, &errMsg);

	if(err != SQLITE_OK){
		cout << "SQL error: " << errMsg << endl;

		return 1;
	}

	return 0;
}



ostream &operator<<(ostream &os, const Airport &A){
	os << A.getID() << ": " << A.getCity() << " " << A.getCountry() << " " << A.getIATA() << " " << A.getLat() << " " << A.getLong() << " " << A.getAlt() << " " << A.getTimezone() << " " << A.getDST() << " " << A.getTZ() << endl;

	return os;
};

Airport *Airport::alphabeticList(){
	string sqlCreate =  "SELECT NAME,IATA FROM AIRPORT ORDER BY NAME ASC;";
	const char *sql = sqlCreate.c_str();

	sqlite3_stmt *stmt;
	int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	// Temporary variables for database retreival.
	const char * NAME, *IATA;
	char filter = '-';

	if(err != SQLITE_OK){
		cout << "SELECT failed: " << sqlite3_errmsg(db) << endl;
	}
	else{
		while (sqlite3_step(stmt) == SQLITE_ROW ) {
			// Get attributes from database.
			NAME = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
			IATA = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));

			if(filter != NAME[0] && NAME != NULL){
				filter = NAME[0];
				cout << "\t" << filter << endl << endl;
			}

			cout << "\t\t" << NAME << endl;
		}
	}

	return NULL;
}
