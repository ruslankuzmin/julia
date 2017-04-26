#ifndef IMAGES_H
#define IMAGES_H

#include <QString>
#include <QImage>
#include <vector>
#include <map>

#include "data_types.h"

/**
 * @brief Объект изображений.
 */
class Images : public QImage
{
public:
    /**
     * @brief Images Создает изображение из массива координат.
     * @param image Изображение.
     * @param width Ширина изображения.
     * @param height Высота изображения.
     */
    Images(std::vector< DecartCoordinates > & image, int width , int height);
    Images(ColorMap & image, int width , int height);
    /**
     * @brief saveImage Сохранение изображения в виде картинки.
     * @param path
     * @return
     */
    bool saveImage(std::string & path);
};

#endif // IMAGES_H
