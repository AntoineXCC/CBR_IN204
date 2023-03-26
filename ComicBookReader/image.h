#ifndef IMAGE_H
#define IMAGE_H

#include <QString>
#include <QPixmap>

class Image
{
private:
    // Width of the screen
    static int width;
    // Height of the screen
    static int height;
    // Scale factor when resizing
    static double scale;

public:
    // Filters for accepted image extensions
    static QStringList imageFilters;
    // Set width and height
    static void setSize(int w, int h);

    // Resize an image according to the current zoom performed
    static QPixmap resize(QPixmap image, QString ratio, QSize valRatio);
    static QPixmap zoomIn(QPixmap image, QSize valRatio);
    static QPixmap zoomOut(QPixmap image, QSize valRatio);

    static QPixmap combine(QPixmap image1, QPixmap image2);
};

#endif // IMAGE_H
