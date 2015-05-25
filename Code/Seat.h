/*=============================================================
| Modified by: kb100
| Version: 1.01
| Modification: Restyled the code.
|==============================================================*/

#ifndef SEAT_H_
#define SEAT_H_

#include "sqlite3.h"

class Seat{
private:
	sqlite3 *db;
	int ID;
	int scheduleID;
	int bookingID;
	std::string seatClass;
	std::string seatNum;

public:
	// Constructors.
	Seat(sqlite3 *d);
	Seat();

	// Get functions.
	int getID() const;
	int getScheduleID() const;
	int getBookingID() const;
	std::string getSeatClass() const;
	std::string getSeatNum() const;

	// Set functions.
	void setDB(sqlite3 *);
	void setID(int);
	void setScheduleID(int SID);
	void setBookingID(int BID);
	void setSeatClass(std::string sClass);
	void setSeatNum(std::string sNum);

	int update();
	int create();
	Seat *getByScheduleID(int sch_ID,std::string sClass,int& resSize); //search using schedule id
	std::string convertSeatNum(int row, int letter); //converts nested loop indexs (row/col) into a seatNum
	bool checkExists(); //initalise objet before use

	// Other functions.
	friend std::ostream &operator<<(std::ostream &output, const Seat &S);
};

#endif //Seat_H_
