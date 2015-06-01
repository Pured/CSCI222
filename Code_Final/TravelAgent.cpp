/*=============================================================
| Modified by: kb100
| Version: 1.01
| Modification: Restyled the code.
|==============================================================*/

#include <iostream>
#include <sstream>
#include "TravelAgent.h"
#include "callback.h"

using namespace std;

// Constructors.
TravelAgent::TravelAgent(sqlite3 *d){
	db = d;
    ID = -1;
    name = "No Name";
    phone = "No Phone";
    email = "No Email";
}

// Get functions.
int TravelAgent::getID() const{
	return ID;
}

string TravelAgent::getName() const{
	return name;
}

string TravelAgent::getPhone() const{
	return phone;
}

string TravelAgent::getEmail() const{
	return email;
}

string TravelAgent::getPassword() const{
	return password;
}

string TravelAgent::getByName(string n){
	stringstream convert;

	convert << ID;
	string convid = convert.str();
	convert.str(string()); // Clear ss.

	string sqlCreate = "SELECT * FROM TRAVELAGENT WHERE NAME = '" + n + "';";
	const char *sql = sqlCreate.c_str();

	sqlite3_stmt *stmt;
	int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	int AGTID = -1;
	const char* NAME, *PHONE, *EMAIL, *PASSWORD;

	if(err != SQLITE_OK){
		cout << "SELECT failed: " << sqlite3_errmsg(db) << endl;
	}
	else{
		while(sqlite3_step(stmt) == SQLITE_ROW){
			AGTID = sqlite3_column_int(stmt, 0);

			NAME = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
			PHONE = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
			EMAIL = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
			PASSWORD = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));

			cout << AGTID << " " << NAME << " " << PHONE << " " << EMAIL << PASSWORD << endl;

			if(NAME == NULL){
				name = "";
			}
			else{
				name = string(NAME);
			}

			if(PHONE == NULL){
				phone = "";
			}
			else{
				phone = string(PHONE);
			}

			if(EMAIL == NULL){
				email = "";
			}
			else{
				email = string(EMAIL);
			}

			if(PASSWORD == NULL){
				password = "";
			}
			else{
			 password = string(PASSWORD);
			}

			ID = AGTID;
		}
	}

	sqlite3_finalize(stmt);

	if(ID == -1){
		return "NOT FOUND";
	}

	return "FOUND";
}

// Set functions.
void TravelAgent::setID(int i){
	ID = i;
}

void TravelAgent::setName(string i){
	name = i;
}

void TravelAgent::setPhone(string i){
	phone = i;
}

void TravelAgent::setPassword(string p){
    password = p;
}

string TravelAgent::setByEmail(string i){
stringstream convert;

	string sqlCreate = "SELECT * FROM TRAVELAGENT WHERE EMAIL = '" + i + "';";
	const char *sql = sqlCreate.c_str();

	sqlite3_stmt *stmt;
	int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	int AGTID = -1;
	const char* NAME, *PHONE, *EMAIL, *PASSWORD;

	if(err != SQLITE_OK){
		cout << "SELECT failed: " << sqlite3_errmsg(db) << endl;
	}
	else{
		while(sqlite3_step(stmt) == SQLITE_ROW){
			AGTID = sqlite3_column_int(stmt, 0);

			NAME = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
			PHONE = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
			EMAIL = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
			PASSWORD = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));

			if(NAME == NULL){
				name = "";
			}
			else{
				name = string(NAME);
			}

			if(PHONE == NULL){
				phone = "";
			}
			else{
				phone = string(PHONE);
			}

			if(EMAIL == NULL){
				email = "";
			}
			else{
				email = string(EMAIL);
			}

			if(PASSWORD == NULL){
				password = "";
			}
			else{
				password = string(PASSWORD);
			}

			ID = AGTID;
		}
	}

	sqlite3_finalize(stmt);

	if(ID == -1){
		return "NOT FOUND";
	}

	return "TRAVELAGENT";
}

int TravelAgent::update(){
	if(ID != -1){
		// Convert any numeric attributes to string.
		stringstream convert;

		convert << ID;
		string convID = convert.str();
		convert.str(string()); // Clear ss.

		string createSql = "UPDATE TRAVELAGENT SET ID = '" + convID + "' WHERE NAME = '" + name + "';" + "UPDATE TRAVELAGENT SET NAME = '" + name + "' WHERE NAME = '" + name + "';" + "UPDATE TRAVELAGENT SET PHONE = '" + phone + "' WHERE NAME = '" + name + "';" + "UPDATE TRAVELAGENT SET EMAIL = '" + email + "' WHERE NAME = '" + name + "';" + "UPDATE TRAVELAGENT SET PASSWORD = '" + password + "'WHERE NAME = '" + name + "';";

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
		cout << "TravelAgent not initialised in UPDATE." << endl;

		return 1;
	}

   return 0;
}

// Other functions.
ostream &operator<<(ostream &os, const TravelAgent &T){
	os << "Travel Agent ID: " << T.getID() << "\nName: " << T.getName() << "\nPhone: " << T.getPhone() << "\nEmail: " << T.getEmail() << "\nPassword: " << T.getPassword() << endl;

	return os;
}
