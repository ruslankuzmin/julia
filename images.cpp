#include "images.h"

Images::Images(std::vector<DecartCoordinates> &image , int width , int height)
    : QImage(QSize(width,height),QImage::Format_RGB32)
{
    this->fill(QColor(Qt::white).rgb());
    for(auto v : image){
        this->setPixel(v.x, v.y, qRgb(0, 0, 0));
    }
}

Images::Images(ColorMap & image, int width, int height)
    : QImage(QSize(width,height),QImage::Format_RGB32)
{
    this->fill(QColor(Qt::white).rgb());
    for(auto el : image){
        for(auto coord : el.second){
             this->setPixel(coord.x, coord.y,
                            qRgb(el.first.r, el.first.g, el.first.b));
        }
    }
}

bool Images::saveImage(std::string & path)
{
    return this->save(QString::fromStdString(path));
}
