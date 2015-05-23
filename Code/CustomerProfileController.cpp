/*=============================================================
| Modified by: kb100
| Version: 1.01
| Modification: Restyled the code.
|==============================================================*/

#include <iostream>
#include <cstdlib>
#include <sstream>
#include "CustomerProfileController.h"
#include "Customer.h"
#include "sqlite3.h"

using namespace std;

CustomerProfileController::CustomerProfileController(sqlite3 *d){
	db = d;
}

// Validates a login of a staff member. Called from validateLogin().
string CustomerProfileController::registerExistingCustomer(string uname, string pwd){
	Customer c(db);
	c.getByEmail(uname);

	c.setPassword(pwd);
	int ret = c.update();

	if(ret == 1){
		return "INVALID";
	}

	return "SUCCESSFUL REGISTRATION";
}

void CustomerProfileController::findCustomer(){
	string e;

	cout << "Input the customer's email: ";
	cin >> e;

	cout << endl;

	Customer cust(db);
	cust.getByEmail(e);
	cout << cust << endl;
}

void CustomerProfileController::createCustomer(){
	// Create variables to store data.
	int lastID = 0, ID = 0;
	long long int CARDNUM = 0, FREQFLIERPTS = 0;
	string TITLE = "", FNAME = "", LNAME = "", GENDER = "", DOB = "", PHONE = "", EMAIL = "", ADDRESS = "", STATE = "", COUNTRY = "", CITY = "", CARDTYPE = "", PASSPORT = "", NOFLY = "", AGENT = "", PASSWORD = "", CARDNUMTEMP = "", FREQFLIERPTSTEMP = "";

	cout << "Creating a new Customer..." << endl;
	Customer cust(db); // Customer ID automoatically assigned in Customer.createCust().

	stringstream convert;

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
	cust.setDOB(DOB); // Must check format is YYYY-MM-DD.

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
	CARDNUM = atoll(CARDNUMTEMP.c_str());
	cust.setCardNum(CARDNUM);

	cout << "Frequent Flier Points: ";
	cin >> FREQFLIERPTSTEMP;
	FREQFLIERPTS = atoll(FREQFLIERPTSTEMP.c_str());
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

void CustomerProfileController::editCustomer(string userType, string username){
	// If called from CustomerUI, use CustomerProfileController.editCustomer(userType,username);.
	// If called from staff member, use CustomerProfileController.editCustomer(userType,"");.

	// Find what type of user is calling this function.
	if(userType == "Customer"){
		Customer cust(db);
		cust.getByEmail(username); // Use provided username for email.

		string input = "-1";
		string change = "";
		long long int cardNum = 0, freqPts = 0;

		while(input != "0"){
			cout << "Customer Edit Menu:\n";
			cout << "Please choose an option:\n\n";
			cout << "1) Edit title.\n";
			cout << "2) Edit given name.\n";
			cout << "3) Edit surname.\n";
			cout << "4) Edit gender.\n";
			cout << "5) Edit D.O.B.\n";
			cout << "6) Edit phone number.\n";
			cout << "7) Edit email.\n";
			cout << "8) Edit address.\n";
			cout << "9) Edit state.\n";
			cout << "10) Edit city.\n";
			cout << "11) Edit country.\n";
			cout << "12) Edit credit card type.\n";
			cout << "13) Edit card number.\n";
			cout << "14) Edit passport.\n";
			cout << "0) Return to previous menu.\n\n";
			cout << "Your Choice: ";
			cin >> input;

			cout << endl;

			if(input == "1"){
				cin.ignore();
				cout << "New title: ";
				getline(cin, change);
				cust.setTitle(change);
			}
			else if(input == "2"){
				cin.ignore();
				cout << "New given name: ";
				getline(cin, change);
				cust.setFName(change);
			}
			else if(input == "3"){
				cin.ignore();
				cout << "New surname: ";
				getline(cin, change);
				cust.setLName(change);
			}
			else if(input == "4"){
				cin.ignore();
				cout << "New gender: ";
				getline(cin, change);
				cust.setGender(change);
			}
			else if(input == "5"){
				cin.ignore();
				cout << "New D.O.B.: ";
				getline(cin, change);
				cust.setDOB(change);
			}
			else if(input == "6"){
				cin.ignore();
				cout << "New phone number: ";
				getline(cin, change);
				cust.setPhone(change);
			}
			else if(input == "7"){
				cin.ignore();
				cout << "New email: ";
				getline(cin, change);
				cust.setEmail(change);
			}
			else if(input == "8"){
				cin.ignore();
				cout << "New address: ";
				getline(cin, change);
				cust.setAddress(change);
			}
			else if(input == "9"){
				cin.ignore();
				cout << "New city: ";
				getline(cin, change);
				cust.setCity(change);
			}
			else if(input == "10"){
				cin.ignore();
				cout << "New state: ";
				getline(cin, change);
				cust.setState(change);
			}
			else if(input == "11"){
				cin.ignore();
				cout << "New country: ";
				getline(cin, change);
				cust.setCountry(change);
			}
			else if(input == "12"){
				cin.ignore();
				cout << "New card type: ";
				getline(cin, change);
				cust.setCardType(change);
			}
			else if(input == "13"){
				cin.ignore();
				cout << "New card number: ";
				cin >> cardNum;
				cust.setCardNum(cardNum);
			}
			else if(input == "14"){
				cin.ignore();
				cout << "New passport: ";
				getline(cin, change);
				cust.setPassport(change);
			}
			else if(input == "0"){
				//...
			}
			else{
				cout << "Invalid Input\n\n";
			}
		}

		cust.update();
	}
	else if(userType == "BookingManager" || userType == "ServiceManager" || userType == "FlightManager" || userType == "ProfileManager" || userType == "Administrator"){
		Customer cust(db);

		string e = "";
		cout << "Input the email of the customer you wish to edit: ";
		cin >> e;

		cust.getByEmail(e); // Get customer using user input for email.
		cout << cust;

		string input = "-1";
		string change = "";
		long long int cardNum = 0, freqPts = 0;

		cout << endl;

		while(input != "0"){
			cout << "Customer Edit Menu:\n";
			cout << "Please choose an option:\n\n";
			cout << "1) Edit title.\n";
			cout << "2) Edit given name.\n";
			cout << "3) Edit surname.\n";
			cout << "4) Edit gender.\n";
			cout << "5) Edit D.O.B.\n";
			cout << "6) Edit phone number.\n";
			cout << "7) Edit email.\n";
			cout << "8) Edit address.\n";
			cout << "9) Edit state.\n";
			cout << "10) Edit city.\n";
			cout << "11) Edit country.\n";
			cout << "12) Edit credit card type.\n";
			cout << "13) Edit card number.\n";
			cout << "14) Edit frequent flier points.\n";
			cout << "15) Edit passport.\n";
			cout << "16) Edit no-fly status.\n";
			cout << "17) Edit travel agent.\n";
			cout << "0) Return to previous menu.\n\n";
			cout << "Your Choice: ";
			cin >> input;

			cout << endl;

			if(input == "1"){
				cin.ignore();
				cout << "New title: ";
				getline(cin, change);
				cust.setTitle(change);
			}
			else if(input == "2"){
				cin.ignore();
				cout << "New given name: ";
				getline(cin, change);
				cust.setFName(change);
			}
			else if(input == "3"){
				cin.ignore();
				cout << "New surname: ";
				getline(cin, change);
				cust.setLName(change);
			}
			else if(input == "4"){
				cin.ignore();
				cout << "New gender: ";
				getline(cin, change);
				cust.setGender(change);
			}
			else if(input == "5"){
				cin.ignore();
				cout << "New D.O.B.: ";
				getline(cin, change);
				cust.setDOB(change);
			}
			else if(input == "6"){
				cin.ignore();
				cout << "New phone number: ";
				getline(cin, change);
				cust.setPhone(change);
			}
			else if(input == "7"){
				cin.ignore();
				cout << "New email: ";
				getline(cin, change);
				cust.setEmail(change);
			}
			else if(input == "8"){
				cin.ignore();
				cout << "New address: ";
				getline(cin, change);
				cust.setAddress(change);
			}
			else if(input == "9"){
				cin.ignore();
				cout << "New city: ";
				getline(cin, change);
				cust.setCity(change);
			}
			else if(input == "10"){
				cin.ignore();
				cout << "New state: ";
				getline(cin, change);
				cust.setState(change);
			}
			else if(input == "11"){
				cin.ignore();
				cout << "New country: ";
				getline(cin, change);
				cust.setCountry(change);
			}
			else if(input == "12"){
				cin.ignore();
				cout << "New card type: ";
				getline(cin, change);
				cust.setCardType(change);
			}
			else if(input == "13"){
				cin.ignore();
				cout << "New card number: ";
				cin >> cardNum;
				cust.setCardNum(cardNum);
			}
			else if(input == "14"){
				cin.ignore();
				cout << "New amount of frequent flier points: ";
				cin >> freqPts;
				cust.setFreqPts(freqPts);
			}
			else if(input == "15"){
				cin.ignore();
				cout << "New passport: ";
				getline(cin, change);
				cust.setPassport(change);
			}
			else if(input == "16"){
				cin.ignore();
				cout << "New no-fly status: ";
				getline(cin, change);
				cust.setNoFly(change);
			}
			else if(input == "17"){
				cin.ignore();
				cout << "New travel agent: ";
				getline(cin, change);
				cust.setAgent(change);
			}
			else if(input == "0"){
				//...
			}
			else{
				cout << "Invalid Input\n\n";
			}
		}

		cust.update();
	}
}

void CustomerProfileController::deleteCustomer(){
	string e;

	cout << "Input the email of the account you wish to delete: ";
	cin >> e;

	cout << endl;

	Customer cust(db);
	cust.getByEmail(e);
	cust.deleteCust();
}
