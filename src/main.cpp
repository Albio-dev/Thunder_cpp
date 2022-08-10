/*
#include "ndarray.cpp"
#include "images.cpp"
#include "series.cpp"
*/

#include <stdio.h>
#include <iostream>

#define cimg_display 0
#define cimg_use_png 1
#define cimg_use_tiff 1
#define cimg_use_jpeg 1

#define cimg_OS 1

#include "../third_party/CImg.h"

using namespace std;
using namespace cimg_library;

/*
template <typename T>
void printMat(NDArray<T> input)
{
    for (uint16_t i = 0; i < input.size(); i++)
    {
        
        if (i % input.getShape()[0] == 0)
            cout << "\n";
        
        cout << input[i] << "\t";
    }
    
    cout << "\n";
}*/

int main() {

    CImg<float> image("../data/singlelayer_png/dot1_grey.png");

    return 0;
}