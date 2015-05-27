
/*=============================================================
| Modified by: djm749
| Version: 1.01
| Modification: refactored makeBooking()
|==============================================================*/

#include "BookingController.h"
#include "SearchController.h"
#include "Booking.h"
#include "Customer.h"
#include "Schedule.h"
#include "Aircraft.h"
#include "Seat.h"
#include "Route.h"
#include "Airport.h"
#include "FlightService.h"
#include "ServiceItem.h"
#include <string>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include "sqlite3.h"

using namespace std;


BookingController::BookingController(sqlite3* d){
	db = d;
	userType = "USERTYPE NOT SET";
}


void BookingController::setType(std::string user_type){
	userType = user_type;

	return;
}

std::string BookingController::getType(){
	return userType;
}

bool BookingController::searchSeatingArray(int row, int let, Seat* arr,int size){
	Seat S(db); //using this for conversion function.
	for (int i = 0; i < size; i++){
		if (S.convertSeatNum(row,let) == arr[i].getSeatNum()){
			return true;
		}
	}

	return false;
}

void BookingController::displaySeating(std::string sClass,Schedule sch){

	Aircraft AC(db);
	std::stringstream convert;

	convert << sch.getPlane();
	string convPlane = convert.str();
	convert.str(string()); // Clear ss.

	//get airplane details for seat availability search
	AC.getByID(convPlane);
	
	//plane dosen't exist
	if (AC.getID() == -1){
		cout << "No data for Aircraft." << endl;
		return;
	}

	//get array of seats from DB by schedule and seat class
	Seat seating(db);
	int resSize = 0;
	Seat* results = seating.getByScheduleID(sch.getID(),sClass,resSize);

	//cout << results[0] << endl;
	
	int rowCounter = 1;
	int formatter = AC.getSClassStartPoint(sClass, rowCounter);

	//cout << formatter << endl;

	if (formatter == -1){
		cout << "Invalid class for seating display.";
		return;
	}

	int size; // define amount of seats in class based on sClass
	if (sClass == "First"){
		size = AC.getFClass();
	}
	else if (sClass == "Business"){
		size = AC.getBClass();
	}
	else if (sClass == "Premium Economy"){
		size = AC.getPEClass();
	}
	else if (sClass == "Economy"){
		size = AC.getEClass();
	}

	if (size == 0){
		cout << "\nNo seats found in " + sClass + " class.\n\n";
		return;
	}

	cout << "\n\t" + sClass + " Class Seating\n\n";

	cout << "\tA  B  C       D  E  F\n\n";

	//print spaces if class seating does not begin at 0

	cout << "\t";
	if (formatter != 0){
		for (int i = 0; i < formatter; i++){

			//if aisle, print row number
			if (i == 3){
				if (rowCounter < 10){
					cout << " " << rowCounter << "   ";
				}
				else{
					cout << " " << rowCounter << "  ";
				}

			}

			//if not end of row print availability, space.
			if (i != 5){
				cout << " " << "  ";
			}
			else{
				//print availability,newline
				cout << " " << "\n\t";
				rowCounter++;
			}
		}

	}


	for (int i = 0; i < size; i++){

		//if aisle, print row number
		if (formatter == 3){
			if (rowCounter < 10){
				cout << " " << rowCounter << "   ";
			}
			else{
				cout << " " << rowCounter << "  ";
			}

		}

		
		if (searchSeatingArray(rowCounter, formatter, results, resSize) == true){
			if (formatter != 5){
				//if not end of row print availability, space.
				cout << "X" << "  ";
			}
			else{
				//print availability,newline
				cout << "X" << "\n\t";
				rowCounter++;
			}
			
		}
		else{
			//if not end of row print availability, space.
			if (formatter != 5){
				//if not end of row print availability, space.
				cout << "A" << "  ";
			}
			else{
				//print availability,newline
				cout << "A" << "\n\t";
				rowCounter++;
			}
		}

		formatter++;

		//if seat count reaches 6, start new row.
		if (formatter == 6){
			formatter = 0;
		}


	}

	if (formatter > 0 && formatter <= 3){
		//cout << "here" << endl;
		for (int i = formatter; i < 3; i++){
			//if aisle, print row number
			cout << "   ";

			if (i == 2){
				if (rowCounter < 10){
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


Seat BookingController::chooseSeating(Booking B, Seat& check){
	bool valid = false;
	std::string userClass;
	cin.ignore();
	//seating
	while (valid == false){

		cout << "Choose your class of seating: ";
		getline(cin, userClass);

		if (userClass == "First" || userClass == "Business" || userClass == "Premium Economy" || userClass == "Economy"){
			valid = true;
		}
		else{
			cout << "Invalid choice. Try again." << endl;
		}
	}

	//display seating details.
	Schedule S(db);
	S.getByID(B.getScheduleID());
	displaySeating(userClass, S);

	valid = false;
	std::string userSeat = "";
	while (valid == false){
		cout << "\n\nChoose a seat from above (eg 10A,3F): ";
		cin >> userSeat;

		check.setScheduleID(B.getScheduleID());
		check.setBookingID(B.getID());
		check.setSeatClass(userClass);
		check.setSeatNum(userSeat);

		if (check.checkExists() == false){
			valid = true; //seat available
		}
		else{
			cout << "Invalid choice. Try again." << endl;
		}
	}
	cout << check << endl;
	return check;
}

FlightService BookingController::chooseServices(Booking B, FlightService& newFS){

	//display service info
	Schedule schedule(db);
	schedule.getByID(B.getScheduleID());

	Route scheduleRoute(db);
	scheduleRoute.getByID(schedule.getRoute());
	cout << "\t\nService Item Menu\n\n";
	ServiceItem SI(db);
	SI.displayAll(scheduleRoute.isInternational());

	bool valid = false;
	std::string userService = "";
	ServiceItem chk(db);
	while (valid == false){
		cout << "\n\nChoose a menu item from above (Enter 'n' for no service required).\n";
		cout << "ID of service item: ";
		cin >> userService;

		if (userService == "n"){
			valid = true;
		}
		else{
			int userChoice = atoi(userService.c_str());
			std::string found = chk.getByID(userChoice);
			cout << chk << endl;

			if (found == "FOUND"){
				valid = true; //ServiceItem exists available
			}
			else{
				cout << "Invalid choice. Try again." << endl;
			}
		}

	}

	//if user has req service items, ask how many
	int userChoice = 0;
	if (chk.getID() != -1){
		valid = false;

		std::string userAmt = "";
		while (valid == false){
			cout << "Amount of service item: ";
			cin >> userAmt;
			userChoice = atoi(userAmt.c_str());

			if (userChoice > 0){
				valid = true; //ServiceItem exists available
			}
			else{
				cout << "Must be greater than 0. Try again." << endl;
			}
		}
	}

	newFS.setScheduleID(schedule.getID());
	newFS.setServiceItemID(chk.getID());
	newFS.setAmount(userChoice);
	newFS.setBookingID(B.getMRE() + 1); // booking has not been committed to DB yet. will be next most recent entry.
	
	return newFS;
}

int BookingController::makeBooking(std::string user_type, std::string username){

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

	if (user_type == "TravelAgent"){
		B.setTravelAgent(username); //must change to refelect user.
	}
	else{
		B.setTravelAgent("");
	}

	bool search = false;
	bool seating = false;
	bool services = false;
	bool confirm = false;

	while (confirm == false){

		//search loop
		while (search == false){
			//let user choose a flight to travel on.
			chosenScheduleID = SC.search(user_type, username);
			schedule.getByID(chosenScheduleID);
			/*
			cout << "Your flight details: \n\n";
			
			cout << schedule << "\n\n";
			*/
			B.setScheduleID(chosenScheduleID);
			search = true;
		}

		while (seating == false){
			//do seating selection
			chooseSeating(B,seat);
			cout << seat << endl;
			seating = true;
		}

		while (services == false){
			//do service selection
			chooseServices(B,flightService);
			services = true;
			//cout << "FS" << flightService << endl;
		}

		bookingR.getByID(schedule.getRoute());
		depart.getByIata(bookingR.getSrc());
		arrive.getByIata(bookingR.getDest());
		cout << "Here are your current booking details: " << endl;
		cout << "\nBooking ID: " << B.getID() << "\n";
		cout << "Flight#: " << schedule.getFlightID() << "\n";
		cout << "Departure: " << depart.getName() << " " << schedule.getDepartDay() << " " << schedule.getDepart()
			<< " " << schedule.getDepartTimezone() << "\n";
		cout << "Arrival: " << arrive.getName() << " " << schedule.getArriveDay() << " " << schedule.getArrive()
			<< " " << schedule.getArriveTimezone() << "\n";

		//get seat data for booking
		cout << "Seat Class: " << seat.getSeatClass() << endl;
		cout << "Seat Number: " << seat.getSeatNum() << endl;

		if (flightService.getServiceItemID() != -1){
			ServiceItem SI(db);
			SI.getByID(flightService.getServiceItemID());
			cout << "Service Item(s): " << flightService.getAmount() << " X " << SI.getItem() << "\n";
		}

		if (user_type == "Travel Agent"){
			cout << "Travel Agent: " << B.getTravelAgent() << "\n";
		}
		
		std::string in = "";
		cout << "\n\tConfirmation\n\n";
		cout << "1) Alter Flight.\n";
		cout << "2) Alter Seating.\n";
		cout << "3) Alter Services. \n";
		cout << "4) Confirm.\n";
		cout << "Your choice: ";
		cin >> in;
		if (in == "1"){
			search = false;
		}
		else if (in == "2"){
			seating = false;
		}
		else if (in == "3"){
			services = false;
		}
		else if (in == "4"){
			confirm = true;
		}
		else{
			cout << "Invalid input. Try again.\n";
		}


	}

	//add booking to table
	B.create(); // create booking

	if (flightService.getServiceItemID() != -1){
		//if user has requested service items
		cout << "creating" << endl;
		seat.setBookingID(B.getMRE());
		seat.create();
		flightService.create();
	}

	return 0;
}


void BookingController::viewCustomerBookings(std::string email){
	Booking test(db);
	int size = 0;
	Booking* temp; //temporary pointer for bOOKING array
	temp = test.getByEmail(email, size);
	
	//cout << size << endl;

	//output
	Seat seat(db);
	FlightService FS(db);
	ServiceItem SI(db);
	Schedule bookingSch(db);
	Route bookingR(db);
	Airport depart(db);
	Airport arrive(db);

	for (int i = 0; i < size; i++){
		//cout << temp[i] << endl; // output all data from booking class
		bookingSch.getByID(temp[i].getScheduleID());
		bookingR.getByID(bookingSch.getRoute());
		depart.getByIata(bookingR.getSrc());
		arrive.getByIata(bookingR.getDest());
		
		cout << "\nBooking ID: " << temp[i].getID() << "\n";
		cout << "Flight#: " << bookingSch.getFlightID() << "\n";
		cout << "Departure: " << depart.getName() << " " << bookingSch.getDepartDay() << " " << bookingSch.getDepart() 
			 <<	" " << bookingSch.getDepartTimezone()<< "\n";
		cout << "Arrival: " << arrive.getName() << " " << bookingSch.getArriveDay() << " " << bookingSch.getArrive()
			<< " " << bookingSch.getArriveTimezone() << "\n";



		//get seat data for booking
		seat.getByBookingID(temp[i].getID());
		cout << "Seat Class: " << seat.getSeatClass() << endl;
		cout << "Seat Number: " << seat.getSeatNum() << endl;

		//get flightService data
		int fsResSize = -1;
		FlightService* fsResults = FS.getByBookingID(temp[i].getID(),fsResSize);


		if (fsResSize > 0){
			//this booking has service items associated
			for (int a = 0; a < fsResSize; a++){
				
				SI.getByID(fsResults[a].getServiceItemID()); // get service item data by the serviceItemID reference
				cout << "Service Item(s): " << fsResults[a].getAmount() << " X " << SI.getItem() << "\n";
			}
			
		}

	}
	
	
}
