#include "CustomerProfileController.h"
#include "Customer.h"
#include "sqlite3.h"

//constructor
CustomerProfileController::CustomerProfileController(sqlite3* d){
	db = d;
}

//Validates a login of a staff member. Called from validateLogin()
std::string CustomerProfileController::registerExistingCustomer(std::string uname, std::string pwd){
	Customer c(db);
	c.setByEmail(uname);
	
	//std::cout<<c<<std::endl;
	
	c.setPassword(pwd);
	int ret = c.update();
	
	if(ret == 1){
		return "INVALID";
	}

	return "SUCCESSFUL REGISTRATION";
}




