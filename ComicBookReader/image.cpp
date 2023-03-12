#include "image.h"
#include <QString>
#include <iostream>

int Image::width = 0;
int Image::height = 0;

void Image::setSize(int w, int h) {
    width = w;
    height = h;
}


// A terminer le resizing
QPixmap Image::resize(QPixmap image, QString ratio) {
    int r;
    if (ratio==QString("Fit page")) {
        return image.scaledToHeight(height);
    } else if (ratio==QString("Fit width")) {
        return image.scaledToWidth(width);
    } else {
        r = (ratio.split(" ")[0].toDouble())/100.;
    }
    std::cout<<r<< width<< height<<std::endl;
    return image.scaled(r*width,r*height,Qt::KeepAspectRatio);
}
