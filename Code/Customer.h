//
//  Customer.h
//  FlightSystem
//
//  Created by Darryl Murphy on 5/04/15.
//

#ifndef ___FlightSystem__Customer__
#define ___FlightSystem__Customer__

#include <iostream>
#include "sqlite3.h"

class Customer{
private:
	sqlite3* db;
    int ID;
    std::string title;
    std::string fName;
    std::string lName;
    std::string gender;
    std::string dob;
    std::string phone;
    std::string email;
    std::string address;
    std::string state;
	std::string city;
    std::string country;
    std::string cardType;
	long long int cardNum;
    long long int freqFlierPts;
    std::string passport;
    std::string nofly;
    std::string agent;
	std::string password;
    
public:
    //constructors
    Customer(sqlite3*);
	
	
    //get functions;
    int getID() const;
	std::string getTitle() const;
    std::string getFName() const;
    std::string getLName() const;
    std::string getGender() const;
    std::string getDOB();
    std::string getPhone() const;
    std::string getEmail() const;
    std::string getAddress() const;
    std::string getState() const;
	std::string getCity() const;
    std::string getCountry() const;
    std::string getCardType() const;
	long long int getCardNum() const;
    long long int getFreqPts() const;
    std::string getPassport() const;
    std::string getNoFly() const;
    std::string getAgent() const;
	std::string getPassword() const;
    
    //set functions
    void setID(int);
	void setTitle(std::string);
    void setFName(std::string);
    void setLName(std::string);
    void setGender(std::string);
    void setDOB(std::string);
    void setPhone(std::string);
    void setEmail(std::string);
    void setAddress(std::string);
    void setState(std::string);
	void setCity(std::string);
    void setCountry(std::string);
    void setCardType(std::string);
	void setCardNum(long long int);
    void setFreqPts(long long int);
    void setPassport(std::string);
    void setNoFly(std::string);
    void setAgent(std::string);
	void setPassword(std::string);
	std::string getByEmail(std::string);

    //other functions
    friend std::ostream &operator<<( std::ostream &output, Customer &S);
	int update(); // updates details in this instance to the database
	int deleteCust();
	int createCust();
};

#endif /* defined(___FlightSystem__Customer__) */
