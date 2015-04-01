/*=============================================================
| Modified by: kb100
| Version: 1.00
| Description: Everything to do with the interface.
|==============================================================*/

#include <iostream>
#include <iomanip>
#include "userInterface.h"

using namespace std;

int mainMenu()
{
	int input = -1;

	cout << setfill('-') << setw(40) << "-\n";
	cout << "Main menu:\n";
	cout << "1) Register a new account.\n";
	cout << "2) Sign in with an existing account.\n";
	cout << "3) View all flights.\n";
	cout << "4) Find a specific flight.\n";
	cout << "0) Exit.\n\n";

	cout << "Please input your choice: ";
	cin >> input;

	cout << endl; //spacing

	switch(input)
	{
		case 0: return 0; //go back to main.cpp

		case 1: //call a function/menu
			break;

		case 2: //call a function/menu
			break;

		case 3: //call a function/menu
			break;

		case 4: //call a function/menu
			break;
	}

	//other functions/menus

	return 0;
}
