
CREATE TABLE AIRPORT(
	id		NUMBER(4)	NOT NULL,
	name 		VARCHAR(50)	NOT NULL,
	city		VARCHAR(50)	NOT NULL,
	country		VARCHAR(50)	NOT NULL,
	iata		VARCHAR(3)	NOT NULL,
	latitude	DECIMAL(10,6)	NOT NULL,
	longitude	DECIMAL(10,6)	NOT NULL,
	altitude	NUMBER(5)	NOT NULL,
	timezone	NUMBER(2)	NOT NULL,
	DST		CHAR(1)		NOT NULL,
	tz		VARCHAR(50)	NOT NULL,
	CONSTRAINT AIRPORT_pkey PRIMARY KEY (id),
	CONSTRAINT airport_iata UNIQUE (iata),
	CONSTRAINT alt_check CHECK (altitude >= 0)
);


CREATE TABLE ROUTE(
	id		NUMBER(4)	NOT NULL,
	src		VARCHAR(3)	NOT NULL,
	dest		VARCHAR(3)	NOT NULL,
	codeshare	CHAR(1)		NULL,
	stops		NUMBER(2)	NOT NULL,
	CONSTRAINT ROUTE_pkey PRIMARY KEY (id),
	CONSTRAINT ROUTE_fkey1 FOREIGN KEY (src)
		REFERENCES AIRPORT(iata),
	CONSTRAINT ROUTE_fkey2 FOREIGN KEY (dest)
		REFERENCES AIRPORT(iata),
	CONSTRAINT codeshare_check CHECK ( codeshare = 'y' OR codeshare = NULL )
);

CREATE TABLE AIRCRAFT(
	id		NUMBER(3)	NOT NULL,
	name		VARCHAR(30)	NOT NULL,
	inService	NUMBER(3) 	NOT NULL,
	fClass		NUMBER(3)	NOT NULL,
	bClass		NUMBER(3)	NOT NULL,
	peClass		NUMBER(3)	NOT NULL,
	eClass		NUMBER(3)	NOT NULL,
	total		NUMBER(3)	NOT NULL,
	CONSTRAINT AIRCRAFT_pkey PRIMARY KEY (id),
	CONSTRAINT inService_check CHECK (inService >= 0),
	CONSTRAINT fClass_check CHECK (fClass >= 0),
	CONSTRAINT bClass_check CHECK (bClass >= 0),
	CONSTRAINT peClass_check CHECK (peClass >= 0),
	CONSTRAINT eClass_check CHECK (eClass >= 0)
);


CREATE TABLE SCHEDULE(
	id					NUMBER(4)	NOT NULL,
	flightID			VARCHAR(6)	NOT NULL,
	plane			NUMBER(3)	NOT NULL,
	route				NUMBER(4)	NOT NULL,
	deptDay 		VARCHAR(3) NOT NULL,
	departDate	DATETIME	NOT NULL,
	deptTimezone VARCHAR(5) NOT NULL,
	arrDay 			VARCHAR(3) NOT NULL,
	arriveDate 		DATE	NOT NULL,
	arrTimezone VARCHAR(5) NOT NULL,
	CONSTRAINT SCHEDULE_pkey PRIMARY KEY (id),
	CONSTRAINT SCHEDULE_fkey1 FOREIGN KEY (plane)
		REFERENCES AIRCRAFT(id),
	CONSTRAINT SCHEDULE_fkey2 FOREIGN KEY (route)
		REFERENCES ROUTE(id)
);

CREATE TABLE BOOKING(
	id					NUMBER(4) 		NOT NULL,
	custEmail 	VARCHAR(50)	NOT NULL,
	scheduleID 	NUMBER(4)		NOT NULL,
	seatClass		VARCHAR(10)	NOT NULL,
	travelAgent 	VARCHAR(50)	NULL,
	CONSTRAINT BOOKING_pkey PRIMARY KEY (id),
	CONSTRAINT BOOKING_fkey1 FOREIGN KEY (custEmail)
		REFERENCES CUSTOMER (email),
	CONSTRAINT BOOKING_fkey2 FOREIGN KEY (scheduleID)
		REFERENCES SCHEDULE (id),
	CONSTRAINT BOOKING_fkey3 FOREIGN KEY (travelAgent)
		REFERENCES TRAVELAGENT (name)
);


CREATE TABLE TRAVELAGENT(
	id	NUMBER(3)	NOT NULL,
	name	VARCHAR(50)	NULL,
	phone	VARCHAR(20)	NOT NULL,
	email	VARCHAR(50)	NOT NULL,
	CONSTRAINT TRAVELAGENT_pkey PRIMARY KEY (email),
	CONSTRAINT agent_name UNIQUE (name)
);


CREATE TABLE CUSTOMER (
	id		NUMBER(4)	NOT NULL,
	title		VARCHAR(10)	NOT NULL,
	fName		VARCHAR(20)	NOT NULL,
	lName		VARCHAR(30)	NOT NULL,
	gender		VARCHAR(6)	NOT NULL,
	DOB		DATE	NOT NULL,
	phone		VARCHAR(20)	NOT NULL,
	email		VARCHAR(50)	NOT NULL,
	address		VARCHAR(50)	NOT NULL,
	state		VARCHAR(50)	NULL,
	city		VARCHAR(50)	NOT NULL,
	country		VARCHAR(40)	NOT NULL,
	credCard		VARCHAR(30)	NULL,
	cardNum		NUMBER(30)	NULL,
	freqFly		NUMBER(10)	NULL,
	passport 	VARCHAR(5)	NOT NULL,
	status		VARCHAR(10)	NULL,
	travelAgent	VARCHAR(50)	NULL,
	CONSTRAINT CUSTOMER_pkey PRIMARY KEY (id),
	CONSTRAINT CUSTOMER_fkey1 FOREIGN KEY (travelAgent)
		REFERENCES TRAVELAGENT(name),
	CONSTRAINT freqFly_check CHECK (freqFly >= 0),
	CONSTRAINT passport_check CHECK (passport = 'TRUE' OR passport = 'FALSE'),
	CONSTRAINT status_check CHECK ( status = NULL OR status = 'watch' OR status = 'no fly')		
);


CREATE TABLE SERVICEITEM (
	id		NUMBER(3)	NOT NULL,
	item		VARCHAR(30)	NOT NULL,
	cost		DECIMAL(5,2)	NOT NULL,
	availability	VARCHAR(15) 	NOT NULL,
	CONSTRAINT SERVICEITEM_pkey PRIMARY KEY (id),
	CONSTRAINT cost_check CHECK (cost >= 0),
	CONSTRAINT availability_check CHECK (availability = 'all' OR availability = 'intenational')
);



CREATE TABLE FLIGHT(
	id		NUMBER(3)	NOT NULL,
	currFCap	NUMBER(3)	NOT NULL,
	currBCap	NUMBER(3)	NOT NULL,
	currPECap	NUMBER(3)	NOT NULL,
	currECap	NUMBER(3)	NOT NULL,
	CONSTRAINT FLIGHT_pkey PRIMARY KEY (id),
	CONSTRAINT FLIGHT_fkey1 FOREIGN KEY (id)
		REFERENCES SCHEDULE(id),
	CONSTRAINT fCap_check CHECK (currFCap >= 0),
	CONSTRAINT bCap_check CHECK (currBCap >= 0),
	CONSTRAINT peCap_check CHECK (currPECap >= 0),
	CONSTRAINT eCap_check CHECK (currECap >= 0)
);

CREATE TABLE FLIGHTSERVICE(
	id 		NUMBER(3)	NOT NULL,
	scheduleID	NUMBER(4)	NOT NULL,
	serviceItem	NUMBER(3)	NOT NULL,
	amount		NUMBER(3)	NOT NULL,
	CONSTRAINT FLIGHTSERVICE_pkey PRIMARY KEY (id),
	CONSTRAINT FLIGHTSERVICE_fkey1 FOREIGN KEY (scheduleID)
		REFERENCES SCHEDULE(id),
	CONSTRAINT amount_check CHECK (amount >= 0)
);

CREATE TABLE STAFF(
	userType	VARCHAR2(15)	NOT NULL,
	email		VARCHAR2(50)	NOT NULL,
	password	VARCHAR2(50)	NOT NULL,		
	CONSTRAINT STAFF_pkey PRIMARY KEY (email),
	CONSTRAINT userType_check CHECK (userType = 'STAFF' OR 
		userType = 'PROFILEMANAGER' OR userType = 'FLIGHTMANAGER' OR
		userType = 'SERVICEMANAGER' OR userType = 'BOOKINGMANAGER' OR
		userType = 'ADMINISTRATOR')
);

CREATE TABLE MESSAGE(
	id				 NUMBER(4) 		NOT NULL,
	userType 	 VARCHAR(15) 		NOT NULL,
	message 	 VARCHAR(200) 	NOT NULL,
	email		 VARCHAR(50) 		NULL,
	CONSTRAINT MESSAGE_pkey PRIMARY KEY (id),
	CONSTRAINT MESSAGE_fkey FOREIGN KEY (email)
		REFERENCES CUSTOMER (email),
	CONSTRAINT userType_check CHECK (userType = 'STAFF' OR 
		userType = 'PROFILEMANAGER' OR userType = 'FLIGHTMANAGER' OR
		userType = 'SERVICEMANAGER' OR userType = 'BOOKINGMANAGER' OR
		userType = 'ADMINISTRATOR')
);

-- @AP.sql
-- @AC.sql
-- @R.sql
-- @SCH.sql
-- @TA.sql
-- @SI.sql
-- @C.sql