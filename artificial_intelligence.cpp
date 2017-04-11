#include "artificial_intelligence.h"

ArtificialIntelligence::ArtificialIntelligence()
{
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
    this->MainLoop();
}

///Выполнение команды операционной системы от имени программы с сохранением результата
std::string ArtificialIntelligence::exec(std::string cmd) {
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) return "ERROR";
    std::string result;
    /*
    char buffer[128];
    while(!feof(pipe)) {
    if(fgets(buffer, 128, pipe) != NULL)
    result += buffer;
    }
    pclose(pipe);
    */
    return result;
}

int ArtificialIntelligence::action(int a,float time)
{
    //Передаем массив нажимаемых кнопок
    //Содержит команды командной строки
    std::string cmd,cmd2,act,times;
    FILE *ptr;
    exec("wmctrl -a 'FCEUX 2.2.1'");
    times=std::to_string(time);

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

ArtificialIntelligence::~ArtificialIntelligence()
{

}

void ArtificialIntelligence::MainLoop()
{
    TargetWindow screenShot("FCEUX 2.2.2");
    //Main loop
    int i = 0;
    while(1==1){
        exec("wmctrl -a 'FCEUX 2.2.2'");
        int act=rand() % 3;
        int time_duration=rand() % 5;
        //Совершение выбранного переменной act действия в течении времени time
        action(act,0.1*time_duration);
        std::vector< std::vector < RGB > > output;
        screenShot.getScreenShot(i,output);
        analyse(output);
        ++i;
        sleep(3);
    }
}

int ArtificialIntelligence::analyse(std::vector<std::vector<RGB> > &output)
{
    std::cout<<"output.size:"<<output.size()<<std::endl;
    std::cout<<"output[1].size:"<<output[1].size()<<std::endl;
}



