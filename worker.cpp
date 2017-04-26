#include "worker.h"

Worker::Worker(ArtificialIntelligence * ptr) : _ptr(ptr)
{
    workersCount = 5;
    isWorkersEnabled = true;

    for(int i=0;i<workersCount;++i){
        workers.push_back(std::thread(&Worker::workerDispatcher,this,i));
    }
}

Worker::~Worker()
{
    //Notify about close
    cv.notify_all();
    for(int i=0;i<workersCount;++i){
        workers[i].join();
    }
}
void Worker::workerDispatcher(int threadId)
{
    std::cout<<"Worker start:"<<threadId<<std::endl;
    int i=0;
    while(1==1){
        ++i;
        {
        std::unique_lock<std::mutex> lk(mWorkers);
        cv.wait(lk);
        }
        if(*enabled == 0)break;
        std::cerr<<"Thread"<<threadId<<" Iteration:"<<i+1<<std::endl;
        int avgInputForOneWorker = ceil(inputSizeForWorkers/(double)workersCount);
        int iterBegin = threadId * avgInputForOneWorker;
        int iterEnd = ( threadId+1 ) * avgInputForOneWorker;
        if(iterEnd>inputSizeForWorkers)iterEnd = inputSizeForWorkers - 1;
        (_ptr->*activeFunctionForWorker)(iterBegin,iterEnd);
        finishedWorkersCount++;
        if(finishedWorkersCount==workersCount) {
            std::cerr<<"YesThreads"<<std::endl;
            cvMainThread.notify_one();
        }
    }
}

void Worker::CallFunctionInWorker(AIfunction function,int sizeForDiv)
{
    inputSizeForWorkers  = sizeForDiv;
    activeFunctionForWorker = function;
    finishedWorkersCount = 0;
    cv.notify_all();
    if(finishedWorkersCount!=workersCount) {
        std::unique_lock<std::mutex> lk(mMainThread);
        cvMainThread.wait(lk);
    }
}
