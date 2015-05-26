/*=============================================================
| Modified by: kb100
| Version: 1.03
| Modification: Restyled the code.
|==============================================================*/

#include <iostream>
#include "ProfileManagerUI.h"
#include "ProfileManagerController.h"

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
		cout << "1) Search for a customer.\n";
		cout << "2) Access profile reports.\n";
		cout << "0) Log out.\n\n";
		cout << "Your choice: ";
		cin >> input;

		cout << endl;

		if(input == "1"){
			pmc.findCustomer();
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
