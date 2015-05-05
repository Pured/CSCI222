#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QObject>
#include <QQuickItem>
#include <iostream>
#include <string>
using namespace std;

class Login : public QObject
{
Q_OBJECT
public:
    explicit Login (QObject* parent = 0) : QObject(parent) {}
    Q_INVOKABLE QString validateLogin(QString user, QString pass);
};

#endif // LOGIN_H
