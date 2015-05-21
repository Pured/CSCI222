

#include "TravelAgentUI.h"
#include "BookingManagerUI.h"


TravelAgentUI::TravelAgentUI(sqlite3* d) {
    db = d;
    userType = "TravelAgent";
    
}

bool TravelAgentUI::run() {
    string input = "";
	
	while(input != "0"){
			cout<<"\t\t\tTRAVEL AGENT HOME"<<endl;
			cout<<"please select an option: "<<endl;
			cout<<"1) Book flight for a customer. "<<endl;
			cout<<"2) View all bookings made."<<endl;
			cout<<"3) Add new customer."<<endl;
			cout<<"4) Edit own details."<<endl;
			cout<<"0) Log Out."<<endl;
			cout<<"Your choice: ";
			cin>>input;
			
			if(input == "1"){
				BookingManagerUI bmUI(db);
				input = bmUI.run();
				//bookFlights();
			}
			else if(input == "2"){
				bookingsMade();
			}
			else if(input == "3"){
				addCustomer();
			}
			else if(input == "4"){
				editDetails();
			}
	}

    return 1;
}

void TravelAgentUI::bookingsMade(){
    
    
}

void TravelAgentUI::addCustomer(){
    
    
}

void TravelAgentUI::editDetails(){
    
    
}