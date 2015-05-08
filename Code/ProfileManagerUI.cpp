#include "ProfileManagerUI.h"
#include "sqlite3.h"

ProfileManagerUI::ProfileManagerUI(sqlite3* d){
	db = d;
    userType = "ProfileManager";
}

bool ProfileManagerUI::run(){
    string input = "";
    cout<<"\t\t\tPROFILE MANAGER HOME"<<endl;
    cout<<"please choose an option"<<endl;
    cout<<"1) Search for customer."<<endl;
    cout<<"2) Access profile reports."<<endl;
    cout<<"3) Log Out."<<endl;
    cout<<"Your choice: ";
    cin>>input;
    
    if(input == "1"){
        cout<<"Not Implemented"<<endl;
    }
    else if( input == "2"){
        cout<<"Not Implemented"<<endl;
    }
    else if(input == "3"){
        return 1;
    }
    else{
        cout<<"Invalid Input"<<endl;
    }

    return 0;
}
