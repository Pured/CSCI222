/*=============================================================
| Modified by: kb100
| Version: 1.01
| Modification: Restyled the code.
|==============================================================*/

#include <iostream>
#include "TravelAgent.h"
#include "TravelAgentUI.h"
#include "BookingManagerUI.h"
#include "BookingController.h"
#include "CustomerProfileController.h"
#include "clearscreen.h"

using namespace std;

TravelAgentUI::TravelAgentUI(sqlite3 *d){
	db = d;
	userType = "TRAVELAGENT";
    name = "Username not set";
}

TravelAgentUI::TravelAgentUI(sqlite3 *d, std::string e){
    db = d;
    userType = "TRAVELAGENT";
    email = e;
}


bool TravelAgentUI::run(){
	string input = "";
    ClearScreen cl; //For the clear screen function.
    cl.clearScreen();//Clear screen.
    
	while(input != "0"){

		cout << "\t\t\tTRAVEL AGENT HOME" << endl;
		cout << "please select an option: " << endl;
		cout << "1) Book flight for a customer. " << endl;
		cout << "2) View all bookings made." << endl;
		cout << "3) Add new customer." << endl;
		cout << "4) Edit own details." << endl;
        cout << "5) View Own Details." << endl;
		cout << "0) Log Out." << endl;
		cout << "Your choice: ";
		cin >> input;
        cl.clearScreen();// Clear screen.
		if(input == "1"){
            TravelAgent ta(db);
            ta.setByEmail(email);
			BookingController bc(db);
            bc.makeBooking(userType, ta.getName());
			
		}
		else if(input == "2"){
            bookingsMade();
		}
		else if(input == "3"){
			CustomerProfileController cpc(db);
			cpc.createCustomer();
		}
		else if(input == "4"){
			editDetails();
		}
        else if(input == "5"){
            viewDetails();
        }
	}
	return 1;
}

void TravelAgentUI::bookingsMade(){
    TravelAgent ta(db);
    ta.setByEmail(email);
    BookingController bc(db);
    bc.viewTravelAgentBookings(ta.getName());
    
}

void TravelAgentUI::editDetails(){
    std::string phone, password;
    TravelAgent ta(db);
    ta.setByEmail(email);
    cout << ta << endl;
    cout << "Enter phone number: ";
    cin >> phone;
    cout << "Enter password: ";
    cin >> password;
    ta.setPhone(phone);
    ta.setPassword(password);
    ta.update();
}


void TravelAgentUI::viewDetails(){
    TravelAgent ta(db);
    ta.setByEmail(email);
    cout << ta << endl;
}








