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
        // TODO: forse values può essere convertita direttamente in un vector?
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
     * @brief Construct a new NDArray object by moving vector pointers
     * 
     * @param lengths Vector of dimensions sizes
     * @param values Vector of elements
     */
    NDArray(std::vector<uint16_t>& lengths, std::vector<T>& values){
        shape = lengths;
        value = values;
    }

    /**
     * @brief Get the value in position given a vector with a precise location
     *
     * @param pos a vector with a position
     * @return vector<T> value referenced by pos
     */
    NDArray<T>* getPosition(vector<T> pos) {

        // Check indexing        
        if (pos.size() > shape.size())
            throw "Wrong dimensional indexing: dimensions mismatch";
        
        int lastdim = pos.size();

        // Calculate requested element's position up to the specified dimension
        int startIndex = 0;
        for (unsigned int i = 0; i < pos.size(); i++) {
            // Check if index out of bounds
            if (pos[i] < 0 || pos[i] >= shape[i])
                throw "Index out of bounds";

            // Calculating chunk size 
            int subDimensionSize = 1;
            for (unsigned int k = shape.size()-1; k != i ; k--) {
                subDimensionSize *= shape[k];
            }

            // Shift index by input * chunk size
            startIndex = startIndex + pos[i] * subDimensionSize;

        }

        vector<uint16_t> new_shape;
        // Starting from the missing dimension calculates the size of the identified matrix
        int endindex = 1;
        for (unsigned int i = lastdim; i < shape.size(); i++){
            endindex *= shape[i];
            new_shape.push_back(shape[i]);
        }
        endindex += startIndex;

        // Temporary output structure
        vector<T> output_temp;

        // Extract data in range
        do{
            output_temp.push_back(this->value[startIndex]);
            startIndex++;
        } while (startIndex < endindex);

        return new NDArray<int>(new_shape, output_temp);
    }

    /**
     * @brief Function to directly address the underlaying vector
     * 
     * @param index index of the referenced element
     * @return T type of the element in the data structure
     */
    T operator[](int index){
        return this->value[index];
    }

    /**
     * @brief Encapsulates underlaying vector size
     * 
     * @return int Number of elements in vector
     */
    int size(){
        return this->value.size();
    }

    /**
     * @brief Get the Data vector stored
     *
     * @return vector<T> of the contained data
     */
    vector<T> getData()
    {
        return this->value;
    }

    /**
     * @brief Get the Shape vector
     *
     * @return vector<uint16_t> shape vector: every position is the dimension size
     */
    vector<uint16_t> getShape()
    {
        return this->shape;
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

    /** @brief
     *
     */
    void fromrandom(std::vector<uint16_t> shape={1}, int npartitions=1, int seed=42) {
        this->shape = shape;
        int num_values = 1;
        for(uint16_t i: shape){
            num_values = num_values * i;
        }
        npartitions = 2;

        std::random_device dev;
        std::mt19937 rng(seed);
        std::uniform_real_distribution<float> dist6(1,6); // distribution in range [1, 6]
        for(int k=0; k < num_values; k++){
            this->value.push_back(dist6(rng));
        }
        std::cout << "OK";
        return;
    }

    /** @brief
     *
     */
    void fromlist(std::list<T> l={}) {
        this->shape = {l.size()};
        this->value.reserve(l.size());
        this->value.assign(l.begin(), l.end());

//        for (char const &c: l) {
//            this->value.push_back(c);
//        }

        return;
    }

};