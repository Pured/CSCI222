#include "FlightManagerUI.h"
#include "sqlite3.h"

FlightManagerUI::FlightManagerUI(sqlite3* d){
	db = d;
    userType = "FlightManager";
}

bool FlightManagerUI::run(){
    string input = "";
    cout<<"\t\t\tFlight Manager Home"<<endl;
    cout<<"please choose an option: "<<endl;
    cout<<"1) Access Aircrafts."<<endl;
    cout<<"2) Access Schedules."<<endl;
    cout<<"3) Access Airports."<<endl;
    cout<<"4) Access Routes."<<endl;
    cout<<"5) Access Flight reports."<<endl;
    cout<<"6) Log out."<<endl;
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
        cout<<"Not Implemented"<<endl;
    }
    else if(input == "5"){
        cout<<"Not Implemented"<<endl;
    }
    else if(input == "6"){
        return 1;
    }
    else{
        cout<<"Invalid Input"<<endl;
    }

    return 0;
}
