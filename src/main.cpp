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
    /*
        NDArray<int> a = NDArray<int>({3, 2, 2}, {1, 2,
                                                  3, 4,

                                                  5, 6,
                                                  7, 8,

                                                  9, 10,
                                                  11, 12});
        NDArray<int> output;
        NDArray<int> input;
        NDArray<int>  temp;
    */
    //Series<double> output;
    /*
    Series<double> intput;

    Series<double> a;
    a.fromrandom({3, 3, 3});
    printMat(a);

    int output = a.count();
    cout << output << "\n";
*/
    

/*
    a.reshape({6, 2}); // Prendere ultima dimensione e moltiplicazione di tutte le altre
    cout << "\nOriginal";
    printMat(a);

    // Test serie
    temp = NDArray<int>::transpose(a);
    cout << "\nTransposed";
    printMat(temp);
    
    cout << "\nmax:";
    output = temp.max(); 
    printMat(output);
*/
/*
    // Test images
    a.reshape({3, 4}); // Prendere moltiplicazione di tutte le dimensioni tranne le ultime 2 e la moltiplicazione delle ultime 2
    cout << "\nOriginal";
    printMat(a);

    temp = NDArray<int>::transpose(a);
    cout << "\nTransposed";
    printMat(temp);

    output = temp.max(); 
    cout << "\nMax:";
    printMat(output);

    output.reshape({2, 2});
    printMat(output);
*/
/*
    NDArray<int> b = NDArray<int>({5, 1}, {1, 2, 3, 4, 5});

    Images<int> p = Images<int>();
    p.frombinary({3}, "../data/binary_values.txt");
*/
    return 0;
}