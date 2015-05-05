#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "resourcepath.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<Admin>("com.myself", 1, 0, "Admin");
    qmlRegisterType<Login>("com.myself",1,0, "Login");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
