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

public:
    // Filters for accepted image extensions
    static QStringList imageFilters;
    // Set width and height
    static void setSize(int w, int h);

    // Resize an image according to the current zoom performed
    static QPixmap resize(QPixmap image, QString ratio);
};

#endif // IMAGE_H
