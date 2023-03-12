#include "book.h"
#include <QString>
#include <QDir>
#include <ui_mainwindow.h>
#include <QPixmap>
#include <QMessageBox>
#include <iostream>

QStringList Book::imageFilters =  {"*.jpg", "bmp"};

Book::Book() : QObject(), pathToDir(""), currPage(0), totalPage(0), ratio(QString("Fit page")) {

}

Book::~Book() {

}

void Book::setPathToDir(QString path) {
    pathToDir = path;
    QDir dir(path);
    dir.setNameFilters(imageFilters);
    foreach (QFileInfo var, dir.entryInfoList()) {
        tabPathToImage.append(var.absoluteFilePath());
        totalPage = totalPage + 1;
    }
    QString pageText;
    pageText = QString::number(currPage+1) + QString("/") + QString::number(totalPage);
    emit pageChanged(tabPathToImage[currPage]);
    emit changePageCounter(currPage, totalPage);
}

void Book::initialise() {

}

void Book::next() {
    if (currPage<totalPage-1) {
        currPage = currPage + 1;
        emit pageChanged(tabPathToImage[currPage]);
        emit changePageCounter(currPage, 0);

    } else {
        emit infoMsgBox("Last page");
    }
}

void Book::previous() {
    if (currPage>0) {
        currPage = currPage - 1;
        emit pageChanged(tabPathToImage[currPage]);
        emit changePageCounter(currPage, 0);
    } else {
        emit infoMsgBox("First page");
    }
}


void Book::first() {
    currPage=0;
    emit pageChanged(tabPathToImage[currPage]);
    emit changePageCounter(currPage, 0);
}

void Book::last() {
    currPage=totalPage-1;
    emit pageChanged(tabPathToImage[currPage]);
    emit changePageCounter(currPage, 0);
}

QString Book::getCurrImagePath() {
    return tabPathToImage[currPage];
}

QString Book::getRatio() {
    return ratio;
}

void Book::setRatio(QString r) {
    ratio = r;
}
