//
//  ServiceItem.cpp
//  222test
//
//  Created by Darryl Murphy on 5/04/15.
//  Copyright (c) 2015 Darryl Murphy. All rights reserved.
//

#include "ServiceItem.h"

//constructors
ServiceItem::ServiceItem(){
    ID = 0;
    item = "No Item";
    cost = 0;
    avail = "No Availability";
}

ServiceItem::ServiceItem(int id,std::string it,float c,std::string a){
    ID = id;
    item = it;
    cost = c;
    avail = a;
}

//get functions
int ServiceItem::getID() const{
    return ID;
}

std::string ServiceItem::getItem() const{
    return item;
}

float ServiceItem::getCost() const{
    return cost;
    
}
std::string ServiceItem::getAvail() const{
    return avail;
}

//set functions
void ServiceItem::setID(int i){
    ID = i;
}
void ServiceItem::setItem(std::string i){
    item = i;
}
void ServiceItem::setCost(float i){
    cost = i;
}
void ServiceItem::setAvail(std::string i){
    avail = i;
}

//other functions
std::ostream &operator<<( std::ostream &os,const ServiceItem &S){
    os<<"Service Item ID: "<<S.getID()<<"\nItem: "<<S.getItem()<<"\nCost: "<<S.getCost()
        <<"\nAvailability: "<<S.getAvail()<<"\n";
    return os;
}