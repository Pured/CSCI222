//
//  clearscreen.cpp
//  
//
//  Created by csci321ga1a on 2/06/2015.
//
//
#include "clearscreen.h"
#include <stdio.h>

void ClearScreen::clearScreen(){
#ifdef __linux__
    system("clear");
#endif
#ifdef WIN32
    system("cls");
#endif
#ifdef _WIN64
    system("cls");
#endif
#ifdef __APPLE__
    system("clear");
#endif
}
