//
//  Route.cpp
//  222test
//
//  Created by Darryl Murphy on 5/04/15.
//  Copyright (c) 2015 Darryl Murphy. All rights reserved.
//

#include "Route.h"

//Constructors

Route::Route(){
    ID = 0;
    srcAirport = "No Source Airport";
    destAirport = "No Destination Airport";
    codeshare = '!';
    stops = 999;
}

Route::Route(int i, std::string src, std::string dest,char cs,int s){
    ID = i;
    srcAirport = src;
    destAirport = dest;
    codeshare = cs;
    stops = s;
}


//get functions
int Route::getID() const{
    return ID;
}

std::string Route::getSrc() const{
    return srcAirport;
}

std::string Route::getDest() const{
    return destAirport;
}

char Route::getCodeshare() const{
    return codeshare;
}

int Route::getStops() const{
    return stops;
}


//set Functions
void Route::setID(int i){
    ID = i;
}

void Route::setSrc(std::string i){
    srcAirport = i;
}

void Route::setDest(std::string i){
    destAirport = i;
}

void Route::setCodeshare(char i){
    codeshare = i;
}

void Route::setStops(int i){
    stops = i;
}

std::ostream &operator<<( std::ostream &output,const Route &R){
    output<<R.getID()<<" "<<R.getSrc()<<" "<<R.getDest()<<" "<<R.getCodeshare()<<" "<<R.getStops()<<std::endl;
    return output;
}