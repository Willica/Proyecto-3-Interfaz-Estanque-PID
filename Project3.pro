QT += widgets \
      charts

TARGET = Project3
CONFIG += console c++11
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
           mainwindow.cpp

HEADERS += mainwindow.h \
    tanque.h

RESOURCES += resources.qrc
