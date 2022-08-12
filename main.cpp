#include "ndarray.hpp"
#include "../src/images.cpp"
#include "../src/series.cpp"

#include <stdio.h>
#include <iostream>

//using namespace std;

template <typename T>
void printMat(NDArray<T> input)
{
    for (uint16_t i = 0; i < input.size(); i++)
    {
        /*
        if  (i % (input.count()) == 0)
            cout << "\n";
        */
        
        if (i % input.getShape()[0] == 0)
            std::cout << "\n";
        
        std::cout << input[i] << "\t";
    }
    
    std::cout << "\n";
}

int main() {

    Series<int> a = Series<int>({1, 5}, {1, 2, 3, 4, 5});
    Images<int> b = Images<int>({1, 5}, {1, 2, 3, 4, 5});
    cimg_library::CImg<float> p = b.read_image("../data/singlelayer_png/dot2_grey.png");

    NDArray<int> c = a.element_wise(b, std::minus<int>());
    printMat(c);
    return 0;
}