#include "ndarray.cpp"

using namespace std;

int main() {

    int arr[] = {1, 2, 3, 4};
    vector<uint16_t> lengths = {2, 2};
//    NDArray n = NDArray<int>(lengths, arr);
    NDArray<int> n(lengths, arr);
    for (uint16_t i: n.shape)
        std::cout << i;
    return 0;
}