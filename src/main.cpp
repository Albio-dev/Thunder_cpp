#include "ndarray.cpp"
#include "images.cpp"
#include "series.cpp"

#include <stdio.h>
#include <iostream>

using namespace std;

int main() {

    int arr[] = {1, 2,    
                 3, 4,                  
                 5, 6};
    vector<uint16_t> lengths = {1, 2, 3};
    NDArray<int> n = NDArray<int>(lengths, arr);

    NDArray<int> data = n.getPosition({0, 1});

    Series<float> q = Series<float>();
    //q.fromtext("../data/values.txt");
    //q.fromrandom();

    NDArray<int> a = NDArray<int>({5, 1}, {1, 2, 3, 4, 5});
//    a.filter([](NDArray<int> input)
//                           { input.getShape(); return false; });

    Images<int> p = Images<int>();
    p.frombinary({3}, "../data/binary_values.txt");

    return 0;
}