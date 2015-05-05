#ifndef ADMIN_H
#define ADMIN_H

#include <QMainWindow>
#include <QObject>
#include <QQuickItem>
#include <iostream>

class Admin : public QObject
{
Q_OBJECT
public:
    explicit Admin (QObject* parent = 0) : QObject(parent) {}
    Q_INVOKABLE QString displayMessage();
private:

};

#endif // ADMIN_H
