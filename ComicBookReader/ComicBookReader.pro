#-------------------------------------------------
#
# Project created by QtCreator 2023-02-27T03:55:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ComicBookReader
TEMPLATE = app

LIBS += -larchive

SOURCES += main.cpp\
    mainwindow.cpp \
    book.cpp \
    image.cpp \
    archiveManager.cpp

HEADERS  += mainwindow.h \
    book.h \
    image.h \
    archiveManager.h

FORMS    += mainwindow.ui
