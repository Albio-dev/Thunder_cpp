#include "include/ndarray.hpp"
#include "src/images.cpp"
#include "src/series.cpp"

#include <stdio.h>
#include <iostream>

//using namespace std;

#include <chrono>
#include <ctime>


template<typename T>
void printMat(ndarray<T> input) {
    for (uint16_t i = 0; i < input.size(); i++) {
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

    return 0;
}