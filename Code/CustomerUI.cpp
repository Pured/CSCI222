#include "CustomerUI.h"
#include "Customer.h"
#include "CustomerProfileController.h"
#include "sqlite3.h"

CustomerUI::CustomerUI(sqlite3* d){
	db = d;
    userType = "Customer";
	username = "Username not set";
}

void CustomerUI::setUsername(std::string i){
	username = i;
}

bool CustomerUI::run(){
	Customer cust(db);

	string input = "-1";

	while(input!="0"){
		cout << "\t\t\tCUSTOMER HOME"<<endl;
		cout << "please select an option: " << endl;
		cout << "1) Manage Flights. " << endl;
		cout << "2) View personal details" << endl;
		cout << "3) Edit personal details" << endl;
		cout << "4) View frequent flier points." << endl;
		cout << "5) Close account" << endl;
		cout << "0) Log Out." << endl;
		cout << "Your choice: ";
		cin >> input;

		if(input == "1"){
			manageFlights();
		}
		else if(input == "2"){
			cust.getByEmail(username);
			cout<<cust<<endl;
		}
		else if(input == "3"){
			manageDetails();
		}

	}

    return 1;
}

void CustomerUI::manageFlights(){
    string input = "";
    cout << "\t\t\tCUSTOMER MANAGE FLIGHTS" << endl;
    cout << "please select an option: " << endl;
    cout << "1) Book Flight. " << endl;
    cout << "2) Cancel Flight" << endl;
    cout << "3) Manage Flight Services" << endl;
    cout << "4) Manage seating" << endl;
    cout << "5) View Booked Flights" << endl;
    cout << "6) Back to customer home. " << endl;
    cout << "Your choice: ";
    cin >> input;

    if(input == "6"){
        run();
    }
    return;
}

void CustomerUI::manageDetails(){
	CustomerProfileController cpc(db);
	cpc.editCustomer(userType,username);
    return;
}
