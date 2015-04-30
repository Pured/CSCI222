#include "LoginController.h"
#include "Staff.h"
#include "sqlite3.h"

//constructor
LoginController::LoginController(sqlite3* d){
	db = d;
}

//Validates a login of a staff member. Called from validateLogin()
std::string LoginController::validateStaffLogin(std::string uname, std::string pwd){
	Staff s(db);
	s.setByEmail(uname);
	
	if(s.getType() != "None" && pwd == s.getPassword()){
		return s.getType();
	}
	
	return "Invalid";
	
}

//validates a login of a customer. Called from validateLogin()
std::string LoginController::validateCustomerLogin(std::string uname, std::string pwd){
	std::cout<<"Customer login not implemented\n";
	return "";
}


//handles the differentiation between a staff member and a client, then calls the
//appropriate validate function( either validateStaff() or validateCustomer() ) .
std::string LoginController::validateLogin(std::string uname, std::string pwd){
	
	std::string staffCheck = "@FlightSys"; //a staff member is defined as having this substring in their username
	std::string ret = "Invalid";
	 
	//find whether it is a staff account that is trying to login
	if(uname.find(staffCheck) != std::string::npos){
		ret = validateStaffLogin(uname,pwd);
	}
	else{
		//try customer login
		ret = validateCustomerLogin(uname,pwd);
	}
	
	return ret;
};
