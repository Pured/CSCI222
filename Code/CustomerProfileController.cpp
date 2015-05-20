#include "CustomerProfileController.h"
#include "Customer.h"
#include "sqlite3.h"
#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib> // atoi
using namespace std;

//constructor
CustomerProfileController::CustomerProfileController(sqlite3* d){
	db = d;
}

//Validates a login of a staff member. Called from validateLogin()
std::string CustomerProfileController::registerExistingCustomer(std::string uname, std::string pwd){
	Customer c(db);
	c.getByEmail(uname);
	
	//std::cout<<c<<std::endl;
	
	c.setPassword(pwd);
	int ret = c.update();
	
	if(ret == 1){
		return "INVALID";
	}

	return "SUCCESSFUL REGISTRATION";
}

void CustomerProfileController::findCustomer(){
	std::string e;

    cout<<"Input the customer's email: ";
	cin>>e;

	cout << endl;
	
	Customer cust(db);
	cust.getByEmail(e);
	cout<<cust<<endl;
	
}

void  CustomerProfileController::createCustomer(){
	
	
	//create variables to store data.
	int lastID, ID;
	long long int CARDNUM, FREQFLIERPTS;
	string TITLE, FNAME, LNAME, GENDER, DOB, PHONE, EMAIL, ADDRESS, STATE, COUNTRY, CITY, CARDTYPE, PASSPORT, NOFLY, AGENT, PASSWORD,CARDNUMTEMP,FREQFLIERPTSTEMP;

		

	cout << "Creating a new Customer..." << endl;
	Customer cust(db); //customer ID automoatically assigned in Customer.createCust()
	
	//cout << "Customer ID: " << ID << endl;
	
	std::stringstream convert;

	
	cout << "Title: ";
	cin.ignore();
	getline(cin, TITLE);
	cust.setTitle(TITLE);

	cout << "Given Name: ";
	getline(cin, FNAME);
	cust.setFName(FNAME);
	
	cout << "Surname: ";
	getline(cin, LNAME);
	cust.setLName(LNAME);

	cout << "Sex: ";
	getline(cin, GENDER);
	cust.setGender(GENDER);

	cout << "D.O.B.: ";
	getline(cin, DOB);
	cust.setDOB(DOB); // must check format is YYYY-MM-DD

	cout << "Phone: ";
	getline(cin, PHONE);
	cust.setPhone(PHONE);

	cout << "Email: ";
	getline(cin, EMAIL);
	cust.setEmail(EMAIL);

	cout << "Address: ";
	getline(cin, ADDRESS);
	cust.setAddress(ADDRESS);

	cout << "City: ";
	getline(cin, CITY);
	cust.setCity(CITY);

	cout << "State: ";
	getline(cin, STATE);
	cust.setState(STATE);

	cout << "Country: ";
	getline(cin, COUNTRY);
	cust.setCountry(COUNTRY);

	cout << "Card Type: ";
	getline(cin, CARDTYPE);
	cust.setCardType(CARDTYPE);

	cout << "Card Number: ";
	cin >> CARDNUMTEMP;
	CARDNUM = atoi(CARDNUMTEMP.c_str());
	cust.setCardNum(CARDNUM);

	cout << "Frequent Flier Points: ";
	cin >> FREQFLIERPTSTEMP;
	FREQFLIERPTS = atoi(FREQFLIERPTSTEMP.c_str());
	cust.setFreqPts(FREQFLIERPTS);

	cin.ignore();

	cout << "Passport: ";
	getline(cin, PASSPORT);
	cust.setPassport(PASSPORT);

	cout << "No-Fly Status: ";
	getline(cin, NOFLY);
	cust.setNoFly(NOFLY);

	cout << "Agent: ";
	getline(cin, AGENT);
	cust.setAgent(AGENT);

	cout << "Password: ";
	getline(cin, PASSWORD);
	cust.setPassword(PASSWORD);

	convert << CARDNUM;
	string convCARDNUM = convert.str();
	
	convert << FREQFLIERPTS;
	string convFlierPts = convert.str();
	
	cust.createCust();
	
}

void CustomerProfileController::editCustomer(){
	
}

void CustomerProfileController::deleteCustomer(){
	std::string e;

	cout << "Input the email of the account you wish to delete: ";
	cin>>e;

	cout << endl;
	
	Customer cust(db);
	cust.getByEmail(e);
	cust.deleteCust();

}




