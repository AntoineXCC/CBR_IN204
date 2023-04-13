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

    // Return an image resized according to the current zoom performed
    static QPixmap resize(QPixmap image, QString ratio, QSize valRatio);
    // Return an image with zoom in
    static QPixmap zoomIn(QPixmap image, QSize valRatio);
    // Return an image with zoom out
    static QPixmap zoomOut(QPixmap image, QSize valRatio);

    // Return an image where image1 is on left and image2 on right
    // The height of the image is a mean of the 2 input image
    static QPixmap combine(QPixmap image1, QPixmap image2);
};

#endif // IMAGE_H
