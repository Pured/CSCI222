#include "CustomerUI.h"
#include "sqlite3.h"

CustomerUI::CustomerUI(sqlite3* d){
	db = d;
    userType = "Customer";
}

bool CustomerUI::run(){
    string input = "";
    cout<<"\t\t\tCUSTOMER HOME"<<endl;
    cout<<"please select an option: "<<endl;
    cout<<"1) Manage Flights. "<<endl;
    cout<<"2) Modify personal details"<<endl;
    cout<<"3) View frequent flier points."<<endl;
    cout<<"3) Close account"<<endl;
    cout<<"4) Log Out."<<endl;
    cout<<"Your choice: ";
    cin>>input;

    if(input == "1"){
        manageFlights();
    }
    else if(input == "2"){
        manageDetails();
    }
    else if(input == "4"){
        return 1;
    }

    return 1;
}

void CustomerUI::manageFlights(){
    string input = "";
    cout<<"\t\t\tCUSTOMER MANAGE FLIGHTS"<<endl;
    cout<<"please select an option: "<<endl;
    cout<<"1) Book Flight. "<<endl;
    cout<<"2) Cancel Flight"<<endl;
    cout<<"3) Manage Flight Services"<<endl;
    cout<<"4) Manage seating"<<endl;
    cout<<"5) View Booked Flights"<<endl;
    cout<<"6) Back to customer home. "<<endl;
    cout<<"Your choice: ";
    cin>>input;

    if(input == "6"){
        run();
    }

    return;
}

void CustomerUI::manageDetails(){
    string input = "";
    cout<<"\t\t\tCUSTOMER MANAGE DETAILS"<<endl;
    cout<<"please select an option: "<<endl;
    cout<<"1) Modify Name. "<<endl;
    cout<<"2) Modify Gender"<<endl;
    cout<<"3) Modify Date Of Birth."<<endl;
    cout<<"4) Modify Contact details"<<endl;
    cout<<"5) Modify Address"<<endl;
    cout<<"6) Modify Credit Card Details"<<endl;
    cout<<"7) Modify Passport details."<<endl;
    cout<<"8) Back to customer flight management. "<<endl;
    cout<<"Your choice: ";
    cin>>input;

    if(input == "8"){ // return to customer home
        manageFlights();
    }

    return;
}
