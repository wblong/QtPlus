#-------------------------------------------------
#
# Project created by QtCreator 2018-08-11T15:20:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = customer_plugin
TEMPLATE = app


SOURCES += main.cpp\
    custom_cpu_widget.cpp \
    custom_slider_widget.cpp \
    widget.cpp

HEADERS  += \
    custom_cpu_widget.h \
    custom_slider_widget.h \
    widget.h

FORMS    +=

RESOURCES += \
    resources.qrc
