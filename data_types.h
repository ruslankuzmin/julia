#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <vector>
#include <map>

/**
 * @brief Объект цвета.
 */
struct __attribute__((__packed__)) RGB {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    bool operator=(const RGB &o) const{
        return r == o.r && g == o.g && b == o.b;
    }
    bool operator!=(const RGB &o) const{
        return r != o.r || g != o.g || b != o.b;
    }
    bool operator<(const RGB &o) const{
        return r < o.r || (r == o.r && g < o.g) ||  (r == o.r && g == o.g && b < o.b);
    }
};

/**
 * @brief Объект координат.
 */
struct __attribute__((__packed__)) DecartCoordinates {
    unsigned short x;
    unsigned short y;
};

/**
 * @brief Объект изображений.
 */
struct Image {
    unsigned short width;
    unsigned short height;
    std::vector<std::vector<RGB> > data;
};


struct __attribute__((__packed__)) FragmentPixel {
    unsigned short x;
    unsigned short y;
    RGB color;
};


typedef std::vector<FragmentPixel> Fragment;
typedef std::map< RGB , std::vector<DecartCoordinates> > ColorMap;

#endif // DATA_TYPES_H
