#include <QApplication>
#include <QWebEngineView>
#include "artificial_intelligence.h"
//C++ libs
#include <thread>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <unistd.h>

using namespace std;

///Выполнение команды операционной системы от имени программы с сохранением результата
std::string exec(std::string cmd) {
FILE* pipe = popen(cmd.c_str(), "r");
if (!pipe) return "ERROR";
char buffer[128];
std::string result;
/*
while(!feof(pipe)) {
if(fgets(buffer, 128, pipe) != NULL)
result += buffer;
}
pclose(pipe);
*/
return result;
}

//Конвертирование из int в string
namespace convert
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

int action(int a,float time)
{
    //Передаем массив нажимаемых кнопок
    //Содержит команды командной строки
    string cmd,cmd2,act,times;
    FILE *ptr;
    exec("wmctrl -a 'FCEUX 2.2.1'");
    times=convert::to_string(time);

     switch (a)
      {
         case 0:
            cmd="";//
        cmd2="";
        act="Ничего не делаю в течении "+times+" сек.";
            break;
         case 1:
            cmd= "xdotool keydown Right";
        cmd2= "xdotool keyup Right";
            act="Двигаюсь вправо в течении "+times+" сек.";
        break;
         case 2:
            cmd= "xdotool keydown f+Right";//Прыжок
        cmd2= "xdotool keyup f+Right";
            act="Прыгаю влево в течении "+times+" сек.";
        break;
         case 3:
            cmd= "xdotool keydown f+Left";//Прыжок
        cmd2= "xdotool keyup f+Left";
            act="Прыгаю вправо в течении "+times+" сек.";
        break;
         case 4:
            cmd= "xdotool keydown Left";
            cmd2="xdotool keyup Left";
        act="Двигаюсь влево в течении "+times+" сек.";
            break;
         case 5:
            cmd= "xdotool keydown Return;";
            cmd2="xdotool keyup Return;";
        act="Нажимаю Enter  в течении "+times+" сек.";
        break;
      }

    act=act+"\n";
    printf(act.c_str());

    //Input command in command line
    ptr = popen(cmd.c_str(), "r");
    pclose(ptr);
    sleep(time);
    ptr = popen(cmd2.c_str(), "r");
    pclose(ptr);
    return 0;
}

void aiThread(){
    double time_action = 0.1;
    //Команда ОС - Закрыть другие окна с игрой
    system("fceux ../input/nintendo_games/Mario.nes &");
    //Ждать 3 секунды
    sleep(3);
    //Команда ОС - Активация окна с игрой
    exec("wmctrl -a 'FCEUX 2.2.2'");
    //Ждать 3 секунды
    sleep(3);
    //Команда ОС - Нажатие Enter
    action(5,time_action);
    //Ждать 3 секунды
    sleep(4);
    //Main loop
    while(1==1){
        //Команда ОС - Активация окна с игрой
        exec("wmctrl -a 'FCEUX 2.2.2");
        int act=rand() % 3;
        int time_duration=rand() % 5;
        //Совершение выбранного переменной act действия в течении времени time
        action(act,0.1*time_duration);
        sleep(3);
    }
}

int main(int argc, char *argv[])
{
    //AI thread
    thread ai(aiThread);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QWebEngineView view;
    view.setUrl(QUrl("qrc:///gui-html-files/index.html"));
    view.resize(1024, 600);
    view.show();
    return app.exec();

    ai.join();
}
