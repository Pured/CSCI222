#ifndef DATABASE_H
#define DATABASE_H

#include <QMainWindow>
#include <QObject>
#include <QQuickItem>
#include <iostream>

class Database : public QObject
{
Q_OBJECT
public:
    explicit Database (QObject* parent = 0) : QObject(parent) {}
    Q_INVOKABLE void getUserName();
    Q_INVOKABLE void getPassword();
};

#endif // DATABASE_H
