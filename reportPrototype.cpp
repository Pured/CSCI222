#include <iostream> 
#include <string> 

using namespace std;

void passenger();	//passenger's report for the day, including occupancy rate
void cashier();		//cashier report like total revenue for the day, week, month
void booking(); 	//daily booking activity summary, monthly
void service();		//report the services required for a certain flight
void showMenu(); 

int main()
{

char answer = 'a'; 

cout << "Reporting Subsystem" << endl;

showMenu();


while(answer != 'e')
{
	cin >> answer;
	switch(answer)
	{
		case 'p': passenger();
		break;
		case 'c': cashier();
		break;
		case 'b': booking();
		break;
		case 's': service();
		break;
		case 'm': showMenu();
		break;
		case 'e': return(1);
		break;
		default: cout << "Please select 'p' for Passenger, 'c' for Cashier, 'b' for Booking, 'e' to exit, 'm' to view the menu again." << endl;
	}
}

return 0;
}


void showMenu()
{
	cout << "Which report do you want to generate?" << endl;
	cout << "'p' for Passenger's Report" << endl;
	cout << "'c' for Cashier's Report" << endl;
	cout << "'b' for Booking Report" << endl;
	cout << "'s' for Service Report" << endl;
	cout << "'e' to exit the reporting system" << endl;
	cout << "'m' to show menu again" << endl;
}

void passenger()
{
	cout << " -------- PASSENGER REPORT --------" << endl;
	string flightNum;	
	
	//add different types of passenger reports. 
	//favourite flights, favourite destination, other interesting data
}

void booking()
{

	//add in other interesting data, such as most popular and least popular booking made (month, day)

	cout << " -------- BOOKING REPORT --------" << endl;
	cout << "Monthly Booking Summary" << endl;
	cout << "\t- total bookings made: 632\n\t- total bookings cancelled: 15" << endl;

	cout << "Daily Booking Summary" << endl;
	cout << "\t- total bookings made: 85\n\t- total bookings cancelled: 5" << endl;
}

void cashier()
{
  //add more 'interesting data'
	cout << " -------- CASHIER REPORT --------" << endl;
	cout << "Total revenue for\n\tToday, Wednesday 1st April 2015: $56,252.50" << endl;
	cout << "\tPast 7 days: $403,875.05" << endl;
}

void service()
{
	//add data such as how much profit was made on the services sales
  //add more 'interesting data'
  
	cout << " -------- SERVICES REPORT --------" << endl;
	string flightNum;	
	
	cout << "For what flight would you like to generate a service report?" << endl;
	cout << "Flight Number: ";
	cin >> flightNum; 

	cout << "Service report for " << flightNum << endl;
	cout << "Stock required: " << endl;
	cout << "\t- 132 bottles of water\n\t- 105 cans of soda\n\t- 52 bottles of beer\n\t- 30 bottles of orange juice" << endl;
	cout << "\t- 90 sandwhiches\n\t- 50 soups\n\t- 30 apples\n\t- 12 pastas" << endl;
	cout << "\t- 90 sandwhiches\n\t- 50 soups\n\t- 30 apples\n\t- 12 pastas" << endl;
}

