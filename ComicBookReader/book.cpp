#include "book.h"
#include "image.h"
#include <QString>
#include <QDir>
#include <QPixmap>
#include <QMessageBox>

Book::Book() : QObject(), pathToDir(""),
    currPage(0), totalPage(0), ratio(QString("Fit page")),
    singleMode(true), coverPageMode(true) {
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
    emit pageChanged(true);
}

void Book::setRatio(QString r) {
    ratio = r;
}

void Book::setSingleMode(bool val) {
    singleMode = val;
    changeCurrImage();
    emit pageChanged(false);
}

void Book::setCoverPageMode(bool val) {
    setSingleMode(false);
    coverPageMode = val;
    if (coverPageMode && currPage != 0) {
        currPage = currPage - 1 + (currPage % 2);
    } else {
        currPage = currPage - (currPage % 2);
    }
    changeCurrImage();
    emit pageChanged(true);
}

void Book::setCurrPage(int val) {
    if (val>=0 && val<totalPage) {
        currPage=val;
        changeCurrImage();
        emit pageChanged(true);
    }
}

void Book::changeCurrImage() {
    if (singleMode || currPage==totalPage-1 || (!singleMode && coverPageMode && currPage==0)) {
        currImage = QPixmap(tabPathToImage[currPage]);
    } else {
        currImage = Image::combine(QPixmap(tabPathToImage[currPage]), tabPathToImage[currPage+1] );
    }
}


void Book::next() {
    if ((currPage<totalPage-1 && singleMode) || currPage<totalPage-2 ) {
        if (singleMode || currPage+1==totalPage-1 || (!singleMode && currPage==0 && coverPageMode)) {
            currPage = currPage + 1;
        } else {
            currPage = currPage + 2;
        }

        changeCurrImage();
        emit pageChanged(true);

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
        emit pageChanged(true);
    } else {
        emit infoMsgBox("First page");
    }
}

void Book::first() {
    currPage=0;
    changeCurrImage();
    emit pageChanged(true);
}

void Book::last() {
    if (singleMode) {
        currPage = totalPage - 1;
    } else if (!singleMode && coverPageMode) {
        currPage = totalPage - 1 - (totalPage % 2);
    } else {
        currPage = totalPage - 1 - ((totalPage - 1) % 2);
    }
    changeCurrImage();
    emit pageChanged(true);
}


QString Book::getRatio() {
    return ratio;
}

QPixmap Book::getCurrImage() {
    return currImage;
}

int Book::getCurrPage() {
    return currPage;
}

int Book::getTotalPage() {
    return totalPage;
}

QFileInfoList* Book::getFileInfoList(QList<int> l) {
    QFileInfoList* fileList = new QFileInfoList();
    foreach(int i, l) {
        fileList->append(QFileInfo(tabPathToImage[i-1]));
    }
    return fileList;
}
