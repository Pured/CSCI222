/*=============================================================
| Modified by: kb100
| Version: 1.04
| Modification: Fixed for linux + fixed code style.
|==============================================================*/

#include <iostream>
#include "GuestUI.h"
#include "StaffUI.h"
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
//#include <conio.h>

using namespace std;

GuestUI::GuestUI(sqlite3 *d){
	db = d;
	userType = "Guest";
	userNum = 0;
}

int GuestUI::run(){
	string input = "";
	cout << "\t\t\tGUEST HOME\n";
	cout << "please choose an option:\n\n";
	cout << "1) login.\n";
	cout << "2) Register.\n";
	cout << "3) Search for flight.\n";
	cout << "0) Exit system.\n";
	cout << "Your choice: ";
	cin >> input;

	if(input == "1"){
		login();
	}
	else if(input == "2"){
		CustomerProfileController cpc(db);
		cpc.createCustomer();
	}
	else if(input == "3"){
		guestSearch();
	}
	else if(input == "0"){
		return 1;
	}
	else{
		cout << "Invalid input.\n\n";
	}

	return 0;
}

void GuestUI::setType(string type){
	userType = type;

	return;
}

string GuestUI::getType(){
	return userType;
}

int GuestUI::getNum(){
	return userNum;
}

void GuestUI::setNum(int num){
	userNum = num;

	return;
}

#ifdef __unix__
int GuestUI::getch(){
	int ch;
	struct termios t_old, t_new;
		
	tcgetattr(STDIN_FILENO, &t_old);
	t_new = t_old;
	t_new.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &t_new);
		
	ch = getchar();
		
	tcsetattr(STDIN_FILENO, TCSANOW, &t_old);

	return ch;
}

string GuestUI::getpass_lin(const char *prompt){
	const char BACKSPACE = 127;
	const char RETURN = 10;

	string password;
	unsigned char ch = 0;

	cout << prompt << endl;

	while((ch=getch()) != RETURN){
		if(ch == BACKSPACE){
			if(password.length() != 0){
				cout << "\b \b";
				password.resize(password.length() - 1);
			}
		}
		else{
			password += ch;
			cout << '*';
		}
	}

	cout << endl;

	return password;
}
#endif

#ifdef _WIN32
string GuestUI::getpass_win(const char *prompt){
	const char BACKSPACE = 8;
	const char RETURN = 13;

	string password;
	unsigned char ch = 0;

	cout << prompt << endl;

	while((ch=getch()) != RETURN){
		if(ch == BACKSPACE){
			if(password.length() != 0){
				cout << "\b \b";
				password.resize(password.length() - 1);
			}
		}
		else if(ch == 0 || ch == 224){ // Handle escape sequences.
			getch(); // Ignore non-printable chars.

			continue;
		}
		else{
			password += ch;

			cout << '*';
		}
	}

	cout << endl;

	return password;
}
#endif

void GuestUI::login(){
	string inputUN = "";
	string inputPWD = "";

	cout << "Enter your username: ";
	cin >> inputUN;
    
#ifdef __unix__
    inputPWD = getpass_lin("Please enter the password: "); //Mask input show asterisks
#endif
    
#ifdef _WIN32
    inputPWD = getpass_win("Please enter the password: "); //Mask input, show asterisks
#endif
    
#ifdef __linux__
    inputPWD = getpass_lin("Please enter the password: "); //Mask input show asterisks
#endif

#ifdef _WIN32
    system("cls");
#endif

#ifdef __APPLE__
    system("clear");
#endif

	// Use logincontroller to validate and return the userType.
	LoginController LC(db);
	string temp = LC.validateLogin(inputUN, inputPWD);

	if(temp == "STAFF"){
		StaffUI sUI(db); // Create staff UI.
		sUI.run(); // Run staff UI.
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
		cout << "This exisiting account has not been registered with the system. Please register first.\n";
		registerExistingCustomer();
	}
	else if(temp == "NOT FOUND"){
		cout << "Account not found.\n";

		return;
	}
	else if(temp == "INCORRECT PASSWORD"){
		cout << "Password is incorrect. Try again.\n";

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
	string inputUN = "";
	string inputPWD = "";
	cout << "\t\t\tREGISTER EXISTING CUSTOMER TO SYSTEM\n";
	cout << "Enter your username: ";
	cin >> inputUN;

	Customer c(db);
	string existing = c.getByEmail(inputUN);

	if(existing == "NOT FOUND"){
		cout << "Create new customer not implemented yet.\n";

		return;
	}

	cout << "Enter your new password: ";
	cin >> inputPWD;

	CustomerProfileController CPC(db);
	string result = CPC.registerExistingCustomer(inputUN, inputPWD);

	if(result == "SUCCESSFUL REGISTRATION"){
		cout << "You have successfully registered to the system. please log in again.\n";
	}
	else{
		cout << "Invalid input. please try again.\n";
	}

	return;
}

void GuestUI::guestSearch(){
	string fromDate, toDate, fromName, toName;

	Airport fromAirport(db);
	Airport toAirport(db);

	// Get input from user about departing airport.

	cin.ignore();
	bool correct = false;

	while(correct == false){
		cout << "Enter name of airport to leave from (type 'list' for airport list): ";
		getline(cin, fromName);

		if(fromName == "list"){
			fromAirport.alphabeticList();
		}
		else{
			string check = fromAirport.getByName(fromName);
			//cout<<check<<endl;
			if(check == "FOUND"){
				correct = true;
			}
			else{
				cout << "Invalid airport selection. Try again." << endl;
			}
		}
	}

	correct = false;

	while(correct == false){
		cout << "Enter name of airport to arrive at (type 'list' for airport list): ";
		getline(cin, toName);

		if (toName == "list"){
			toAirport.alphabeticList();
		}
		else{
			string check = toAirport.getByName(toName);
			//cout<<check<<endl;
			if(check == "FOUND"){
				correct = true;
			}
			else{
				cout << "Invalid airport selection. Try again." << endl;
			}
		}

	}

	Route route(db);
	int routeCheck = route.getByAirports(fromAirport.getIATA(), toAirport.getIATA());

	if(routeCheck == -1){
		cout << "No route between " + fromAirport.getName() + " and " + toAirport.getName() + "available.\n";

		return;
	}

	cout << "Enter a date to search from(YYYY-MM-DD): ";
	cin >> fromDate;
	cout << "Enter a date to search to(YYYY-MM-DD): ";
	cin >> toDate;

	ScheduleController SC(db);
	int amtResults = 0;
	Schedule* results = SC.search(fromDate, toDate, amtResults, 1);

	cout << amtResults << endl;

	for(int i = 0; i < amtResults; i++){
		cout << "Flight " << results[i].getFlightID() << ": ";
		cout << results[i].getDepartDay() << " ";
		cout << results[i].getDepart() << " ";
		cout << results[i].getDepartTimezone() << endl;
	}

	delete[] results;
	results = NULL;
}
