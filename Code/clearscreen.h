//
//  clearscreen.h
//  
//
//  Created by Peter Mavridis on 27/05/2015.
//
//


#include <stdlib.h>

#ifdef __linux__
    void clearScreen(){
        system("clear");
    }
#endif
#ifdef WIN32
    void clearScreen(){
        system("cls");
    }
#endif
#ifdef _WIN64
	void clearScreen(){
		system("cls");
	}
#endif
#ifdef __APPLE__
    void clearScreen(){
        system("clear");
    }
#endif



