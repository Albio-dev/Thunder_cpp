#include "ndarray.cpp"

#include <stdio.h>
#include <iostream>

using namespace std;

int main() {

    int arr[] = {1, 2, 3, 4};
    vector<uint16_t> lengths = {2, 2};
    NDArray<int> n = NDArray<int>(lengths, arr);
    //NDArray<int> n(lengths, arr);
    for (uint16_t i: n.shape)
        cout << i << "\t";
    cout << "\n";
    return 0;
}