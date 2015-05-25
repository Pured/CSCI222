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
#include "TravelAgent.h"
#include "Airport.h"
#include "Route.h"
#include "SearchController.h"

GuestUI::GuestUI(sqlite3* d){
	db = d;
    userType = "Guest";
    userNum = 0;

}

int GuestUI::run(){
    std::string input = "";
    std::cout << "\t\t\tGUEST HOME" << std::endl;
    std::cout << "please choose an option:\n\n";
    std::cout << "1) login" << std::endl;
    std::cout << "2) Register" << std::endl;
    std::cout << "3) Search for flight" << std::endl;
    std::cout << "4) Exit system." << std::endl;
    std::cout << "Your choice: ";
    std::cin >> input;

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
    //system("clear");
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
}

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
	SearchController SC(db);
	SC.search(userType,"none");
}


