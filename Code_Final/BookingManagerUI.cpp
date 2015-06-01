/*=============================================================
| Modified by: kb100
| Version: 1.04
| Modification: Removed customerAccessMenu().
|==============================================================*/

#include <iostream>
#include <sstream>
#include "BookingManagerUI.h"
#include "BookingManagerController.h"
#include "CustomerProfileController.h"

using namespace std;

BookingManagerUI::BookingManagerUI(sqlite3 *d){
	db = d;
	userType = "BookingManager";
}

bool BookingManagerUI::run(){
	BookingManagerController bmc(db);
	CustomerProfileController cpc(db);
	string input = "-1";

	cout << endl;

	while(input != "0"){
		cout << "\t\t\tBOOKING MANAGER HOME\n\n";
		cout << "Please choose an option:\n\n";
		cout << "1) Search for a customer.\n";
		cout << "2) Access the no-fly list.\n";
		cout << "3) Access booking reports.\n";
		cout << "0) Log out\n\n";
		cout << "Your choice: ";
		cin >> input;

		cout << endl;

		if(input == "1"){
			cpc.findCustomer();
		}
		else if(input == "2"){
			bmc.checkNoFly();
		}
		else if(input == "3"){
			bmc.bookingReport();
		}
		else if(input == "0"){
			return 1;
		}
		else{
			cout << "Invalid input.\n\n";
		}
	}

	return 0; 
}
