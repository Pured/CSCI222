#include "StaffUI.h"
#include "sqlite3.h"

StaffUI::StaffUI(sqlite3* d){
	db = d;
    userType = "Staff";
}

bool StaffUI::run(){
    std::string input;
    std::cout<<"\t\t\tStaff Home"<<std::endl;
    std::cout<<"Please choose an option:"<<std::endl;
    std::cout<<"1) Search for customer."<<std::endl;
	std::cout<<"2) Log Out"<<std::endl;
    std::cout<<"Your choice: ";
    std::cin>>input;
    
    if(input == "1"){
        std::cout<<"Not Implemented"<<std::endl;
    }
    else if( input == "2"){
        return 1;
    }
    else{
        std::cout<<"Invalid Input"<<std::endl;
    }

    return 0;
}
