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

#include "target_window.h"

#if defined(_OPENMP)
    #include "omp.h"
#endif

#ifdef OPEN_CL
    #include "omp.h"
#endif

using namespace std;
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
    void analyze(std::vector< std::vector < RGB > > & output);
    int action(int a, float time);
    std::string exec(std::string cmd);
    void diff2Images(std::vector<std::vector<RGB> > &image1, std::vector<std::vector<RGB> > &image2);
    std::vector< std::vector<RGB> > oldScreenshot;
    std::vector< DecartCoordinates > diff;
    int frameID;
    string frameIDString;
};

#endif // ARTIFICIAL_INTELLIGENCE_H
