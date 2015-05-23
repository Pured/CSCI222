/*=============================================================
| Modified by: kb100
| Version: 1.02
| Modification: Implemented the UI and Controller.
|==============================================================*/

#include "ServiceManagerUI.h"
#include "ServiceManagerController.h"
#include "sqlite3.h"
#include <sstream>

ServiceManagerUI::ServiceManagerUI(sqlite3* d){
	db = d;
    userType = "ServiceManager";
}

bool ServiceManagerUI::run(){
	ServiceManagerController smc(db);
	string input = "-1";

	cout << endl;

	while(input!="0"){
		cout<<"\t\t\tSERVICE MANAGER HOME\n\n";
		cout<<"Please choose an option:\n\n";
		cout<<"1) Search for a flight.\n";
		cout<<"2) Access service items.\n";
		cout<<"3) Access service reports.\n";
		cout<<"0) Log out.\n\n";
		cout<<"Your choice: ";
		cin>>input;

		cout << endl;

		if(input == "1"){
			smc.findFlight();
		}
		else if(input == "2"){
			serviceItemUI();
		}
		else if(input == "3"){
			smc.serviceReport();
		}
		else if(input == "0"){
			return 1;
		}
		else{
			cout<<"Invalid input.\n\n";
		}
	}

	return 0;
}

void ServiceManagerUI::serviceItemUI(){
	ServiceManagerController smc(db);
	string input = "-1";

	cout << endl;

	while(input!="0"){
		cout<<"Service Items Menu:\n\n";
		cout<<"Please choose an option:\n\n";
		cout<<"1) View service items.\n";
		cout<<"2) Add service items.\n";
		cout<<"3) Edit service items.\n";
		cout<<"4) Remove service items.\n";
		cout<<"0) Return to main menu.\n\n";
		cout<<"Your choice: ";
		cin>>input;

		cout << endl;

		if(input == "1"){
			smc.findService();
		}
		else if(input == "2"){
			smc.createService();
		}
		else if(input == "3"){
			smc.editService();
		}
		else if(input == "4"){
			smc.deleteService();
		}
		else if(input == "0"){
			//...
		}
		else{
			cout<<"Invalid input.\n\n";
		}
	}
}
