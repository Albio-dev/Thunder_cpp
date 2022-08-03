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
template<class T>
class NDArray {

public:
    /// @var Actual values vector
    vector<T> value;
    /// @var Matrix size
    vector<uint16_t> shape;

    /**
     * @brief Construct a new NDArray object
     */
    NDArray() = default;

    /**
     * @brief Construct a new NDArray object
     *
     * @param lengths Dimensions vector object, basically a reshape
     * @param values Actual matrix values
     */
    NDArray(vector<std::uint16_t> lengths, T *values) {

        // Data checks
        if (lengths.size() == 0)
            throw "Requested 0 dimensioned array";

        this->shape = lengths;

        uint16_t values_length = 1;
        for (uint16_t i: lengths)
            values_length = values_length * i;

        for (unsigned int i = 0; i < values_length; i++) {
            value.push_back(values[i]);
        }

    }

    /**
     * @brief Get the Data vector stored
     * 
     * @return vector<T> of data 
     */
    vector<T> getData() {
        return this->value;
    }

    /**
     * @brief Get the Shape vector
     * 
     * @return vector<uint16_t> shape vector: every position is the dimension size
     */
    vector<uint16_t> getShape() {
        return this->shape;
    }

    /**
     * @brief Get the value in position given a vector with a precise location
     *
     * @param pos a vector with a position
     * @return vector<T> value referenced by pos
     */
    T getPosition(vector<int> pos) {

        // Check indexing
        if (pos.size() != shape.size())
            throw "Wrong dimensional indexing: dimensions mismatch";

        // Calculate requested element's position
        int position = 0;
        for (unsigned int i = 0; i < shape.size(); i++) {
            // Check if index out of bounds
            if (pos[i] < 0 || pos[i] >= shape[i])
                throw "Index out of bounds";

            // Calculating chunk size
            int total = 1;
            for (unsigned int k = shape.size()-1; k != i ; k--) {
                total = total * shape[k];
            }

            // Shift index by input * chunk size
            position = position + pos[i] * total;

        }

        return value[position];
    }

    /**
     * @brief Explicit count of elements. Return one default, I use only one matrix. Spark use multiple matrices
     *
     * @return 1
     */
    int count() {
        return 1;
    }

    /**
     * @brief Clip values in an array above and below
     *
     * @param min_value min value to clip
     * @param max_value max value to clip
     */
    void clip(const T& min_value, const T& max_value) {
        std::transform(std::begin(value), std::end(value), std::begin(value),
                       [&] (const T& v) { return std::clamp(v, min_value, max_value); });
    }

    /**
     * @brief Dot devide and array with another. ToDo: Controlli grandezze array e valori siano corretti/compatibibli
     *  tipo se un valore é di tipo int e l'altro tipo uint cast di che tipo (int imo)
     *
     * @return
     */
    template<class K>
    vector<double> dotdivide(const NDArray<K> other) {
        if(shape != other.shape)
            throw "Array shape don't match";

        vector<double> out = {};

        for(unsigned int i = 0; i < value.size(); i++){
            out.push_back(value[i]/(double)other.value[i]);
        }

        return out;
    }


};