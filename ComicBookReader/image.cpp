#include "image.h"
#include <QString>
#include <iostream>

int Image::width = 0;
int Image::height = 0;
QStringList Image::imageFilters =  {"*.jpg", "bmp"};

void Image::setSize(int w, int h) {
    width = w;
    height = h;
}


// Pb avec le scaling width lorsque 100 % ?
QPixmap Image::resize(QPixmap image, QString ratio) {
    double r;
    if (ratio==QString("Fit page")) {
        return image.scaledToHeight(height*0.98);
    } else if (ratio==QString("Fit width")) {
        return image.scaledToWidth(width*0.98);
    } else {
        r = (ratio.split(" ")[0].toDouble())/100;
    }
    return image.scaled(image.width()*r, image.height()*r,Qt::KeepAspectRatio);
}
