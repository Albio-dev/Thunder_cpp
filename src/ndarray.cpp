/**
 * @file ndarray.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-08-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "ndarray.hpp"
using namespace std;

/**
 * @brief 
 * Class to handle multidimensional matrices. Serializes dimensions into a monodimensional array.
 * 
 * @tparam T 
 * Datatype for the matrix  
 * 
 */
template <class T>
class NDArray{

    public:
        /// @var Actual values vector
        vector<T> value;
        /// @var Matrix size
        vector<uint16_t> shape;

    /**
     * @brief Construct a new NDArray object
     * 
     * @param lengths Dimensions vector object, basically a reshape
     * @param values Actual matrix values
     */
    NDArray(vector<std::uint16_t> lengths, T * values){

        //assert(lengths.size() != 0);
        shape = lengths;

        uint16_t values_length = lengths.back();
        lengths.pop_back();
        for(uint16_t i : lengths)
            values_length = values_length * i;

        for (unsigned int i = 0; i < values_length; i++){
            value.push_back(values[i]);
        }

    }

    /**
     * @brief Get the Data vector stored
     * 
     * @return vector<T> of data 
     */
    vector<T> getData(){
        return this->value;
    }

    /**
     * @brief Get the Shape vector
     * 
     * @return vector<uint16_t> shape vector: every position is the dimension size
     */
    vector<uint16_t> getShape(){
        return this->shape;
    }
};