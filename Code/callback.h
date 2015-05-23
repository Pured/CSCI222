// The callback method is used as a parameter to the sqlite3_exec() function.
// callback enables us to see the results and messages from sql.
// DO NOT USE THIS TO STORE QUERY RESULTS...SEE 'HOW TO QUERY TABLE AND STORE RETURNED DATA' SECTION.

//reference: http://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
	int i;
	for(i=0; i<argc; i++){
	//printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	//printf("\n");

	return 0;
}
