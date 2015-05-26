#include "weatherController.h"

//http library
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/Exception.h>
#include <iostream>
#include <string>
#include <sstream>

//xml file output
#include <fstream>

//xml processing
#include "tinystr.h"
#include "tinyxml.h"

using namespace Poco::Net;
using namespace Poco;
using namespace std;



WeatherController::WeatherController(sqlite3* d)
{
	db = d;
	weatherQuery = "http://api.worldweatheronline.com/free/v2/weather.ashx?key=715c0aed8f53c39b20a552360e497&q=";
	lat = 0;
	lon = 0;
	numDays = 1;

}

void WeatherController::setWQuery(){

	std::stringstream convert;

	convert << lat;
	string convLat = convert.str();
	convert.str(string()); // Clear ss.

	convert << lon;
	string convLon = convert.str();
	convert.str(string()); // Clear ss.

	convert << numDays;
	string convNumDays = convert.str();
	convert.str(string()); // Clear ss

	weatherQuery = weatherQuery + convLat + "," + convLon + "&num_of_days=" + convNumDays + "&tp=3&format=xml";
}

void WeatherController::setLat(float l){
	lat = l;
}

void WeatherController::setLon(float l){
	lon = l;
}

void WeatherController::setNumDays(int i){
	numDays = i;
}

int WeatherController::executeQuery(){

	setWQuery();

	//cout << weatherQuery << endl;

	std::fstream weatherFile;
	weatherFile.open("weather.xml", std::fstream::out);

	try
	{

						/* WEATHER QUERY*/
		// prepare session
		URI uri(weatherQuery);
		HTTPClientSession session(uri.getHost(), uri.getPort());

		// prepare path
		string path(uri.getPathAndQuery());
		if (path.empty()) path = "/";

		// send request
		HTTPRequest req(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
		session.sendRequest(req);

		// get response
		HTTPResponse res;
		//std::cout << res.getStatus() << " " << res.getReason() << std::endl;

		// print response
		istream &is = session.receiveResponse(res);
		StreamCopier::copyStream(is, weatherFile);

	}
	catch (Exception &ex)
	{
		cerr << ex.displayText() << endl;
		return -1;
	}

	weatherFile.close();

	return 0;
}

void WeatherController::displayResults(){

	//open xml file with weather results
	TiXmlDocument doc;
	if (!doc.LoadFile("weather.xml")){
		std::cout << doc.ErrorDesc() << std::endl;
	}
	else{
		//std::cout << "Successful XML read" << std::endl;
	}

	

	//check if root node is null
	TiXmlElement* root = doc.FirstChildElement();
	if (root == NULL){
		std::cout << "Failed to load file: No root element" << std::endl;
		doc.Clear();
	}
	else{
		//std::cout << "XML doc has root" << std::endl;
	}

	
	//get current conditions data
	std::cout << std::endl;

	TiXmlElement* currCon = root->FirstChildElement("current_condition");
	TiXmlElement* elem = currCon->FirstChildElement("observation_time");
	std::string temp = elem->GetText();
	std::cout << "Observation Time: " << temp << std::endl;

	elem = currCon->FirstChildElement("temp_C");
	temp = elem->GetText();
	std::cout << "Tempreture: " << temp << " deg celcius." << std::endl;

	elem = currCon->FirstChildElement("weatherDesc");
	temp = elem->GetText();
	std::cout << "Whether Description: " << temp << std::endl;

	elem = currCon->FirstChildElement("windspeedKmph");
	temp = elem->GetText();
	std::cout << "Wind Speed: " << temp << "km/h." << std::endl;

	elem = currCon->FirstChildElement("winddir16Point");
	temp = elem->GetText();
	std::cout << "Wind Direction: " << temp << std::endl;

	elem = currCon->FirstChildElement("precipMM");
	temp = elem->GetText();
	std::cout << "Precipitation: " << temp << "mm" << std::endl;

	elem = currCon->FirstChildElement("humidity");
	temp = elem->GetText();
	std::cout << "Humidity: " << temp << std::endl;

	elem = currCon->FirstChildElement("visibility");
	temp = elem->GetText();
	std::cout << "Visibility: " << temp << std::endl;

	elem = currCon->FirstChildElement("pressure");
	temp = elem->GetText();
	std::cout << "Air Pressure: " << temp << std::endl;

	elem = currCon->FirstChildElement("cloudcover");
	temp = elem->GetText();
	std::cout << "Cloud Cover: " << temp << std::endl;

}

int WeatherController::getAirportWeather(Airport a){

	cout << a.getName() << " \tAirport\n";

	setLat(a.getLat());
	setLon(a.getLong());

	executeQuery();
	displayResults();

	return 0;
}

std::string* WeatherController::getAllAirportIATA(int& resSize){

	string sqlCreate = "SELECT COUNT(ID) FROM AIRPORT;";
	const char *sql = sqlCreate.c_str();

	sqlite3_stmt *stmt;
	int err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	int querySize = 0; //temp int to store amt results

	//exec count query
	if (err != SQLITE_OK) {
		std::cout << "SELECT failed: " << sqlite3_errmsg(db) << std::endl;
	}
	else{
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			querySize = sqlite3_column_int(stmt, 0);
		}
	}

	resSize = querySize;//assign referenced variable the size of dynamic array.
	sqlite3_finalize(stmt);

	std::string* temp = new string[resSize];

	sqlCreate = "SELECT IATA FROM AIRPORT;";
	sql = sqlCreate.c_str();

	err = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	const char * IATA;
	int i = 0;
	if (err != SQLITE_OK){
		cout << "SELECT failed: " << sqlite3_errmsg(db) << endl;
	}
	else{
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			IATA = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
			if (IATA != NULL){
				temp[i] = IATA;
			}
			i++;
		}
	}

	sqlite3_finalize(stmt);

	return temp;
}

int WeatherController::checkDanger(){
	
	//open xml file with weather results
	TiXmlDocument doc;
	if (!doc.LoadFile("weather.xml")){
		std::cout << doc.ErrorDesc() << std::endl;
	}
	else{
		//std::cout << "Successful XML read" << std::endl;
	}


	//check if root node is null
	TiXmlElement* root = doc.FirstChildElement();
	std::string nodeType = root->Value();
	if (root == NULL){
		std::cout << "Failed to load file: No root element" << std::endl;
		doc.Clear();
	}
	else if(nodeType == "html" ){
		cout << root->Value() << endl;
		cout << "Server error" << endl;
	}
	else{

		cout << root->Value() << endl;
		TiXmlElement* currCon = root->FirstChildElement("current_condition");

		TiXmlElement* elem = currCon->FirstChildElement("weatherCode");

		std::string temp = elem->GetText();
		std::cout << temp << std::endl;
	}


	
	return 0;
}

int WeatherController::searchDanger(){

	int amtRes = -1;
	std::string* results;
	results = getAllAirportIATA(amtRes);

	if (results != NULL){
		Airport temp(db);
		for (int i = 0; i < amtRes; i++){
			temp.getByIata(results[i]); //get airport data from DB
			
			//set co-ordinates for search
			cout << temp.getLat() << " " << temp.getLong() << endl;
			setLat(temp.getLat());
			setLon(temp.getLong());
			setWQuery();
			
			//execute
			executeQuery();
			
			//check if dangerous conditions
			checkDanger();
			

		}
	}



	delete[] results;

	return 0;
}




