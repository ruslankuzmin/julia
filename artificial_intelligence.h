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

#include "images.h"
#include "worker.h"
#include "target_window.h"
#include "neural_networks/convolutional_nn.h"

#if defined(_OPENMP)
    #include "omp.h"
#endif

#ifdef OPEN_CL
    #include "omp.h"
#endif

using namespace std;

/**
 * @brief Основной процесс.
 */
class ArtificialIntelligence
{
public:
    ArtificialIntelligence();
    ~ArtificialIntelligence();
    /**
     * @brief MainLoop Главный цикл.
     * @param enabled Отключающая главный цикл переменная.
     */
    void MainLoop(int & enabled);
private:
    /**
     * @brief analyze Анализ полученного от приложения скриншота.
     * @param output Скриншот полученный от приложения.
     */
    void analyze(Image & output);
    /**
     * @brief analyzeConvolutionalNeuralNetwork
     * @param output
     */
    void analyzeConvolutionalNeuralNetwork(Image & output);
    /**
     * @brief action Выполение действия в игре. Например прыжок или движение вперед.
     * @param a Номер действия
     * @param time Сколько по времени будет зажата клавиши и выолняться действие.
     * @return
     */
    int action(int a, float time);
    /**
     * @brief exec Выполнение команды приложением через терминал.
     * @param cmd Команда
     * @return Вывод команды.
     */
    std::string exec(std::string cmd);
    /**
     * @brief oldScreenshot Изображение скриншота сделанного до обрабатываемого.
     */
    Image oldScreenshot;
    /**
     * @brief diff Сохраненная разница пикселей двух изображений.
     */
    std::vector< DecartCoordinates > diff;
    ColorMap condReflexes;
    std::vector<Fragment> fragments;

    /**
     * @brief frameID Порядковый номер обрабатываемого скриншота.
     */
    int frameID;
    /**
     * @brief frameIDString Порядковый номер обрабатываемого скриншота в виде строковой переменной.
     */
    string frameIDString;
    /**
     * @brief workers
     */
    Worker workers;
    //Main functions
    /**
     * @brief diff2Images Сравнение двух последовательных изображений попиксельно для получения списка различающихся пискселей
     * @param image1 Первое изображение
     * @param image2 Второе изображение
     */
    void diff2Images(Image &image1, Image &image2);
    void diff2ImagesWorker(int iterBegin,int iterEnd);
    /**
     * @brief findConcurrencesInImage
     */
    void findConcurrencesInImage(Image &image);
    void findConcurrencesInImageWorker(int iterBegin,int iterEnd);
    /**
     * @brief findRepeatedPatternsInImage
     */
    void findRepeatedPatternsInImage(Image &outputScreenshot);
    /**
     * @brief cnn Свёрточная нейронная сеть. Добавлена ради эксперимента.
     */
    ConvolutionalNN cnn;
};

#endif // ARTIFICIAL_INTELLIGENCE_H
