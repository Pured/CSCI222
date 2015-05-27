//
//  clearscreen.h
//  
//
//  Created by csci321ga1a on 27/05/2015.
//
//


#include <stdlib.h>

#ifdef __linux__
    void clearscreen(){
        system("clear");
    }
#endif
#ifdef WIN32
    void clearscreen(){
        system("cls");
    }
#endif
#ifdef __APPLE__
    void clearscreen(){
        system("clear");
    }
#endif



