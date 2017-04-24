#ifndef ARTIFICIAL_INTELLIGENCE_H
#define ARTIFICIAL_INTELLIGENCE_H

#include <iostream>
#include <time.h>
#include <unistd.h>
#include <omp.h>
#include <math.h>
#include <stdio.h>
#include <map>
#include <vector>
#include <thread>
#include <condition_variable>
#include <mutex>



#include "images.h"

#include "target_window.h"

#if defined(_OPENMP)
    #include "omp.h"
#endif

#ifdef OPEN_CL
    #include "omp.h"
#endif

using namespace std;

class ArtificialIntelligence;
typedef void (ArtificialIntelligence::*AIfunction)(int,int);
/**
 * @brief The ArtificialIntelligence class
 */
class ArtificialIntelligence
{
public:
    ArtificialIntelligence();
    ~ArtificialIntelligence();
    void MainLoop(int & enabled);
private:
    //Current thread
    void analyze(Image & output);
    void analyzeConvolutionalNeuralNetwork(Image & output);
    int action(int a, float time);
    std::string exec(std::string cmd);
    void diff2Images(Image &image1, Image &image2);
    Image oldScreenshot;
    std::vector< DecartCoordinates > diff;
    int frameID;
    string frameIDString;
    bool _enabled;
    //Workers
    void workerDispatcher(int threadId);
    std::vector<std::thread> workers;
    int workersCount;
    int finishedWorkersCount;
    void CallFunctionInWorker(AIfunction function,int sizeForDiv);
    std::mutex mWorkers;
    std::mutex mMainThread;
    std::condition_variable cv;
    std::condition_variable cvMainThread;
    int inputSizeForWorkers;
    AIfunction activeFunctionForWorker;
    void diff2ImagesWorker(int iterBegin,int iterEnd);
    bool isWorkersEnabled;
    void *arg1;
    void *arg2;
    void *arg3;
    void *arg4;
};

#endif // ARTIFICIAL_INTELLIGENCE_H
