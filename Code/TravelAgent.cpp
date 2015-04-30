//
//  TravelAgent.cpp
//  222test
//
//  Created by Darryl Murphy on 5/04/15.
//  Copyright (c) 2015 Darryl Murphy. All rights reserved.
//

#include "TravelAgent.h"

//constructors
TravelAgent::TravelAgent(){
    ID = 0;
    name = "No Name";
    phone = "No Phone";
    email = "No Email";
}

TravelAgent::TravelAgent(int i ,std::string n,std::string p,std::string e){
    ID = i;
    name = n;
    phone = p;
    email = e;
}

//get functions
int TravelAgent::getID() const{
    return ID;
}

std::string TravelAgent::getName() const{
    return name;
}

std::string TravelAgent::getPhone() const{
    return phone;
}

std::string TravelAgent::getEmail() const{
    return email;
}

//set functions
void TravelAgent::setID(int i){
    ID = i;
}
void TravelAgent::setName(std::string i){
    name = i;
}
void TravelAgent::setPhone(std::string i){
    phone = i;
}
void TravelAgent::setEmail(std::string i){
    email = i;
}

//other functions
std::ostream &operator<<( std::ostream &os, const TravelAgent &T){
    os<<"Travel Agent ID: "<<T.getID()<<"\nName: "<<T.getName()<<"\nPhone: "<<T.getPhone()<<"\nEmail: "<<T.getEmail()<<"\n";
    return os;
}