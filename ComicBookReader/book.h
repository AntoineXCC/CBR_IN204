#ifndef BOOK_H
#define BOOK_H

#include <QObject>
#include <QString>
#include <QVector>

class Book : public QObject
{
    Q_OBJECT
//private:
private:
    static QStringList imageFilters;

    // Path to the dir with all the images
    QString pathToDir;
    QVector<QString> tabPathToImage;
    QString ratio;
    int currPage;
    int totalPage;


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
    QString getCurrImagePath();
    QString getRatio();
    void setRatio(QString r);

signals:
    // Changing the page to display on the main screen
    void pageChanged(QString path);
    // Changing the page counter
    void changePageCounter(int currPage, int totalPage);
    void infoMsgBox(QString msg);


public slots:
};

#endif // BOOK_H
