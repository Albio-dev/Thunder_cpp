#include "ndarray.cpp"
#include "images.cpp"
#include "series.cpp"

#include <stdio.h>
#include <iostream>

using namespace std;

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
            cout << "\n";
        
        cout << input[i] << "\t";
    }
    
    cout << "\n";
}

int main() {


    NDArray<int> a = NDArray<int>({5}, {1, 2, 3, 4, 5});
    printMat(a);




    return 0;
}