#include "ndarray.hpp"
#include <vector>

#include <iostream>

using namespace std;

template <class T>
class NDArray{

    public:
        vector<T> value;
        vector<uint16_t> shape;

    NDArray(vector<uint16_t> lengths, T * values){

        assert(lengths.size() != 0);
        shape = lengths;

        uint16_t values_length = lengths.back();
        lengths.pop_back();
        for(uint16_t i : lengths)
            values_length = values_length * i;

        for (uint i = 0; i < values_length; i++){
            value.push_back(values[i]);
        }

        for (uint j = 0; j < value.size(); j++){
            cout << value[j] << "\t";
        }

        cout << "\n";

    }
};