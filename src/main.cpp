#include "ndarray.cpp"
#include "images.cpp"
#include "series.cpp"

#include <stdio.h>
#include <iostream>

#define cimg_display 0
#define cimg_use_png 1
#define cimg_use_tiff 0
#define cimg_use_jpeg 0

#include "../third_party/CImg.h"

using namespace std;

template <typename T>
void printMat(NDArray<T> input)
{
    for (uint16_t i = 0; i < input.size(); i++)
    {
        if  (i % (input.count()) == 0)
            cout << "\n";
        
        if (i % input.getShape()[1] == 0)
            cout << "\n";
        
        cout << input[i] << "\t";
    }
    
    cout << "\n";
}

int main() {

    return 0;
}