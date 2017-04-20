#ifndef ARTIFICIAL_INTELLIGENCE_H
#define ARTIFICIAL_INTELLIGENCE_H

#include <iostream>
#include <time.h>
#include <unistd.h>
#include <omp.h>
#include <math.h>

#include <map>
#include <vector>

#include "target_window.h"

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
};

#endif // ARTIFICIAL_INTELLIGENCE_H
