#include "ndarray.cpp"

#include <stdio.h>
#include <iostream>

using namespace std;

int main() {

    int arr[] = {1, 2,    
                 3, 4,                  
                 5, 6};
    vector<uint16_t> lengths = {1, 2, 3};
    NDArray<int> n = NDArray<int>(lengths, arr);

    NDArray<int> data = *n.getPosition({0, 1});

    for (int i = 0; i < data.size(); i++){
        cout << data[i] << "\t";
    }
    cout << "\n";


    return 0;
}