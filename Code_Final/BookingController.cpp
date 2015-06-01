/*=============================================================
| Modified by: kb100
| Version: 1.03
| Modification: Cleaned up the code.
|==============================================================*/

#include <iostream>
#include <cstdlib>
#include <sstream>
#include "BookingController.h"
#include "SearchController.h"
#include "Customer.h"
#include "Aircraft.h"
#include "Route.h"
#include "Airport.h"
#include "ServiceItem.h"
#include "clearscreen.h"

using namespace std;

BookingController::BookingController(sqlite3 *d){
	db = d;
	userType = "USERTYPE NOT SET";
}

void BookingController::setType(string user_type){
	userType = user_type;

	return;
}

string BookingController::getType(){
	return userType;
}

bool BookingController::searchSeatingArray(int row, int let, Seat *arr, int size){
	Seat S(db); //using this for conversion function.
	for(int i = 0; i < size; i++){
		if(S.convertSeatNum(row, let) == arr[i].getSeatNum()){
			return true;
		}
	}

	return false;
}

void BookingController::displaySeating(string sClass, Schedule sch){
	Aircraft AC(db);
	stringstream convert;

	convert << sch.getPlane();
	string convPlane = convert.str();
	convert.str(string()); // Clear ss.

	// Get airplane details for seat availability search.
	AC.getByID(convPlane);
	
	// Plane dosen't exist.
	if(AC.getID() == -1){
		cout << "No data for Aircraft." << endl;

		return;
	}

	// Get array of seats from DB by schedule and seat class.
	Seat seating(db);
	int resSize = 0;
	Seat *results = seating.getByScheduleID(sch.getID(), sClass, resSize);
	
	int rowCounter = 1;
	int formatter = AC.getSClassStartPoint(sClass, rowCounter);

	if(formatter == -1){
		cout << "Invalid class for seating display.";

		return;
	}

	int size; // Define amount of seats in class based on sClass.

	if(sClass == "First"){
		size = AC.getFClass();
	}
	else if(sClass == "Business"){
		size = AC.getBClass();
	}
	else if(sClass == "Premium Economy"){
		size = AC.getPEClass();
	}
	else if(sClass == "Economy"){
		size = AC.getEClass();
	}

	if(size == 0){
		cout << "\nNo seats found in " + sClass + " class.\n\n";

		return;
	}

	cout << "\n\t" + sClass + " Class Seating\n\n";
	cout << "\tA  B  C       D  E  F\n\n";
	cout << "\t";

	// Print spaces if class seating does not begin at 0.
	if(formatter != 0){
		for(int i = 0; i < formatter; i++){
			// If aisle, print row number.
			if(i == 3){
				if(rowCounter < 10){
					cout << " " << rowCounter << "   ";
				}
				else{
					cout << " " << rowCounter << "  ";
				}
			}

			// If not end of row print availability, space.
			if(i != 5){
				cout << " " << "  ";
			}
			else{
				// Print availability, newline.
				cout << " " << "\n\t";
				rowCounter++;
			}
		}
	}

	for(int i = 0; i < size; i++){
		//If aisle, print row number.
		if(formatter == 3){
			if(rowCounter < 10){
				cout << " " << rowCounter << "   ";
			}
			else{
				cout << " " << rowCounter << "  ";
			}
		}

		if(searchSeatingArray(rowCounter, formatter, results, resSize) == true){
			if(formatter != 5){
				// If not end of row print availability, space.
				cout << "X" << "  ";
			}
			else{
				// Print availability, newline.
				cout << "X" << "\n\t";
				rowCounter++;
			}
		}
		else{
			// If not end of row print availability, space.
			if (formatter != 5){
				// If not end of row print availability, space.
				cout << "A" << "  ";
			}
			else{
				// Print availability, newline.
				cout << "A" << "\n\t";
				rowCounter++;
			}
		}

		formatter++;

		// If seat count reaches 6, start new row.
		if(formatter == 6){
			formatter = 0;
		}
	}

	if(formatter > 0 && formatter <= 3){
		for(int i = formatter; i < 3; i++){
			// If aisle, print row number.
			cout << "   ";

			if(i == 2){
				if(rowCounter < 10){
					cout << " " << rowCounter << "   ";
				}
				else{
					cout << " " << rowCounter << "  ";
				}
			}
		}
	}

	delete[] results;

	return;
}

Seat BookingController::chooseSeating(Booking B, Seat &check){
	bool valid = false;
	string userClass;

	cin.ignore();

	// Seating.
	while(valid == false){
		cout << "Choose your class of seating: ";
		getline(cin, userClass);

		if(userClass == "First" || userClass == "Business" || userClass == "Premium Economy" || userClass == "Economy"){
			valid = true;
		}
		else{
			cout << "Invalid choice. Try again.\n";
		}
	}

	// Display seating details.
	Schedule S(db);
	S.getByID(B.getScheduleID());
	displaySeating(userClass, S);

	valid = false;
	string userSeat = "";
	while(valid == false){
		cout << "\n\nChoose a seat from above (e.g. 10A,3F): ";
		cin >> userSeat;

		check.setScheduleID(B.getScheduleID());
		check.setBookingID(B.getID());
		check.setSeatClass(userClass);
		check.setSeatNum(userSeat);

		if(check.checkExists() == false){
			valid = true; // Seat available.
		}
		else{
			cout << "Invalid choice. Try again.\n";
		}
	}

	cout << check << endl;

	return check;
}

FlightService BookingController::chooseServices(Booking B, FlightService& newFS){
	// Display service info.
	Schedule schedule(db);
	schedule.getByID(B.getScheduleID());

	Route scheduleRoute(db);
	scheduleRoute.getByID(schedule.getRoute());
	cout << "\t\nService Item Menu\n\n";
	ServiceItem SI(db);
	SI.displayAll(scheduleRoute.isInternational());

	bool valid = false;
	string userService = "";
	ServiceItem chk(db);

	while(valid == false){
		cout << "\n\nChoose a menu item from above (Enter 'n' for no service required).\n";
		cout << "ID of service item: ";
		cin >> userService;

		if(userService == "n"){
			valid = true;
		}
		else{
			string found = chk.getByID(userService);
			cout << chk << endl;

			if(found == "FOUND"){
				valid = true; // ServiceItem exists available.
			}
			else{
				cout << "Invalid choice. Try again.\n";
			}
		}
	}

	int userChoice = 0;

	// If user has req service items, ask how many.
	if(chk.getID() != -1){
		valid = false;

		string userAmt = "";

		while(valid == false){
			cout << "Amount of service item: ";
			cin >> userAmt;
			userChoice = atoi(userAmt.c_str());

			if(userChoice > 0){
				valid = true; // ServiceItem exists available.
			}
			else{
				cout << "Must be greater than 0. Try again.\n";
			}
		}
	}

	// Set new FS IDs.
	newFS.setScheduleID(schedule.getID());
	newFS.setServiceItemID(chk.getID());
	newFS.setAmount(userChoice);
	newFS.setBookingID(B.getMRE() + 1);
	
	return newFS;
}

int BookingController::makeBooking(string user_type, string username){
    ClearScreen cl;
	cout << "\n\t\tCreate New Booking\n\n";

	SearchController SC(db); 
	int chosenScheduleID = -1;
	FlightService flightService(db);
	Seat seat(db);
	Schedule schedule(db);
	Airport depart(db);
	Airport arrive(db);
	Route bookingR(db);

	Booking B(db);
	B.setCustEmail(username);

	if(user_type == "TRAVELAGENT"){
        std::string email;
		B.setTravelAgent(username); // Must change to refelect user.
        cout << "Enter email of customer: ";
        cin >> email;
        B.setCustEmail(email);
	}
	else{
		B.setTravelAgent("");
	}

	bool search = false;
	bool seating = false;
	bool services = false;
	bool confirm = false;

	while(confirm == false){
		// Search loop
		while(search == false){
			// Let user choose a flight to travel on.
			chosenScheduleID = SC.search(user_type, username);
			schedule.getByID(chosenScheduleID);
			B.setScheduleID(chosenScheduleID);
			search = true;
		}

		while(seating == false){
			// Do seating selection.
			chooseSeating(B,seat);
			cout << seat << endl;
			seating = true;
		}

		while(services == false){
			// Do service selection.
			chooseServices(B,flightService);
			services = true;
		}

		bookingR.getByID(schedule.getRoute());
		depart.getByIata(bookingR.getSrc());
		arrive.getByIata(bookingR.getDest());

		cout << "Here are your current booking details:\n";
		cout << "\nBooking ID: " << B.getID() << endl;
		cout << "Flight#: " << schedule.getFlightID() << endl;
		cout << "Departure: " << depart.getName() << " " << schedule.getDepartDay() << " " << schedule.getDepart() << " " << schedule.getDepartTimezone() << endl;
		cout << "Arrival: " << arrive.getName() << " " << schedule.getArriveDay() << " " << schedule.getArrive() << " " << schedule.getArriveTimezone() << endl;

		// Get seat data for booking.
		cout << "Seat Class: " << seat.getSeatClass() << endl;
		cout << "Seat Number: " << seat.getSeatNum() << endl;

		stringstream ss;
		string sID;

		ss << flightService.getServiceItemID();

		sID = ss.str();

		if(flightService.getServiceItemID() != -1){
			ServiceItem SI(db);
			SI.getByID(sID);
			cout << "Service Item(s): " << flightService.getAmount() << " X " << SI.getItem() << endl;
		}

		if(user_type == "Travel Agent"){
			cout << "Travel Agent: " << B.getTravelAgent() << endl;
		}

		string in = "";

		cout << "\n\tConfirmation\n\n";
		cout << "1) Alter Flight.\n";
		cout << "2) Alter Seating.\n";
		cout << "3) Alter Services. \n";
		cout << "4) Confirm.\n\n";
		cout << "Your choice: ";
		cin >> in;

		cout << endl;

		if(in == "1"){
			search = false;
		}
		else if(in == "2"){
			seating = false;
		}
		else if(in == "3"){
			services = false;
		}
		else if(in == "4"){
			confirm = true;
		}
		else{
			cout << "Invalid input. Try again.\n";
		}
	}

	// Add booking to table.
	B.create(); // Create booking.

	if(flightService.getServiceItemID() != -1){
		// If user has requested service items.
		cout << "Creating...\n";

		seat.setBookingID(B.getMRE());
		seat.createSeat();
		flightService.createFlightService();
	}
    cl.clearScreen();
	return 0;
}

void BookingController::viewCustomerBookings(string email){
	Booking test(db);
	int size = 0;
	Booking *temp; // Temporary pointer for BOOKING array.
	temp = test.getByEmail(email, size);

	// Output.
	Seat seat(db);
	FlightService FS(db);
	ServiceItem SI(db);
	Schedule bookingSch(db);
	Route bookingR(db);
	Airport depart(db);
	Airport arrive(db);

	for(int i = 0; i < size; i++){
		// Output all data from booking class.
		bookingSch.getByID(temp[i].getScheduleID());
		bookingR.getByID(bookingSch.getRoute());
		depart.getByIata(bookingR.getSrc());
		arrive.getByIata(bookingR.getDest());
		
		cout << "\nBooking ID: " << temp[i].getID() << endl;
        if (temp[i].getTravelAgent() != "") {
            cout << "Travel Agent: " << temp[i].getTravelAgent() << endl;
        }
		cout << "Flight#: " << bookingSch.getFlightID() << endl;
		cout << "Departure: " << depart.getName() << " " << bookingSch.getDepartDay() << " " << bookingSch.getDepart() << " " << bookingSch.getDepartTimezone()<< endl;
		cout << "Arrival: " << arrive.getName() << " " << bookingSch.getArriveDay() << " " << bookingSch.getArrive() << " " << bookingSch.getArriveTimezone() << endl;

		// Get seat data for booking.
		seat.getByBookingID(temp[i].getID());
		cout << "Seat Class: " << seat.getSeatClass() << endl;
		cout << "Seat Number: " << seat.getSeatNum() << endl;

		// Get flightService data.
		int fsResSize = -1;
		FlightService *fsResults = FS.getByBookingID(temp[i].getID(), fsResSize);

		stringstream ss;
		string sID;

		if(fsResSize > 0){
			// This booking has service items associated.
			for(int a = 0; a < fsResSize; a++){
				ss << fsResults[a].getServiceItemID();

				sID = ss.str();

				SI.getByID(sID); // Get service item data by the serviceItemID reference.
				cout << "Service Item(s): " << fsResults[a].getAmount() << " X " << SI.getItem() << "\n";
			}
		}
	}
}

void BookingController::viewTravelAgentBookings(string name){
    Booking test(db);
    int size = 0;
    Booking *temp; // Temporary pointer for BOOKING array.
    temp = test.getTravelByEmail(name, size);
    
    // Output.
    Seat seat(db);
    FlightService FS(db);
    ServiceItem SI(db);
    Schedule bookingSch(db);
    Route bookingR(db);
    Airport depart(db);
    Airport arrive(db);
    
    for(int i = 0; i < size; i++){
        // Output all data from booking class.
        bookingSch.getByID(temp[i].getScheduleID());
        bookingR.getByID(bookingSch.getRoute());
        depart.getByIata(bookingR.getSrc());
        arrive.getByIata(bookingR.getDest());
        
        cout << "\nBooking ID: " << temp[i].getID() << endl;
        if (temp[i].getTravelAgent() != "") {
            cout << "Travel Agent: " << temp[i].getTravelAgent() << endl;
        }
        cout << "Flight#: " << bookingSch.getFlightID() << endl;
        cout << "Departure: " << depart.getName() << " " << bookingSch.getDepartDay() << " " << bookingSch.getDepart() << " " << bookingSch.getDepartTimezone()<< endl;
        cout << "Arrival: " << arrive.getName() << " " << bookingSch.getArriveDay() << " " << bookingSch.getArrive() << " " << bookingSch.getArriveTimezone() << endl;
        
        // Get seat data for booking.
        seat.getByBookingID(temp[i].getID());
        cout << "Seat Class: " << seat.getSeatClass() << endl;
        cout << "Seat Number: " << seat.getSeatNum() << endl;
        
        // Get flightService data.
        int fsResSize = -1;
        FlightService *fsResults = FS.getByBookingID(temp[i].getID(), fsResSize);
        
        stringstream ss;
        string sID;
        
        if(fsResSize > 0){
            // This booking has service items associated.
            for(int a = 0; a < fsResSize; a++){
                ss << fsResults[a].getServiceItemID();
                
                sID = ss.str();
                
                SI.getByID(sID); // Get service item data by the serviceItemID reference.
                cout << "Service Item(s): " << fsResults[a].getAmount() << " X " << SI.getItem() << "\n";
            }
        }
    }
}


