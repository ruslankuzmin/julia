#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
/*
    //Устаревший метод - из -за привоения вектора
    std::auto_ptr<int> x_ptr(new int(42));
    std::auto_ptr<int> y_ptr;
    //Нехороший момент
    y_ptr = x_ptr;
    // segmentation fault
    std::cout << *x_ptr << std::endl;

    //В отличии от auto_ptr, unique_ptr запрещает копирование.
    std::unique_ptr<int> x_ptr(new int(42));
    std::unique_ptr<int> y_ptr;
    // ошибка при компиляции
    y_ptr = x_ptr;
    // ошибка при компиляции
    std::unique_ptr<int> z_ptr(x_ptr);
    Изменение прав владения ресурсом осуществляется с помощью вспомогательной функции std::move (которая является частью механизма перемещения).
    Как auto_ptr, так и unique_ptr обладают методами reset(), который сбрасывает права владения, и get(), который возвращает сырой (классический) указатель.
    shared_ptr Это самый популярный и самый широкоиспользуемый умный указатель. Он начал своё развитие как часть библиотеки boost.
Задача - создать эффективный массив из int и его перебрать

*/
/*Правила:
Использовать shared_ptr
*/
    std::shared_ptr<int> ptr(new int(200));
    std::cout<<ptr.get()[23];
    for(int i=0;i<200;++i){
        ptr.get()[i];
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}
