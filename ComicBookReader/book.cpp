#include "book.h"
#include "image.h"
#include <QString>
#include <QDir>
#include <ui_mainwindow.h>
#include <QPixmap>
#include <QMessageBox>
#include <iostream>

Book::Book() : QObject(), pathToDir(""),
    currPage(0), totalPage(0), ratio(QString("Fit page")),
    singleMode(true) {

}

Book::~Book() {

}

void Book::setPathToDir(QString path) {
    pathToDir = path;
    QDir dir(path);
    dir.setNameFilters(Image::imageFilters);
    foreach (QFileInfo var, dir.entryInfoList()) {
        tabPathToImage.append(var.absoluteFilePath());
        totalPage = totalPage + 1;
    }
    changeCurrImage();
    emit pageChanged(tabPathToImage[currPage]);
    emit changePageCounter(currPage, totalPage);
}

void Book::next() {
    if ((currPage<totalPage-1 && singleMode) || currPage<totalPage-2 ) {
        if (singleMode || currPage+1==totalPage-1) {
            currPage = currPage + 1;
        } else {
            currPage = currPage + 2;
        }

        changeCurrImage();
        emit pageChanged(tabPathToImage[currPage]);
        emit changePageCounter(currPage, 0);

    } else {
        emit infoMsgBox("Last page");
    }
}

void Book::previous() {
    if (currPage>0) {
        if (singleMode || currPage-1==0) {
            currPage = currPage - 1;
        } else {
            currPage = currPage - 2;
        }
        changeCurrImage();
        emit pageChanged(tabPathToImage[currPage]);
        emit changePageCounter(currPage, 0);
    } else {
        emit infoMsgBox("First page");
    }
}


void Book::first() {
    currPage=0;
    changeCurrImage();
    emit pageChanged(tabPathToImage[currPage]);
    emit changePageCounter(currPage, 0);
}

void Book::last() {
    currPage=totalPage-1;
    changeCurrImage();
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

void Book::setSingleMode(bool val) {
    singleMode = val;
    changeCurrImage();
    emit pageChanged(tabPathToImage[currPage]);
    emit changePageCounter(currPage, 0);
}

void Book::changeCurrImage() {
    if (singleMode || currPage==totalPage-1) {
        currImage = QPixmap(tabPathToImage[currPage]);
    } else {
        currImage = Image::combine(QPixmap(tabPathToImage[currPage]), tabPathToImage[currPage+1] );
    }
}

QPixmap Book::getCurrImage() {
    return currImage;
}
