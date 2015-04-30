#include "GuestUI.h"
#include "StaffUI.h"
#include <string>
#include "LoginController.h"

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
	
	if(temp == "STAFF"){
		//create and run staff UI
		StaffUI sUI(db);
		sUI.run();
	}

    return;
};
