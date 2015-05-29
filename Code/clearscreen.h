//
//  clearscreen.h
//  
//
//  Created by Peter Mavridis on 27/05/2015.
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
#ifdef _WIN64
	void clearscreen(){
		system("cls");
	}
#endif
#ifdef __APPLE__
    void clearscreen(){
        system("clear");
    }
#endif



