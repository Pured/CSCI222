#include "Staff.h"
#include "sqlite3.h"

Staff::Staff(sqlite3* d){
	db = d;
    userType = "None";
    userName = "No Username";
    password = "No Password";
}

Staff::Staff(sqlite3* d,std::string uType,std::string uName, std::string pw){
	db=d;
    userType = uType;
    userName = uName;
    password = pw;
    
}




//set functions
void Staff::setUsername(std::string i){
    userName = i;
}

void Staff::setPassword(std::string i){
    password = i;
}

void Staff::setType(std::string i){
    userType = i;
}

//sets all staff member attributes by finding their email address from the database.
std::string Staff::setByEmail(std::string e){
	
	std::string sqlCreate = "SELECT  USERTYPE,EMAIL,PASSWORD FROM STAFF WHERE EMAIL = '" + e +"';";
	const char* sql = sqlCreate.c_str();
	
	//std::cout<<sql<<std::endl;

	sqlite3_stmt *stmt;
    int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    //create variables to store data.
    const char* UT; //temp storage for userType
    const char* UN; //temp storage for userNAme;
    const char* PWD; //temp storage for password

    if (err != SQLITE_OK) {
        std::cout << "SELECT failed: " << sqlite3_errmsg(db) << std::endl;
    }
    else{
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			//get data from db
            UT = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)); //get col 0
            UN= reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)); // get col 1
            PWD = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)); // get col 2
			
			//std::cout<<UT<<" "<<UN<<" "<<PWD;
			
			//cast to string
			if(UT == NULL || UN == NULL || PWD == NULL){ //make sure UT/UN/PWD is not null, otherwise the return behaviour is undefined.
				userType = "";
				userName = "";
				password = "";
			}
			else{
				userType = std::string(UT);
				userName = std::string(UN);
				password = std::string(PWD);
			}
			
        }
    }

    sqlite3_finalize(stmt);
	
	return userType;
};





//get functions
std::string Staff::getPassword() const{
    return password;
}

std::string Staff::getType() const{
    return userType;
}

std::string Staff::getUsername() const{
    return userName;
}





//other functions
std::ostream &operator<<( std::ostream &output,const Staff &S){
    output<<S.getUsername()<<" "<<S.getPassword();
    return output;
}