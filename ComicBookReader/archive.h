#ifndef ARCHIVE_H
#define ARCHIVE_H

#include <QCoreApplication>
#include <QByteArray>
#include <QBitArray>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QFileDialog>


void Unzip(QString zipPath);
bool Zip(QFileInfoList fileList, QString zipPath);

#endif // ARCHIVE_H
