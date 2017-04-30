#ifndef TARGETWINDOW_H
#define TARGETWINDOW_H

#include <malloc.h>
#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <cairo/cairo.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "data_types.h"

/**
 * @brief Взаимодействие с окном целевого приложения .Например с игрой.
 */
class TargetWindow
{
public:
    /**
     * @brief TargetWindow Получение данных целевого окна.
     * @param windowTitle Заголовок окна.
     */
    TargetWindow(std::string windowTitle);
    /**
     * @brief getScreenShot Получение скриншота.Сохранение скриншота в файл и в буфер.
     * @param screenID Номер скриншота для создания имени сохранения.
     * @param output Структура в которую будет сохранен скриншот.
     */
    void getScreenShot(int screenID,Image & output);
    /**
     * @brief window
     */
    Window window;
private:
    int get_shift(int mask);
    /**
     * @brief getX11WindowByTitle Получение идентификатора окна по его заголовку.
     * @param dpy
     * @param top
     * @param name
     * @return
     */
    Window getX11WindowByTitle(Display *dpy, Window top, char *name);
    /**
     * @brief width Ширина окна в пикселях.
     */
    unsigned int width;
    /**
     * @brief height Длина окна в пикселях.
     */
    unsigned int height;
};

#endif // TARGETWINDOW_H
