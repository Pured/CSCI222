#include "resourcepath.h"
#include <iostream>
#include <fstream>
#include <string>
#include <QString>

using namespace std;

QString Login::validateLogin(QString user, QString pass)
{
    QString u,p,r;
    string us,pw,rl;
    ifstream fin;
    fin.open("/Users/achillez/Dropbox/CompSci/2015/CSCI222/testbuild/flightbooking/username.txt");

    // Tests if file can be opened.
    if(fin.fail()){
        return "Unable to open file!";
    }

    while(fin.peek() != EOF){
        getline(fin, us, ',');
        getline(fin,pw,',');
        getline(fin,rl,'\n');
        u = QString::fromStdString(us);
        p = QString::fromStdString(pw);
        r = QString::fromStdString(rl);
        /*
        int x = QString::compare(u,user,Qt::CaseInsensitive);
        int y = QString::compare(p,pass,Qt::CaseInsensitive);
        cout << "X: " << x << endl;
        cout << "Y: " << y << endl;
        cout << "U: " << us << " " << "P: " << pw << endl;
        */
        if((u == user) && (p == pass)){
            return r;
        }
        fin.clear();
    }
    fin.close();
    return "userCreateAccount";
}

