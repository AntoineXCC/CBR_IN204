#-------------------------------------------------
#
# Project created by QtCreator 2023-02-27T03:55:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ComicBookReader
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    book.cpp

HEADERS  += mainwindow.h \
    book.h

FORMS    += mainwindow.ui
