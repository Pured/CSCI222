#include "LoginController.h"
#include "Staff.h"
#include "Customer.h"
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
	else if (s.getType() == "None" && pwd != s.getPassword()){
		return "INCORRECT PASSWORD";
	}
	
	return "NOT FOUND";
	
}

//validates a login of a customer. Called from validateLogin()
std::string LoginController::validateCustomerLogin(std::string uname, std::string pwd){
	
	Customer c(db);
	std::string check  = c.setByEmail(uname);
	
	if(c.getPassword() == pwd && check == "CUSTOMER"){
		return check;
	}
	else if(check == "CUSTOMER" && c.getPassword() != pwd){
		return "INCORRECT PASSWORD";
	}
	
	return check; // will return CUSTOMER, NOT FOUND or NOT REGISTERED
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
		//Customer c(db);
		ret = validateCustomerLogin(uname,pwd);
	}
	
	//std::cout<<ret<<std::endl;
	return ret;
};
