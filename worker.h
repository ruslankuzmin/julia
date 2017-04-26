#ifndef WORKER_H
#define WORKER_H

#include <vector>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <iostream>
#include <cmath>

class ArtificialIntelligence;
typedef void (ArtificialIntelligence::*AIfunction)(int,int);

/**
 * @brief Класс для параллельного выполнения функций с помощью потоков.Реализация похожа на .
 */
class Worker
{
public:
    /**
     * @brief Worker Конструктор
     * @param ptr Указатель на основной процесс
     */
    Worker(ArtificialIntelligence * ptr);
    ~Worker();
    /**
     * @brief _ptr Указатель на основной процесс
     */
    ArtificialIntelligence * _ptr;
    /**
     * @brief workerDispatcher
     * @param threadId
     */
    void workerDispatcher(int threadId);
    /**
     * @brief workers Потоки параллельного выполнения.
     */
    std::vector<std::thread> workers;
    /**
     * @brief workersCount Количество потоков
     */
    std::atomic<int> workersCount;
    /**
     * @brief finishedWorkersCount Количество потоков окончивших своё выполнение.
     */
    std::atomic<int> finishedWorkersCount;
    /**
     * @brief CallFunctionInWorker Обертка для создания запроса к потокам.
     * @param function Выполняемая функция главного класса.
     * @param sizeForDiv Разделяемое между потоками количество итераций цикла.
     */
    void CallFunctionInWorker(AIfunction function,int sizeForDiv);
    /**
     * @brief mWorkers Мьютекс потоков.
     */
    std::mutex mWorkers;
    /**
     * @brief mMainThread Мьютекс главного потока.
     */
    std::mutex mMainThread;
    /**
     * @brief cv Сигнализирует о появлении новой выполняемой функции потокам.
     */
    std::condition_variable cv;
    /**
     * @brief cvMainThread Сигнализирует о завершении потоков главному потоку.
     */
    std::condition_variable cvMainThread;
    /**
     * @brief inputSizeForWorkers Разделяемое между потоками количество итераций цикла.
     */
    std::atomic<int> inputSizeForWorkers;
    /**
     * @brief activeFunctionForWorker Текущая выполняемая в потоках функция.
     */
    AIfunction activeFunctionForWorker;
    /**
     * @brief enabled Сигнализирует о завершении основного потока.
     */
    int * enabled;
    /**
     * @brief isWorkersEnabled Включены ли потоки.
     */
    bool isWorkersEnabled;
    /**
     * @brief arg1 Первая входная переменная для выполняемых параллельно функций.
     */
    void *arg1;
    /**
     * @brief arg2 Вторая входная переменная для выполняемых параллельно функций.
     */
    void *arg2;
    /**
     * @brief arg3 Третья входная переменная для выполняемых параллельно функций.
     */
    void *arg3;
    /**
     * @brief arg4 Четвертая входная переменная для выполняемых параллельно функций.
     */
    void *arg4;
};

#endif // WORKER_H
