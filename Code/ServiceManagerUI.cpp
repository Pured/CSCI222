#include "ServiceManagerUI.h"
#include "sqlite3.h"

ServiceManagerUI::ServiceManagerUI(sqlite3* d){
	db = d;
    userType = "ServiceManager";
}

bool ServiceManagerUI::run(){
    string input;
    cout<<"\t\t\tSERVICE MANAGER HOME"<<endl;
    cout<<"please select an option: "<<endl;
    cout<<"1) Search for flight"<<endl;
    cout<<"2) Access Service Items"<<endl;
    cout<<"3) Access Service Reports."<<endl;
    cout<<"4) Log Out."<<endl;
    cout<<"Your choice: ";
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
