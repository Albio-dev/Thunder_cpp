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

void read_image(std::string path) {
    Images<float> k = Images<float>::fromtif(path);
}

int main() {

    std::random_device rdev;
    std::mt19937 rgen(rdev());
    std::uniform_int_distribution<int> idist(1, 4); //(inclusive, inclusive)

    Images<float> k = Images<float>::fromtif("../benchmark/data/" + std::to_string(idist(rgen)) + ".png");
    Images<float> a = Images<float>::frompng("../benchmark/data/" + std::to_string(idist(rgen)) + ".png");

    std::vector<Images<float>> allVector;

    auto start = std::chrono::system_clock::now();

    for (int i = 0; i < 1; i++) {
        std::string value = std::to_string(idist(rgen));
//        std::cout << value << "\t";
        Images<float> k = Images<float>::fromtif("../benchmark/data/" + value + ".tif");
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    std::cout << "Elapsed time file: " << elapsed_seconds.count() << "s" << std::endl;


    std::cout << "\n";


    std::vector<int> inputArray;
    std::vector<uint16_t> dimensions = {10, 10};
    for (int i = 0; i < 100; i++)
        inputArray.push_back(11);

    start = std::chrono::system_clock::now();
    for (int i = 0; i < 10000; i++) {
        ndarray<int> n = ndarray<int>::fromarray(dimensions, inputArray.data());
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;

    std::cout << "Elapsed time array: " << elapsed_seconds.count() << "s" << std::endl;


    ndarray<int> n = ndarray<int>::fromarray(dimensions, inputArray.data());

    n = n.var();
    n.clip(2, 4);
    n = n.mean();

    start = std::chrono::system_clock::now();
    for (int i = 0; i < 10000; i++) {
        ndarray<int> void_var = n.std();
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;

    std::cout << "Elapsed time std: " << elapsed_seconds.count() << "s" << std::endl;


    int f = 0;
    start = std::chrono::system_clock::now();
    for (int i = 0; i < 10000; i++) {
        f = n.count();
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;

    std::cout << "Elapsed time count: " << elapsed_seconds.count() << "s" << std::endl;


    return 0;
}