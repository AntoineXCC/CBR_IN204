#include "image.h"
#include <QString>
#include <QPainter>

int Image::width = 0;
int Image::height = 0;
double Image::scale = 1.25;

QStringList Image::imageFilters =  {"*.bmp", "*.gif", "*.jpg", "*.jpeg", "*.png"};

void Image::setSize(int w, int h) {
    width = w;
    height = h;
}

QPixmap Image::resize(QPixmap image, QString ratio, QSize valRatio) {
    if (ratio==QString("Fit page")) {
        return image.scaledToHeight(height);
    } else if (ratio==QString("Fit width")) {
        return image.scaledToWidth(width*0.98);
    } else {
        return image.scaled(valRatio);
    }
}

QPixmap Image::zoomIn(QPixmap image, QSize valRatio) {
    return resize(image, QString("Custom"), valRatio*1.25);
}

QPixmap Image::zoomOut(QPixmap image, QSize valRatio) {
    return resize(image, QString("Custom"), valRatio/1.25);
}

QPixmap Image::combine(QPixmap image1, QPixmap image2) {
    int meanHeight = (image1.height() + image2.height())/2 + (image1.height() + image2.height()) % 2;
    image1 = image1.scaledToHeight(meanHeight);
    image2 = image2.scaledToHeight(meanHeight);
    QImage image(image1.width() + image2.width(), image1.height(), QImage::Format_ARGB32_Premultiplied);
    image.fill(QColor(Qt::transparent));

    // Paint everything in a pixmap.
    QPixmap pixmap = QPixmap::fromImage(image);
    QPainter paint(&pixmap);
    paint.drawPixmap(0, 0, image1);
    paint.drawPixmap(image1.width(), 0, image2);
    return pixmap;
}
