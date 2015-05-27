/*=============================================================
| Modified by: kb100
| Version: 1.04
| Modification: Added customerAccessMenu().
|==============================================================*/

#include <iostream>
#include "ProfileManagerUI.h"
#include "ProfileManagerController.h"
#include "CustomerProfileController.h"

using namespace std;

ProfileManagerUI::ProfileManagerUI(sqlite3 *d){
	db = d;
	userType = "ProfileManager";
}

bool ProfileManagerUI::run(){
	ProfileManagerController pmc(db);
	string input = "-1";

	cout << endl;

	while(input != "0"){
		cout << "\t\t\tPROFILE MANAGER HOME\n\n";
		cout << "Please choose an option:\n\n";
		cout << "1) Access customer.\n";
		cout << "2) Access profile reports.\n";
		cout << "0) Log out.\n\n";
		cout << "Your choice: ";
		cin >> input;

		cout << endl;

		if(input == "1"){
			customerAccessMenu();
		}
		else if(input == "2"){
			pmc.profileReport();
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

void ProfileManagerUI::customerAccessMenu(){
	CustomerProfileController cpc(db);
	string input = "-1";

	cout << endl;

	while(input != "0"){
		cout << "Customer Access Menu:\n";
		cout << "Please choose an option:\n\n";
		cout << "1) Search for a customer.\n";
		cout << "2) Create a new customer.\n";
		cout << "3) Edit a customer.\n";
		cout << "4) Delete a customer.\n";
		cout << "0) Return to main menu.\n\n";
		cout << "Your choice: ";
		cin >> input;

		cout << endl;

		if(input == "1"){
			cpc.findCustomer();
		}
		else if(input == "2"){
			cpc.createCustomer();
		}
		else if(input == "3"){
			cpc.editCustomer(userType,"");
		}
		else if(input == "4"){
			cpc.deleteCustomer();
		}
		else if(input == "0"){
			//...
		}
		else{
			cout << "Invalid input.\n\n";
		}
	}
}
