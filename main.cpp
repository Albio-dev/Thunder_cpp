#include "include/ndarray.hpp"
#include "src/images.cpp"
#include "src/series.cpp"

#include <stdio.h>
#include <iostream>

//using namespace std;

template <typename T>
void printMat(ndarray<T> input)
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

/*
    std::cout << std::is_trivially_copyable<ndarray<int>>::value << "\n";
    std::cout << std::is_standard_layout<ndarray<int>>::value << "\n";
    std::cout << std::is_pod<ndarray<int>>::value << "\n";

    std::cout << std::is_trivially_copyable<Series<int>>::value << "\n";
    std::cout << std::is_standard_layout<Series<int>>::value << "\n";
    std::cout << std::is_pod<Series<int>>::value << "\n";

    std::cout << std::is_trivially_copyable<Images<int>>::value << "\n";
    std::cout << std::is_standard_layout<Images<int>>::value << "\n";
    std::cout << std::is_pod<Images<int>>::value << "\n";
*/
    auto a = ndarray<int>::fromarray({5}, {1, 2, 3, 4, 5});
    //a[2] +=1;

    std::cout << a[2] << "\n";

    return 0;
}