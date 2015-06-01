/*=============================================================
| Modified by: kb100
| Version: 1.02
| Modification: Restyled the code.
|==============================================================*/

#include <iostream>
#include "LoginController.h"
#include "Staff.h"
#include "Customer.h"
#include "TravelAgent.h"
#include "sqlite3.h"

using namespace std;

// Constructor.
LoginController::LoginController(sqlite3 *d){
	db = d;
}

// Validates a login of a staff member. Called from validateLogin().
string LoginController::validateStaffLogin(string uname, string pwd){
	Staff s(db);
	s.setByEmail(uname);

	if(s.getType() != "None" && pwd == s.getPassword()){
		return s.getType();
	}
	else if(s.getType() == "None" && pwd != s.getPassword()){
		return "INCORRECT PASSWORD";
	}

	return "NOT FOUND";
}

// Validates a login of a customer. Called from validateLogin().
string LoginController::validateCustomerLogin(string uname, string pwd){
	Customer c(db);
	string check = c.getByEmail(uname);

	if(c.getPassword() == pwd && check == "CUSTOMER"){
		return check;
	}
	else if(check == "CUSTOMER" && c.getPassword() != pwd){
		return "INCORRECT PASSWORD";
	}

	return check; // Will return CUSTOMER, NOT FOUND or NOT REGISTERED.
}

// Handles the differentiation between a staff member and a client, then calls the appropriate validate function(either validateStaff() or validateCustomer()).
string LoginController::validateLogin(string uname, string pwd){

	string staffCheck = "@FlightSys"; // A staff member is defined as having this substring in their username.
	string ret = "Invalid";

	// Find whether it is a staff account that is trying to login.
	if(uname.find(staffCheck) != string::npos){
		ret = validateStaffLogin(uname, pwd);
	}
	else{
		ret = validateCustomerLogin(uname, pwd); // Try customer login.

		if(ret == "CUSTOMER" || ret == "NOT REGISTERED"){
			return ret;
		}
		else{
			ret = validateTravelAgentLogin(uname, pwd); // Try travel agent login.

			return ret;
		}
	}

	//cout << ret << endl;
	return ret;
}

// Validates a login of a travel agent. Called from validateLogin().
string LoginController::validateTravelAgentLogin(string uname, string pwd){
	TravelAgent t(db);
	string check = t.setByEmail(uname);

	if(t.getPassword() == pwd && check == "TRAVELAGENT"){
		return check;
	}
	else if(check == "TRAVELAGENT" && t.getPassword() != pwd){
		return "INCORRECT PASSWORD";
	}

	return "NOT FOUND";
}
