/*=============================================================
| Modified by: kb100
| Version: 1.03
| Modification: Modified the Other functions.
|==============================================================*/

#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include "sqlite3.h"

class Customer{
private:
	sqlite3 *db;

	int ID;
	long long int cardNum, freqFlierPts;
	std::string title, fName, lName, gender, dob, phone, email, address, state, city, country, cardType, passport, nofly, agent, password;

public:
	// Constructors.
	Customer(sqlite3 *);

	// Get functions.
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

	// Set functions.
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

	// Other functions.
    friend std::ostream &operator<<(std::ostream &output, Customer &S);
	int createCustomer();
	int updateCustomer(); // Updates details in this instance to the database.
	int deleteCustomer();
};

#endif // CUSTOMER_H_
