#include "archive.h"
#include "QtGui/private/qzipreader_p.h"
#include "QtGui/private/qzipwriter_p.h"
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <iostream>
#include <QMessageBox>

// Unzip dans le dossier spécifié
void Unzip(QString zipPath) {
    QZipReader reader(zipPath);
    QString path = QFileDialog::getExistingDirectory(0, "Choix lieu extraction", "../data");
    foreach(QZipReader::FileInfo item, reader.fileInfoList()) {
        qDebug() << path + QString("/") + item.filePath;
        QFile file(path + QString("/") + item.filePath);
        file.open(QIODevice::WriteOnly);
        file.write(reader.fileData(item.filePath));
        file.close();
    }
    reader.close();
}

// Zip uniquement pour l'instant un dossier entier (à changer pour seulement les images spécifiées)
bool Zip(QFileInfoList fileList, QString zipPath) {
    QZipWriter writer(zipPath);
    if(fileList.size()<=0){
        qDebug()<<"there is no file to zip, please check it";
        return false;
    }
    //
    for(int i=0;i != fileList.size(); i++){
        QString filePath=fileList.at(i).filePath();
        QFile file(filePath);
        QString fileName = file.fileName().section("/",-1,-1);
        qDebug()<<"fileName:"<<fileName;
        if(file.exists()){
            file.open(QIODevice::ReadOnly);
            writer.addFile(fileName, file.readAll());
            file.close();
        }
        else{
            qDebug()<<"file not exist:"<<fileName;
        }
    }
    writer.close();
}


