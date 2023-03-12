#-------------------------------------------------
#
# Project created by QtCreator 2023-02-27T03:55:55
#
#-------------------------------------------------

QT       += core gui \
            gui-private

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ComicBookReader
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        book.cpp \
        archive.cpp \

HEADERS  += mainwindow.h \
        book.h \
        archive.h \

FORMS    += mainwindow.ui
