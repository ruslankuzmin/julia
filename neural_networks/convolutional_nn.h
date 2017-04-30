#ifndef CONVOLUTIONAL_NN_H
#define CONVOLUTIONAL_NN_H

#include <vector>
#include "../data_types.h"

#define LAYERS_COUNT 5
#define KERNEL_WIDTH 5
class ConvolutionalNN
{
public:
    ConvolutionalNN();
    void setImage(Image & newImage);
    int getID();
private:
    std::vector<Image> layers;
    Image kernel;
};

#endif // CONVOLUTIONAL_NN_H
