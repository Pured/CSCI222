
/*=============================================================
| Modified by: djm749
| Version: 1.00
| Modification: created
|==============================================================*/

#include "BookingController.h"
#include "Booking.h"
#include "Customer.h"
#include "Schedule.h"
#include "Aircraft.h"
#include "Seat.h"
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

	//cout << "S" << size << endl;
	//cout << formatter << endl;
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




		/*
		//if not end of row print availability, space.
		if (formatter != 5){

			if (searchSeatingArray(rowCounter, formatter,results,resSize) == true){
				cout << "X" << "  ";
			}
			else{
				cout << "A" << "  ";
			}
			
		}
		else{
			//print availability,newline
			cout << "A" << "\n\t";
			rowCounter++;
		}
		*/

		formatter++;

		//if seat count reaches 6, start new row.
		if (formatter == 6){
			formatter = 0;
		}


	}

	//cout << formatter << endl;

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


int BookingController::makeBooking(std::string user_type, std::string username,int schID){

	cout << "\n\t\tCreate New Booking\n\n";

	cout << "Your flight details: \n\n";
	Booking B(db);

	Schedule schedule(db);
	schedule.getByID(schID);
	cout << schedule << "\n\n";



	bool valid = false;
	std::string userClass;
	//seating
	while (valid == false){
		
		cout << "Choose your class of seating: ";
		cin >> userClass;

		if (userClass == "First" || userClass == "Business" || userClass == "Premium Economy" || userClass == "Economy"){
			valid = true;
		}
		else{
			cout << "Invalid choice. Try again." << endl;
		}
	}

	displaySeating(userClass, schedule);

	valid = false;
	std::string userSeat = "";
	Seat check(db);
	while (valid == false){
		cout << "\n\nChoose a seat from above (eg 10A,3F): ";
		cin >> userSeat;
		check.setScheduleID(schID);
		check.setSeatClass(userClass);
		check.setSeatNum(userSeat);

		if (check.checkExists() == false){
			valid = true; //seat available
		}
		else{
			cout << "Invalid choice. Try again." << endl;
		}
	}

	


	//service info

	//allow change details

	return 0;
}


