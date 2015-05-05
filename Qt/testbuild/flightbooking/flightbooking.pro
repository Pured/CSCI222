TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    admin.cpp \
    database.cpp \
    login.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES += \
    bckgrnd.jpg \
    back.png \
    username.txt \
    login.txt \
    files/login.txt \
    files/username.txt \
    users.txt \
    images/radar.jpg

HEADERS += \
    admin.h \
    resourcepath.h \
    database.h \
    login.h
