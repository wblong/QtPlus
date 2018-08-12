#-------------------------------------------------
#
# Project created by QtCreator 2018-07-14T14:23:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = psp_ui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    selfielddialog.cpp \
    tableviewpage.cpp

HEADERS  += mainwindow.h \
    selfielddialog.h \
    tableviewpage.h

FORMS += \
    selfielddialog.ui

RESOURCES += \
    res.qrc
