#include "artificial_intelligence.h"

ArtificialIntelligence::ArtificialIntelligence()
{
    double time_action = 0.1;
    workersCount = 5;
    isWorkersEnabled = true;

    for(int i=0;i<workersCount;++i){
        workers.push_back(std::thread(&ArtificialIntelligence::workerDispatcher,this,i));
    }

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
    system("killall -9 fceux");
    //Notify about close
    cv.notify_all();
    for(int i=0;i<workersCount;++i){
        workers[i].join();
    }
}

void ArtificialIntelligence::MainLoop(int & enabled)
{
    _enabled = enabled;
    TargetWindow screenShot("FCEUX 2.2.2");
    Image screenshot;
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

void ArtificialIntelligence::diff2Images(Image &image1 ,
                                         Image &image2 ){
    if(isWorkersEnabled){
        cout<<"Calling worker";
        arg1 = &image1;
        arg2 = &image2;
        diff.clear();
        CallFunctionInWorker(&ArtificialIntelligence::diff2ImagesWorker,image1.data.size());
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

void ArtificialIntelligence::analyze(Image &outputScreenshot)
{
    map< RGB , vector<DecartCoordinates> > condReflexes;

    static bool isFirstTime = true;
    if(isFirstTime){
        isFirstTime = false;
    }else {
        this->diff2Images(outputScreenshot,oldScreenshot);
        Images diffImage(diff,outputScreenshot.width,outputScreenshot.height);
        std::string path = "output/screenshots/screenshot-"+frameIDString+"-diff.jpg";
        diffImage.saveImage(path);
    }

    for( unsigned short y=0; y < outputScreenshot.data.size() ; ++y ) {
        for( unsigned short x=0; x < outputScreenshot.data[y].size() ; ++x ){
            RGB color = outputScreenshot.data[y][x];
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

void ArtificialIntelligence::analyzeConvolutionalNeuralNetwork(Image &output)
{
    (void) output;
}

//Workers
void ArtificialIntelligence::workerDispatcher(int threadId)
{
    std::cout<<"Worker start:"<<threadId<<std::endl;
    int i=0;
    while(1==1){
        ++i;
        std::unique_lock<std::mutex> lk(mWorkers);
        cv.wait(lk);
        if(_enabled == 0)break;
        std::cerr<<"Thread"<<threadId<<" Iteration:"<<i+1<<std::endl;
        int avgInputForOneWorker = ceil(inputSizeForWorkers/(double)workersCount);
        int iterBegin = threadId * avgInputForOneWorker;
        int iterEnd = ( threadId+1 ) * avgInputForOneWorker;
        if(iterEnd>inputSizeForWorkers)iterEnd = inputSizeForWorkers - 1;
        (this->*activeFunctionForWorker)(iterBegin,iterEnd);
        finishedWorkersCount++;
        //if(finishedWorkersCount==workersCount) cvMainThread.notify_all();
    }
}

void ArtificialIntelligence::CallFunctionInWorker(AIfunction function,int sizeForDiv)
{
    inputSizeForWorkers  = sizeForDiv;
    activeFunctionForWorker = function;
    finishedWorkersCount = 0;
    cv.notify_all();
    while(finishedWorkersCount!=workersCount){};
    //std::unique_lock<std::mutex> lk(mMainThread);
    //cvMainThread.wait(lk);
}

void ArtificialIntelligence::diff2ImagesWorker(int iterBegin,int iterEnd){
    Image * image1 = (Image *)arg1;
    Image * image2 = (Image *)arg2;
    for( unsigned short y=iterBegin; y < iterEnd ; ++y ) {
        for( unsigned short x=0; x < image1->data[y].size() ; ++x ){
            if( image1->data[y][x] != image2->data[y][x] ){
                diff.push_back({x,y});
            }
        }
    }
}



