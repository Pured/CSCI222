
#include "TravelAgentUI.h"
#include "BookingManagerUI.h"


TravelAgentUI::TravelAgentUI(sqlite3* d) {
    db = d;
    userType = "TravelAgent";
    
}

bool TravelAgentUI::run() {
    string input = "";
    cout<<"\t\t\tTRAVEL AGENT HOME"<<endl;
    cout<<"please select an option: "<<endl;
    cout<<"1) Book flight for a customer. "<<endl;
    cout<<"2) View all bookings made."<<endl;
    cout<<"3) Add new customer."<<endl;
    cout<<"4) Edit own details."<<endl;
    cout<<"5) Log Out."<<endl;
    cout<<"Your choice: ";
    cin>>input;
    
    if(input == "1"){
        BookingManagerUI bmUI(db);
        bmUI.run();
        //bookFlights();
    }
    else if(input == "2"){
        cout << "This is 2 " << endl;
        //bookingsMade();
    }
    else if(input == "3"){
        cout << "This is 3 " << endl;
        //addCustomer();
    }
    else if(input == "4"){
        cout << "This is 4 " << endl;
        //editDetails();
    }
    else if(input == "5"){
        return 1;
    }
    return 1;
}

/*
void TravelAgentUI::bookFlights(){

    
}
void TravelAgentUI::bookingsMade(){
    
    
}
void TravelAgentUI::addCustomer(){
    
    
}
void TravelAgentUI::editDetails(){
    
    
}
 */







