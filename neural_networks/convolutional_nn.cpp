#include "convolutional_nn.h"

ConvolutionalNN::ConvolutionalNN()
{
    kernel.width = KERNEL_WIDTH;
    kernel.height = KERNEL_WIDTH;
}

void ConvolutionalNN::setImage(Image &newImage)
{
    if(layers.size() == 0){
        for(int i=0;i<LAYERS_COUNT;++i){
            Image tmp;
            tmp.width = newImage.width;
            tmp.height = newImage.height;
            layers.push_back(tmp);
        }
        for(int i=0;i<kernel.height;++i){
            for(int j=0;j<kernel.height;++j){
                RGB tmp;
                tmp.r = rand() % 255 / newImage.width * newImage.height * LAYERS_COUNT;
            }
        }
    }
}

int ConvolutionalNN::getID()
{

}
