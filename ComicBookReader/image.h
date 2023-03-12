#ifndef IMAGE_H
#define IMAGE_H

#include <QString>
#include <QPixmap>

class Image
{
    static int width;
    static int height;
public:
    static void setSize(int w, int h);

    static QPixmap resize(QPixmap image, QString ratio);
};

#endif // IMAGE_H
