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
int copy_data(struct archive *ar, struct archive *aw);

#endif // ARCHIVE_H
