#ifndef IMAGES_H
#define IMAGES_H

#include <QString>
#include <QImage>
#include <vector>
#include "data_types.h"

class Images : public QImage
{
public:
    Images(std::vector< DecartCoordinates > & image, int width , int height);
    bool saveImage(std::string & path);
};

#endif // IMAGES_H
