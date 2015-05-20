/*=============================================================
| Modified by: kb100
| Version: 1.01
| Modification: Implemented the UI and Controller.
|==============================================================*/

#include "BookingManagerUI.h"
#include "BookingManagerController.h"
#include <iostream>
#include <sstream>

using namespace std;

BookingManagerUI::BookingManagerUI(sqlite3* d){
	db = d;
    userType = "BookingManager";
}

bool BookingManagerUI::run(){
	BookingManagerController bmc(db);
	string input = "-1";

	cout << endl;

	while(input!="0"){
		cout<<"\t\t\tBOOKING MANAGER HOME\n\n";
		cout<<"Please choose an option:\n\n";
		cout<<"1) Access a customer.\n";
		cout<<"2) Access the No-fly list.\n";
		cout<<"3) Access booking reports.\n";
		cout<<"0) Log Out\n\n";
		cout<<"Your Choice: ";
		cin>>input;

		cout << endl;

		if(input == "1"){
			customerAccessMenu();
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
			cout<<"Invalid Input\n\n";
		}
	}

	return 0; 
}

void BookingManagerUI::customerAccessMenu(){
	BookingManagerController bmc(db);
	string input = "-1";

	cout << endl;

	while(input!="0"){
		cout<<"Customer Access Menu:\n";
		cout<<"Please choose an option:\n\n";
		cout<<"1) Search for a customer.\n";
		cout<<"2) Create a new customer.\n";
		cout<<"3) Edit a customer.\n";
		cout<<"4) Delete a customer.\n";
		cout<<"0) Return to main menu.\n\n";
		cout<<"Your Choice: ";
		cin>>input;

		cout << endl;

		if(input == "1"){
			bmc.findCustomer();
		}
		else if(input == "2"){
			bmc.createCustomer();
		}
		else if(input == "3"){
			bmc.editCustomer();
		}
		else if(input == "4"){
			bmc.deleteCustomer();
		}
		else if(input == "0"){
			//...
		}
		else{
			cout<<"Invalid Input\n\n";
		}
	}
}
