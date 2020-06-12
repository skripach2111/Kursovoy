QT       += core gui
QT       += core sql
#QT       += axcontainer
QT       += printsupport
#QT       += webkitwidgets

TARGET = word
TEMPLATE = app

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminmain.cpp \
    database.cpp \
    databasebuffer.cpp \
    databaseselectiondialog.cpp \
    dropbuttondb.cpp \
    dropmenudb.cpp \
    expertmain.cpp \
    groupbox_leapbuttons.cpp \
    informationdb_dialog.cpp \
    informationuser_dialog.cpp \
    leapbutton.cpp \
    main.cpp \
    authorization.cpp \
    adddb_dialog.cpp \
    opermain.cpp \
    usersselectiondialog.cpp

HEADERS += \
    adminmain.h \
    authorization.h \
    database.h \
    adddb_dialog.h \
    databasebuffer.h \
    databaseselectiondialog.h \
    dropbuttondb.h \
    dropmenudb.h \
    expertmain.h \
    groupbox_leapbuttons.h \
    informationdb_dialog.h \
    informationuser_dialog.h \
    leapbutton.h \
    opermain.h \
    usersselectiondialog.h

FORMS += \
    adminmain.ui \
    authorization.ui \
    adddb_dialog.ui \
    databaseselectiondialog.ui \
    dropbuttondb.ui \
    dropmenudb.ui \
    expertmain.ui \
    groupbox_leapbuttons.ui \
    informationdb_dialog.ui \
    informationuser_dialog.ui \
    leapbutton.ui \
    opermain.ui \
    usersselectiondialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH+=include
#LIBS+=C:\Windows\libmysql.lib

RESOURCES += \
    qdarkstyle/style.qrc
