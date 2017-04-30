#include "artificial_intelligence.h"

ArtificialIntelligence::ArtificialIntelligence()
    : workers(this)
{
    double time_action = 0.1;
    frameID = 0;
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
    printf("%s",act.c_str());

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
    (void)system("killall -9 fceux");
}

void ArtificialIntelligence::MainLoop(int & enabled)
{
    workers.enabled = &enabled;
    TargetWindow screenShot("FCEUX 2.2.2");
    TargetSound targetSound;
    Image screenshot;
    SoundChunk sound;
    //Main loop
    while(enabled > 0){
        frameIDString = std::to_string(frameID);
        exec("wmctrl -a 'FCEUX 2.2.2'");
        int act=rand() % 3;
        int time_duration=rand() % 5;
        //Совершение выбранного переменной act действия в течении времени time
        action(act,0.1*time_duration);
        screenShot.getScreenShot(frameID,screenshot);
        targetSound.getSound(sound);
        this->analyze(screenshot,sound);
        ++frameID;
        sleep(3);
    }
}

void ArtificialIntelligence::diff2Images(Image &image1 ,
                                         Image &image2 ){
    diff.clear();
    if(workers.isWorkersEnabled){
        workers.arg1 = &image1;
        workers.arg2 = &image2;
        workers.CallFunctionInWorker(&ArtificialIntelligence::diff2ImagesWorker,image1.data.size());
        return;
    }

    #if defined(_OPENMP)
    #pragma omp parallel for
    #endif
    for( unsigned short y=0; y < image1.data.size() ; ++y ) {
        for( unsigned short x=0; x < image1.data[y].size() ; ++x ){
            if( image1.data[y][x] != image2.data[y][x] ){
                diff.push_back({x,y});
            }
        }
    }
}

void ArtificialIntelligence::diff2ImagesWorker(int iterBegin,int iterEnd){
    Image * image1 = (Image *)workers.arg1;
    Image * image2 = (Image *)workers.arg2;
    std::cerr<<iterBegin<<"begin"<<iterEnd<<std::endl;
    for( unsigned short y=iterBegin; y < iterEnd ; ++y ) {
        for( unsigned short x=0; x < image1->data[y].size() ; ++x ){
            if( image1->data[y][x] != image2->data[y][x] ){
                diff.push_back({x,y});

            }
        }
    }
    std::cerr<<iterBegin<<"end"<<iterEnd<<std::endl;
}

void ArtificialIntelligence::findConcurrencesInImage(Image &image)
{
    condReflexes.clear();
    if(workers.isWorkersEnabled && 1==2){
        workers.arg1 = &image;
        workers.CallFunctionInWorker(&ArtificialIntelligence::findConcurrencesInImageWorker,image.data.size());
        return;
    }

    for( unsigned short y=0; y < image.data.size() ; ++y ) {
        for( unsigned short x=0; x < image.data[y].size() ; ++x ){
            RGB color = image.data[y][x];
            if(condReflexes[color].size() == 0 ){
                vector<DecartCoordinates> tmpDC;
                condReflexes[color] = tmpDC;
            }
            condReflexes[color].push_back({x,y});
        }
    }
}

/**
 * 200 x 200 int array of maps better
 */
void ArtificialIntelligence::findConcurrencesInImageWorker(int iterBegin, int iterEnd)
{
    Image * image = (Image *)workers.arg1;

}

void ArtificialIntelligence::findRepeatedPatternsInImage(Image & image)
{
    //Тут надо создать поиск повторяющихся фрагментов
    //berem pervii pixel prosmatrivaem vse sovpadenia
    // Testing
    int min_width = 3;
    int min_height = 3;
    //Wrong
    //if the same then save
    /*
    for( unsigned short y=0; y < image.data.size() ; ++y ) {
        for( unsigned short x=0; x < image.data[y].size() - min_width ; ++x ){
            RGB color = image.data[y][x];
            for(auto coord : condReflexes[color]){
                if(image[coord.y][coord.x+1] ){
                    Fragment fragment;
                    fragments.push_back(fragment);
                }
            }
        }
    }
    */
}

void ArtificialIntelligence::analyze(Image &outputScreenshot,SoundChunk sound)
{
    static bool isFirstFrame = true;
    if(isFirstFrame){
        isFirstFrame = false;
    }else {
        this->diff2Images(outputScreenshot,oldScreenshot);
        Images diffImage(diff,outputScreenshot.width,outputScreenshot.height);
        std::string path = "output/screenshots/screenshot-"+frameIDString+"-diff.png";
        diffImage.saveImage(path);
    }

    this->findConcurrencesInImage(outputScreenshot);
    Images concurrencesImage(condReflexes,outputScreenshot.width,outputScreenshot.height);
    std::string pathReflexes = "output/screenshots/screenshot-"+frameIDString+"-reflexes.png";
    concurrencesImage.saveImage(pathReflexes);

    this->findRepeatedPatternsInImage(outputScreenshot);


    oldScreenshot = outputScreenshot;
}

void ArtificialIntelligence::analyzeConvolutionalNeuralNetwork(Image &output)
{
    (void) output;
}






