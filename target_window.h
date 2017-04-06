#ifndef TARGETWINDOW_H
#define TARGETWINDOW_H

#include <malloc.h>
#include <string>
#include <cstring>
#include <cairo/cairo.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "3rdparty/bmp/bitmap_image.hpp"

class TargetWindow
{
public:
    TargetWindow(std::string windowTitle);
    void saveScreenShot(int screenID);
    Window window;
private:
    int get_shift(int mask);
    Window getX11WindowByTitle(Display *dpy, Window top, char *name);
    unsigned int width;
    unsigned int height;
};

#endif // TARGETWINDOW_H
