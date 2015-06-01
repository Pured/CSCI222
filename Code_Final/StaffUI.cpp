/*=============================================================
| Modified by: kb100
| Version: 1.01
| Modification: Restyled the code.
|==============================================================*/

#include <iostream>
#include "StaffUI.h"
#include <string>

using namespace std;

StaffUI::StaffUI(sqlite3 *d){
	db = d;
	userType = "Staff";
}

bool StaffUI::run(){
	string input;
	cout << "\t\t\tSTAFF HOME\n";
	cout << "Please choose an option:\n";
	cout << "1) Search for customer.\n";
	cout << "2) Log Out.\n";
	cout << "Your choice: ";
	cin >> input;

	if(input == "1"){
		cout << "Not Implemented.\n";
	}
	else if(input == "2"){
		return 1;
	}
	else{
		cout << "Invalid Input.\n";
	}

	return 0;
}
