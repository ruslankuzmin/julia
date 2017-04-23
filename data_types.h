#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <vector>

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

struct __attribute__((__packed__)) DecartCoordinates {
    unsigned short x;
    unsigned short y;
};

struct Image {
    unsigned short width;
    unsigned short height;
    std::vector<std::vector<RGB> > data;
};
#endif // DATA_TYPES_H
