#include "ndarray.cpp"

#include <stdio.h>
#include <iostream>

using namespace std;

int main() {

    int arr[] = {1, 2,
                 3, 4,
                 /////////////
                 5,6,
                 7,8};
    vector<uint16_t> lengths = {2, 2, 2};
    NDArray<int> n = NDArray<int>(lengths, arr);
    //NDArray<int> n(lengths, arr);
    for (uint16_t i: n.getData())
        cout << i << "\t";
    cout << "\n";

    int i = n.getPosition({1, 0, 0});
    cout << i;
     i = n.getPosition({1, 0, 1});
    cout << i;
     i = n.getPosition({1, 1, 0});
    cout << i;
     i = n.getPosition({1, 1, 1});
    cout << i;


    return 0;
}