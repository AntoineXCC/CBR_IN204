#ifndef ARCHIVE_H
#define ARCHIVE_H

#include <QCoreApplication>
#include <QString>
#include <QFile>
#include <QFileDialog>


// Extract files from zipPath to path in a folder with the base name of zipPath
void Unzip(QString zipPath, QString path);
// Create an archive to zipPath with all files in fileList
void Zip(QFileInfoList fileList, QString zipPath);
// Function used in Unzip
int copy_data(struct archive *ar, struct archive *aw);

#endif // ARCHIVE_H
