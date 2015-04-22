#include <string>
#include <stdio.h>
#include "sqlite3.h"
#include <iostream>

using namespace std;

//The callback method is used as a parameter to the sqlite3_exec() function.
//callback enables us to see the results and messages from sql.
//DO NOT USE THIS TO STORE QUERY RESULTS...SEE 'HOW TO QUERY TABLE AND STORE RETURNED DATA' SECTION.
//
//reference: http://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm
static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main(int argc, char* argv[])
{
                                /***** HOW TO OPEN OR CREATE A TABLE ***/
	sqlite3 *database;
	char *errMsg = 0;
	int err = sqlite3_open("Database.db", &database); //if database does not exits this will create one.

	if(err != SQLITE_OK){
		cout<<"Cannot access database"<<endl;
	}
	else{
		cout<<"Hooray im a database!!"<<endl;
	}



                                /***** HOW TO CREATE A TABLE ***/
    cout<<"creating table..."<<endl;
    //Create a statement
	char *sql = "CREATE TABLE AIRPORT( \
                id		NUMBER(4)	NOT NULL, \
                name 		VARCHAR(50)	NOT NULL, \
                city		VARCHAR(50)	NOT NULL, \
                country		VARCHAR(50)	NOT NULL, \
                iata		VARCHAR(3)	NOT NULL, \
                latitude	DECIMAL(10,6)	NOT NULL, \
                longitude	DECIMAL(10,6)	NOT NULL, \
                altitude	NUMBER(5)	NOT NULL, \
                timezone	NUMBER(2)	NOT NULL, \
                DST		CHAR(1)		NOT NULL, \
                tz		VARCHAR(50)	NOT NULL, \
                CONSTRAINT AIRPORT_pkey PRIMARY KEY (id), \
                CONSTRAINT airport_iata UNIQUE (iata), \
                CONSTRAINT alt_check CHECK (altitude >= 0) \
            );";

    //execute statement
    err = sqlite3_exec(database, sql, callback, 0, &errMsg);
    if( err != SQLITE_OK ){
        cout<<"SQL error: "<<errMsg<<endl<<endl;
   }else{
      cout<<"Created table"<<endl<<endl;
   }




                                            /***** HOW TO INSERT INTO A TABLE ***/
    cout<<"Inserting into table..."<<endl;
    //Create a statement
	sql = "INSERT INTO AIRPORT VALUES(5,'Port Moresby Jacksons Intl','Port Moresby','Papua New Guinea', \
                                         'POM',-9.443383,147.22005,146,10,'U',' Pacific/Port_Moresby');";

    //execute statement
    err = sqlite3_exec(database, sql, callback, 0, &errMsg);
    if( err != SQLITE_OK ){
        cout<<"SQL error: "<<errMsg<<endl<<endl;
   }else{
      cout<<"Row inserted successfully"<<endl<<endl;
   }

                                            /***** HOW TO QUERY TABLE AND STORE RETURNED DATA ***/
    //The reason we cant use callback to store data from querys is that we cannot pass
    //our own classes or structs into the callback method to store the results.
    //
    //we need to:
    //1)create a statement object ( sqlite3_stmt )
    //2) prepare statement with sqlite3_prepare_v2()
    //3) step through query results with sqlite3_step(stmt)
    //      3.1) store attribute values in struct/class
    //      3.2) store struct/class in list/vector for multi row results.
    //4)finalize statement.

    cout<<"Querying table..."<<endl;
    //Create a statement
	sql = "SELECT ID,NAME,CITY FROM AIRPORT;";

	sqlite3_stmt *stmt;
    err = sqlite3_prepare_v2(database, sql, -1, &stmt, NULL);

    //create variables to store data.
    int id;
    const char* name;
    const char* city;

    if (err != SQLITE_OK) {
        cout << "SELECT failed: " << sqlite3_errmsg(database) << endl;
    }
    else{
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            id = sqlite3_column_int(stmt, 0);
            name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            city = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

            //output data as its received
            cout<<"ID: "<<id<<"\nName: "<<name<<"\nCity: "<<city<<"\n\n"<<endl;

            //if you want to put data in a list/vector
            //vector.push_back(Airport(id, name, city ,...));
        }
    }

    sqlite3_finalize(stmt);




                                    /***** HOW TO UPDATE TABLE ***/
    cout<<"Updating table and querying the results..."<<endl;

    /* Create merged SQL statement */
   sql = "UPDATE AIRPORT SET NAME = 'Sydney' WHERE ID=5; " \
         "SELECT ID,NAME,CITY FROM AIRPORT";

   /* Execute SQL statement */
   err = sqlite3_exec(database, sql, callback, 0, &errMsg);
    if( err != SQLITE_OK ){
        cout<<"SQL error: "<<errMsg<<endl;
   }else{
      cout<<"Row Updated successfully"<<endl;
   }

	sqlite3_close(database);
}
