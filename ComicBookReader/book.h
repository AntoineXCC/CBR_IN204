#ifndef BOOK_H
#define BOOK_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QPixmap>
#include <QFileDialog>

class Book : public QObject
{
    Q_OBJECT
private:
    // Path to the dir with all the images
    QString pathToDir;
    // Vector of each image's path
    QVector<QString> tabPathToImage;
    // Currently performed zoom on the book : can be "Custom", "Fit page" (eq. to fit height) or "Fit width"
    QString ratio;
    // Current page of the book
    int currPage;
    // Number of pages
    int totalPage;
    // One or two pages shown on the screen
    bool singleMode;
    // Only used in double page mode -> CoverPage mode (show only the first page if true otherwise show 2 pages)
    bool coverPageMode;
    // Current image on screen with no transformation (no zoom, ...)
    QPixmap currImage;

public:
    Book();
    ~Book();

    // Set the path to the dir with all the images and create the tab with all the path
    void setPathToDir (QString path);
    // Set the performed zoom
    void setRatio(QString r);
    // Set the page mode
    void setSingleMode(bool val);
    // Set if cover page mode
    void setCoverPageMode(bool val);
    // Set current page
    void setCurrPage(int val);
    // Update the current image according to the different parameters (current page, singleMode, coverPageMode, ...)
    void changeCurrImage();

    // Go to next page if possible
    void next();
    // Go to previous page if possible
    void previous();
    // Go to last page
    void last();
    // Go to first page
    void first();

    // Return the performed zoom
    QString getRatio();
    // Return number of pages of the Comic Book
    int getTotalPage();
    // Return current page number
    int getCurrPage();
    // Return current image shown on screen
    QPixmap getCurrImage();
    // Return fileInfoList of the pages in l, used to create an archive of the selected images
    QFileInfoList* getFileInfoList(QList<int> l);


signals:
    // Changing the image displayed on the screen, boolean tells if page number changed
    void pageChanged(bool numPageChanged);
    // Error/information msg
    void infoMsgBox(QString msg);


public slots:
};

#endif // BOOK_H
