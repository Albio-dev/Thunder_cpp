#include "ndarray.cpp"
#include "images.cpp"
#include "series.cpp"

#include <stdio.h>
#include <iostream>

using namespace std;

void printMat(NDArray<int> input){
    for (uint16_t i = 0; i < input.size(); i++)
    {
        if (i % input.getShape()[1] == 0)
            cout << "\n";
        cout << input[i] << "\t";
    }
    
    cout << "\n";
}

int main() {

    NDArray<int> a = NDArray<int>({3, 2, 2}, {1, 2,
                                              3, 4,

                                              5, 6,
                                              7, 8,

                                              9, 10,
                                              11, 12});
    NDArray<int> output;
    NDArray<int> input;
    NDArray<int>  temp;

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
    
    return 0;
}