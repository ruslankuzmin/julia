#include "artificial_intelligence.h"

ArtificialIntelligence::ArtificialIntelligence()
{
    double time_action = 0.1;
    system("fceux ../input/nintendo_games/Mario.nes &");
    //Ждать
    sleep(3);
    //Команда ОС - Активация окна с игрой
    exec("wmctrl -a 'FCEUX 2.2.2'");
    //Ждать
    sleep(3);
    //Команда ОС - Нажатие Enter
    action(5,time_action);
    //Ждать
    sleep(4);
    // Init vars
    frameID = 0;
}

///Выполнение команды операционной системы от имени программы с сохранением результата
std::string ArtificialIntelligence::exec(std::string cmd) {
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) return "ERROR";
    return "";
}

int ArtificialIntelligence::action(int a,float time)
{
    //Передаем массив нажимаемых кнопок
    std::string cmd,cmd2,act,times;
    FILE *ptr;
    exec("wmctrl -a 'FCEUX 2.2.2'");
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
    system("killall -9 fceux");
}

void ArtificialIntelligence::MainLoop(int & enabled)
{
    TargetWindow screenShot("FCEUX 2.2.2");
    std::vector< std::vector < RGB > > screenshot;
    //Main loop
    while(enabled > 0){
        frameIDString = std::to_string(frameID);
        exec("wmctrl -a 'FCEUX 2.2.2'");
        int act=rand() % 3;
        int time_duration=rand() % 5;
        //Совершение выбранного переменной act действия в течении времени time
        action(act,0.1*time_duration);
        screenShot.getScreenShot(frameID,screenshot);
        this->analyze(screenshot);
        ++frameID;
        sleep(3);
    }
}

void ArtificialIntelligence::diff2Images(std::vector< std::vector<RGB> > &image1 ,
                                         std::vector< std::vector<RGB> > &image2 ){
    if(diff.size()>0)diff.clear();

    #if defined(_OPENMP)
        #pragma omp parallel for
    #endif
    for( unsigned int y=0; y < image1.size() ; ++y ) {
        for( unsigned int x=0; x < image1[y].size() ; ++x ){
            if( image1[y][x] != image2[y][x] ){
                diff.push_back({x,y});
            }
        }
    }
}




void ArtificialIntelligence::analyze(std::vector< std::vector<RGB> > &outputScreenshot)
{
    map< RGB , vector<DecartCoordinates> > condReflexes;

    static bool isFirstTime = true;
    if(isFirstTime){
        isFirstTime = false;
    }else {
        this->diff2Images(outputScreenshot,oldScreenshot);
        Images diffImage(diff,256,240);
        std::string path = "output/screenshots/screenshot-"+frameIDString+"-diff.jpg";
        diffImage.saveImage(path);
    }

    for( unsigned int y=0; y < outputScreenshot.size() ; ++y ) {
        for( unsigned int x=0; x < outputScreenshot[y].size() ; ++x ){
            RGB color = outputScreenshot[y][x];
            if(condReflexes[color].size() == 0 ){
                vector<DecartCoordinates> tmpDC;
                condReflexes[color] = tmpDC;
            }
            condReflexes[color].push_back({x,y});
        }
    }
    oldScreenshot = outputScreenshot;

    for(auto key : condReflexes){
        cout<<key.second.size()<<endl;
    }
}



