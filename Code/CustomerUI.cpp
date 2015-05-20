#include "CustomerUI.h"
#include "Customer.h"
#include "CustomerProfileController.h"
#include "sqlite3.h"

CustomerUI::CustomerUI(sqlite3* d){
	db = d;
    userType = "Customer";
}

bool CustomerUI::run(){
	Customer cust(db);

	string input = "-1";

	while(input!="0"){
		cout<<"\t\t\tCUSTOMER HOME"<<endl;
		cout<<"please select an option: "<<endl;
		cout<<"1) Manage Flights. "<<endl;
		cout<<"2) View personal details"<<endl;
		cout<<"3) Edit personal details"<<endl;
		cout<<"4) View frequent flier points."<<endl;
		cout<<"5) Close account"<<endl;
		cout<<"0) Log Out."<<endl;
		cout<<"Your choice: ";
		cin>>input;

		if(input == "1"){
			manageFlights();
		}
		else if(input == "2"){
			cust.getByEmail(cust.getEmail());
		}
		else if(input == "3"){
			manageDetails();
		}
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
	Customer cust(db);

	string input = "-1";
	string change = "";
	long long int cardNum = 0, freqPts = 0;

	while(input!="0"){
		cout<<"Customer Edit Menu:\n";
		cout<<"Please choose an option:\n\n";
		cout<<"1) Edit title.\n";
		cout<<"2) Edit given name.\n";
		cout<<"3) Edit surname.\n";
		cout<<"4) Edit gender.\n";
		cout<<"5) Edit D.O.B.\n";
		cout<<"6) Edit phone number.\n";
		cout<<"7) Edit email.\n";
		cout<<"8) Edit address.\n";
		cout<<"9) Edit state.\n";
		cout<<"10) Edit city.\n";
		cout<<"11) Edit country.\n";
		cout<<"12) Edit credit card type.\n";
		cout<<"13) Edit card number.\n";
		cout<<"14) Edit passport.\n";
		cout<<"0) Return to previous menu.\n\n";
		cout<<"Your Choice: ";
		cin>>input;

		cout << endl;

		if(input == "1"){
			cin.ignore();
			cout << "New title: ";
			getline(cin, change);
			cust.setTitle(change);
		}
		else if(input == "2"){
			cin.ignore();
			cout << "New given name: ";
			getline(cin, change);
			cust.setFName(change);
		}
		else if(input == "3"){
			cin.ignore();
			cout << "New surname: ";
			getline(cin, change);
			cust.setLName(change);
		}
		else if(input == "4"){
			cin.ignore();
			cout << "New gender: ";
			getline(cin, change);
			cust.setGender(change);
		}
		else if(input == "5"){
			cin.ignore();
			cout << "New D.O.B.: ";
			getline(cin, change);
			cust.setDOB(change);
		}
		else if(input == "6"){
			cin.ignore();
			cout << "New phone number: ";
			getline(cin, change);
			cust.setPhone(change);
		}
		else if(input == "7"){
			cin.ignore();
			cout << "New email: ";
			getline(cin, change);
			cust.setEmail(change);
		}
		else if(input == "8"){
			cin.ignore();
			cout << "New address: ";
			getline(cin, change);
			cust.setAddress(change);
		}
		else if(input == "9"){
			cin.ignore();
			cout << "New city: ";
			getline(cin, change);
			cust.setCity(change);
		}
		else if(input == "10"){
			cin.ignore();
			cout << "New state: ";
			getline(cin, change);
			cust.setState(change);
		}
		else if(input == "11"){
			cin.ignore();
			cout << "New country: ";
			getline(cin, change);
			cust.setCountry(change);
		}
		else if(input == "12"){
			cin.ignore();
			cout << "New card type: ";
			getline(cin, change);
			cust.setCardType(change);
		}
		else if(input == "13"){
			cin.ignore();
			cout << "New card number: ";
			cin >> cardNum;
			cust.setCardNum(cardNum);
		}
		else if(input == "14"){
			cin.ignore();
			cout << "New passport: ";
			getline(cin, change);
			cust.setPassport(change);
		}
		else if(input == "0"){
			//...
		}
		else{
			cout<<"Invalid Input\n\n";
		}
	}

	cust.update();

    return;
}
