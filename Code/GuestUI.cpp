#include "GuestUI.h"
#include "StaffUI.h"
#include <string>
#include "LoginController.h"
#include "CustomerProfileController.h"
#include "ScheduleController.h"
#include "Customer.h"
#include "CustomerUI.h"
#include "ProfileManagerUI.h"
#include "FlightManagerUI.h"
#include "ServiceManagerUI.h"
#include "BookingManagerUI.h"
#include "TravelAgentUI.h"
#include "Airport.h"
#include "Route.h"

GuestUI::GuestUI(sqlite3* d){
	db = d;
    userType = "Guest";
    userNum = 0;

};

int GuestUI::run(){
    std::string input = "";
    std::cout<<"\t\t\tGUEST HOME"<<std::endl;
    std::cout<<"please choose an option:\n\n";
    std::cout<<"1) login"<<std::endl;
    std::cout<<"2) Register"<<std::endl;
    std::cout<<"3) Search for flight"<<std::endl;
    std::cout<<"4) Exit system."<<std::endl;
    std::cout<<"Your choice: ";
    std::cin>>input;

    if(input == "1"){
        login();
    }
    else if(input == "4"){
        return 1;
    }
	else if(input == "2"){
		CustomerProfileController cpc(db);
		cpc.createCustomer();
	}
	else if(input == "3"){
		guestSearch();
	}

    return 0;
}

void GuestUI::setType(std::string type){
    userType = type;

    return;
}

std::string GuestUI::getType(){
    return userType;
}

int GuestUI::getNum(){
    return userNum;
}

void GuestUI::setNum(int num){
    userNum = num;

    return;
}

void GuestUI::login(){
	
	std::string inputUN = "";
	std::string inputPWD = "";
	std::cout<<"Enter your username: ";
	std::cin>>inputUN;
	std::cout<<"Enter your password: ";
	std::cin>>inputPWD;
	
	//use logincontroller to validate and return the userType
	LoginController LC(db);
	std::string temp = LC.validateLogin(inputUN,inputPWD);
	
	//cout<<temp<<endl;
																			
	if(temp == "STAFF"){
		//create and run staff UI
        StaffUI sUI(db);
		sUI.run();
	}
	else if(temp == "PROFILEMANAGER"){
		ProfileManagerUI pmUI(db);
		pmUI.run();
	}
	else if(temp == "FLIGHTMANAGER"){
        FlightManagerUI fmUI(db);
		fmUI.run();
	}
	else if(temp == "SERVICEMANAGER"){
			ServiceManagerUI smUI(db);
			smUI.run();
	}
	else if(temp == "BOOKINGMANAGER"){
		BookingManagerUI bmUI(db);
		bmUI.run();
	}
    else if(temp == "TRAVELAGENT"){
        std::cout << "Are wwe there yet? " << std::endl;
        TravelAgentUI taUI(db);
        taUI.run();
    }
	
	else if(temp == "NOT REGISTERED"){
		cout<<"This exisiting account has not been registered with the system. Please register first.";
		registerExistingCustomer();
	}
	else if(temp == "NOT FOUND"){
		cout<<"Account not found."<<endl;
		return;
	}
	else if(temp == "INCORRECT PASSWORD"){
		cout<<"Password is incorrect. Try again."<<endl;
		return;
	}
	else if(temp == "CUSTOMER"){
		CustomerUI cUI(db);
		cUI.setUsername(inputUN);
		cUI.run();
	}

    return;
};

void GuestUI::registerExistingCustomer(){
	std::string inputUN = "";
	std::string inputPWD = "";
	std::cout<<"\t\t\tREGISTER EXISTING CUSTOMER TO SYSTEM"<<std::endl;
	std::cout<<"Enter your username: ";
	std::cin>>inputUN;
	
	Customer c(db);
	std::string existing = c.getByEmail(inputUN);
	
	if (existing == "NOT FOUND"){
		std::cout<<"Create new customer not implemented yet"<<endl;
		return;
	}
	
	std::cout<<"Enter your new password: ";
	std::cin>>inputPWD;
	
	CustomerProfileController CPC(db);
	std::string result = CPC.registerExistingCustomer(inputUN,inputPWD);
	if(result == "SUCCESSFUL REGISTRATION"){
		std::cout<<"You have successfully registered to the system. please log in again."<<std::endl;
	}
	else{
		std::cout<<"Invalid input. please try again."<<std::endl;
	}
	return;
	
}

void GuestUI::guestSearch(){
	std::string fromDate,toDate,fromName,toName;
	
	Airport fromAirport(db);
	Airport toAirport(db);
	
	//get input from user about departing airport
	
	cin.ignore();
	bool correct = false;
	while(correct == false){
		cout<<"Enter name of airport to leave from (type 'list' for airport list): ";
		getline(cin,fromName);
		
		if(fromName == "list"){
				fromAirport.alphabeticList();
		}
		else{
			std::string check = fromAirport.getByName(fromName);
			//cout<<check<<endl;
			if(check == "FOUND"){
				correct = true;
			}
			else{
				cout<<"Invalid airport selection. Try again."<<endl;
			}
		}
		
	}
	
	//cin.ignore();
	//cout<<"here"<<endl;
	correct = false;
	while(correct == false){
		cout<<"Enter name of airport to arrive at (type 'list' for airport list): ";
		getline(cin,toName);
		
		if(toName == "list"){
				toAirport.alphabeticList();
		}
		else{
			std::string check = toAirport.getByName(toName);
			//cout<<check<<endl;
			if(check == "FOUND"){
				correct = true;
			}
			else{
				cout<<"Invalid airport selection. Try again."<<endl;
			}
		}
		
	}
	
	Route route(db);
	int routeCheck = route.getByAirports(fromAirport.getIATA(),toAirport.getIATA());
	
	if(routeCheck == -1){
		cout<<"No route between " + fromAirport.getName() + " and " + toAirport.getName() + "available";
		return;
	}
	

	
	
	cout<<"Enter a date to search from(YYYY-MM-DD): ";
	cin>>fromDate;
		cout<<"Enter a date to search to(YYYY-MM-DD): ";
	cin>>toDate;
	
	ScheduleController SC(db);
	int amtResults = 0;
	Schedule* results = SC.search(fromDate,toDate,amtResults,1);
	
	cout<<amtResults<<endl;
	
	for(int i = 0; i<amtResults; i++){
		cout<<"Flight "<< results[i].getFlightID()<<": ";
		cout<<results[i].getDepartDay()<<" ";
		cout<<results[i].getDepart()<<" ";
		cout<<results[i].getDepartTimezone()<<endl;
	}
	
	delete[] results;
	results = NULL;
}


