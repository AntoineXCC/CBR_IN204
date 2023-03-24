#include "image.h"
#include <QString>
#include <iostream>

int Image::width = 0;
int Image::height = 0;
double Image::scale = 1.25;
QStringList Image::imageFilters =  {"*.jpg", "bmp"};

void Image::setSize(int w, int h) {
    width = w;
    height = h;
}


// Pb avec le scaling width lorsque 100 % ?
QPixmap Image::resize(QPixmap image, QString ratio, QSize valRatio) {
    if (ratio==QString("Fit page")) {
        return image.scaledToHeight(height*0.98);
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
