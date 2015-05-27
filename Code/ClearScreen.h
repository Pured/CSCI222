//
//  ClearScreen.h
//  
//
//  Created by csci321ga1a on 27/05/2015.
//
//

#ifndef _ClearScreen_h
#define _ClearScreen_h

#ifdef __linux__
void clearScreen(){
    system("clear");
}
#endif
#ifdef _WIN32
void clearScreen(){
    system("cls");
}
#endif
#ifdef __APPLE__
void clearScreen(){
    system("clear");
}
#endif

#endif
