#include "target_window.h"

TargetWindow::TargetWindow(std::string windowTitle)
{
    Display *display = XOpenDisplay(NULL);
    window = getX11WindowByTitle( display , DefaultRootWindow(display) , (char *)windowTitle.c_str() );
}

Window TargetWindow::getX11WindowByTitle(Display *dpy, Window top, char *name)
{
    Window *children, dummy;
    unsigned int nchildren;
    unsigned int i;
    Window w = 0;
    char *window_name;

    if (XFetchName(dpy, top, &window_name) && !strcmp(window_name, name))
        return (top);

    if (!XQueryTree(dpy, top, &dummy, &dummy, &children, &nchildren))
        return (0);

    for (i = 0; i < nchildren; i++)
    {
        w = getX11WindowByTitle(dpy, children[i], name);
        if (w)
            break;
    }
    if (children)
        XFree((char *) children);
    return (w);
}

void TargetWindow::getScreenShot(int screenID,std::vector< std::vector < RGB > > & output)
{
    Display *disp;
    XWindowAttributes watts;
    XImage *image;
    cairo_surface_t *surface;
    int stride;
    disp = XOpenDisplay(NULL);
    XGetWindowAttributes(disp, window, &watts);
    width = watts.width;
    height = watts.height;

    image = XGetImage(disp, window, watts.x, watts.y, width, height, AllPlanes,ZPixmap);
    stride = cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, width);
    unsigned char * data = (unsigned char *) malloc (stride * height);
    int red_shift = get_shift(image->red_mask);
    int green_shift = get_shift(image->green_mask);
    int blue_shift = get_shift(image->blue_mask);

    std::cout<<"width:"<<width<<"height:"<<height<<std::endl;

    output.clear();
    for (unsigned int y = 0; y < height; ++y)
    {
        std::vector < RGB > tmp;
        output.push_back(tmp);
        for (unsigned int x = 0; x < width; ++x) {
            unsigned long pixel = XGetPixel(image, x, y);
            unsigned char red = (image->red_mask & pixel) >> red_shift;
            unsigned char green = (image->green_mask & pixel) >> green_shift;
            unsigned char blue = (image->blue_mask & pixel) >> blue_shift;
            data[y * stride + x * 4 + 0]=blue;
            data[y * stride + x * 4 + 1]=green;
            data[y * stride + x * 4 + 2]=red;
            RGB color;
            color.b = blue;
            color.g = green;
            color.r = red;
            output[y].push_back(color);
        }
    }
    std::string filename="output/screenshots/screenshot-"+std::to_string(screenID)+".png";
    surface = cairo_image_surface_create_for_data(data,CAIRO_FORMAT_RGB24,width,height,stride);
    cairo_surface_write_to_png(surface,filename.c_str());
    cairo_surface_destroy(surface);
    free(data);
}

inline int TargetWindow::get_shift (int mask) {
      int shift = 0;
      while (mask) {
        if (mask & 1) break;
        shift++;
        mask >>=1;
      }
      return shift;
}

