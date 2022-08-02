#include "ndarray.hpp"
#include <vector>
#include <iostream>

using namespace std;

class ndarray{

    public:
    vector<int> array;

    ndarray(vector<int> lengths, int* values){

        int values_length = 1;
        for (uint j = 0; j < lengths.size(); j++)
            values_length = j * values_length;
        
        for (int i = 0; i < values_length; i++){
            array.push_back(values[i]);
        }

        for (uint j = 0; j < array.size(); j++){

            cout << array[j] << "\t";
            
        }
        cout << "\n";

    }
};