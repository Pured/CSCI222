/*=============================================================
| Modified by: kb100
| Version: 1.01
| Modification: Restyled the code.
|==============================================================*/

#include <iostream>
#include "CustomerUI.h"
#include "CustomerProfileController.h"
#include "Customer.h"

using namespace std;

CustomerUI::CustomerUI(sqlite3 *d){
	db = d;
	userType = "Customer";
	username = "Username not set";
}

void CustomerUI::setUsername(string i){
	username = i;
}

bool CustomerUI::run(){
	Customer cust(db);

	string input = "-1";

	while(input != "0"){
		cout << "\t\t\tCUSTOMER HOME" << endl;
		cout << "Please select an option: " << endl;
		cout << "1) Manage Flights. " << endl;
		cout << "2) View personal details." << endl;
		cout << "3) Edit personal details." << endl;
		cout << "4) View frequent flier points." << endl;
		cout << "5) Close an account." << endl;
		cout << "0) Log out." << endl;
		cout << "Your choice: ";
		cin >> input;

		if(input == "1"){
			manageFlights();
		}
		else if(input == "2"){
			cust.getByEmail(username);
			cout << cust << endl;
		}
		else if(input == "3"){
			manageDetails();
		}
		else if(input == "4"){
			cout << "NOT IMPLEMENTED.\n\n";
		}
		else if(input == "5"){
			cout << "NOT IMPLEMENTED.\n\n";
		}
		else if(input == "0"){
		    //...
		}
		else{
			cout << "Invalid Input.\n\n";
		}
	}

	return 1;
}

void CustomerUI::manageFlights(){
    string input = "-1";

	while(input != "0"){
		cout << "\t\t\tCUSTOMER MANAGE FLIGHTS" << endl;
		cout << "Please select an option: " << endl;
		cout << "1) Book a flight." << endl;
		cout << "2) Cancel a flight." << endl;
		cout << "3) Manage flight services." << endl;
		cout << "4) Manage seating." << endl;
		cout << "5) View booked flights." << endl;
		cout << "0) Back to customer menu. " << endl;
		cout << "Your choice: ";
		cin >> input;

		if(input == "1"){
			cout << "NOT IMPLEMENTED.\n\n";
		}
		else if(input == "2"){
			cout << "NOT IMPLEMENTED.\n\n";
		}
		else if(input == "3"){
			cout << "NOT IMPLEMENTED.\n\n";
		}
		else if(input == "4"){
			cout << "NOT IMPLEMENTED.\n\n";
		}
		else if(input == "5"){
			cout << "NOT IMPLEMENTED.\n\n";
		}
		else if(input == "0"){
		    //...
		}
		else{
			cout << "Invalid input.\n\n";
		}
	}
}

void CustomerUI::manageDetails(){
	CustomerProfileController cpc(db);

	cpc.editCustomer(userType,username);

	return;
}
