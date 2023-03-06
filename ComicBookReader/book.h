#ifndef BOOK_H
#define BOOK_H

#include <QObject>
#include <QString>
#include <QVector>

class Book : public QObject
{
    Q_OBJECT
private:
    // Path to the dir with all the images
    QString pathToDir;
    QVector<QString> tabPathToImage;
    int currPage;
    int totalPage;
    static QStringList imageFilters;

public:
    Book();
    ~Book();

    // Set the path to the dir with all the images and create the tab with all the path
    void setPathToDir (QString path);

    // Initalise the comic book
    void initialise();

    void next();
    void previous();
    void last();
    void first();

signals:
    void pageChanged(QString path, QString pageText);
    void infoMsgBox(QString msg);


public slots:
};

#endif // BOOK_H
