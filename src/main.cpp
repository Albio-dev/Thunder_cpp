#include "ndarray.cpp"

using namespace std;

int main(){

    int arr[] = {1, 2, 3, 4};
    vector<int> lengths = {2, 2};
    ndarray n = ndarray(lengths, arr);

    return 0;
}