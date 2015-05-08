#include "BookingManagerUI.h"
#include <iostream>
#include "sqlite3.h"

using namespace std;

BookingManagerUI::BookingManagerUI(sqlite3* d){
	db = d;
    userType = "BookingManager";
}

bool BookingManagerUI::run(){
    string input;
    cout<<"\t\t\t BOOKING MANAGER HOME"<<endl;
    cout<<"Please choose an option: \n"<<endl;
    cout<<"1) Search for a customer."<<endl;
    cout<<"2) Access No-fly list."<<endl;
    cout<<"3) Access Booking reports."<<endl;
    cout<<"4) Log Out"<<endl;
    cout<<"Your Choice: ";
    cin>>input;
    
    if(input == "1"){
        cout<<"Not Implemented"<<endl;
    }
    else if( input == "2"){
        cout<<"Not Implemented"<<endl;
    }
    else if(input == "3"){
        cout<<"Not Implemented"<<endl;
    }
    else if(input == "4"){
        return 1;
    }
    else{
        cout<<"Invalid Input"<<endl;
    }

    return 0;
}
