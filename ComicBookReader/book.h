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
    // Vector of each image's path
    QVector<QString> tabPathToImage;
    // Currently performed zoom on the book : can be a percentage, "Fit page" (eq. to fit height) or "Fit width"
    QString ratio;
    // Current page of the book
    int currPage;
    // Number of pages
    int totalPage;


public:
    Book();
    ~Book();

    // Set the path to the dir with all the images and create the tab with all the path
    void setPathToDir (QString path);
    // Set the performed zoom
    void setRatio(QString r);

    // Initalise the comic book -> Not used
    void initialise();

    // Go to next page if possible
    void next();
    // Go to previous page if possible
    void previous();
    // Go to last page
    void last();
    // Go to first page
    void first();

    // Get the path of the current image shown
    QString getCurrImagePath();
    // Get the performed zoom
    QString getRatio();


signals:
    // Changing the page to display on the main screen
    void pageChanged(QString path);
    // Changing the page counter
    void changePageCounter(int currPage, int totalPage);


    void infoMsgBox(QString msg);


public slots:
};

#endif // BOOK_H
