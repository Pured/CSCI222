//
//  test.cpp
//  
//
//  Created by Ali Sayed on 25/05/2015.
//
//

#include <iostream>
#include <string>
#include <curses.h>
using namespace std;


string getpass(const char *prompt)
{
    printw(prompt);
    noecho();  // disable character echoing
    
    char buff[64];
    getnstr(buff,sizeof(buff));
    
    echo(); // enable character echoing again
    return buff;
}

int main()
{
    const string correct_password="ali";
    
    initscr(); // enable ncurses
    
    string pwd=getpass("Please enter the password: ");
    
    if(correct_password==pwd)
        cout << "\nCorrect password!" << endl;
    else
        cout << "\nIncorrect password. Try again" << endl;
    
    cout << "HELLO!!" << endl;
    
    endwin(); // disable ncurses
    
    return 0;
}