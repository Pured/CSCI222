/*=============================================================
| Modified by: kb100
| Version: 1.00
| Description: Everything to do with the users of the system.
|==============================================================*/

class Person
{
	private:
		//variables
	public:
		virtual int dummy();
		//functions
};

//People----------------------------------------------------------------------------------------------------------------

class Customer : public Person
{
	private:
		//variables
	public:
		int dummy() {return 0;}; //overrides the abstract base class
		//functions
};

class Staff : public Person
{
	private:
		//variables
	public:
		int dummy() {return 0;}; //overrides the abstract base class
		//functions
};

//Staff-----------------------------------------------------------------------------------------------------------------

class Manager : public Staff
{
	private:
		//variables
	public:
		//functions
};

//Managers--------------------------------------------------------------------------------------------------------------

class BookingManager : virtual public Manager
{
	private:
		//variables
	public:
		//functions
};

class FlightControlManager : virtual public Manager
{
	private:
		//variables
	public:
		//functions
};

class ServicesManager : virtual public Manager
{
	private:
		//variables
	public:
		//functions
};

class ProfileManager : virtual public Manager
{
	private:
		//variables
	public:
		//functions
};

//ADMINISTRATOR=========================================================================================================

class Administrator : public BookingManager, public FlightControlManager, public ServicesManager, public ProfileManager
{
	//Administrator = God

	private:
		//variables
	public:
		//functions
};
