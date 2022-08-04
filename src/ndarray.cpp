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
     * @brief Construct a new NDArray object when values are given in a C array
     * Basically a copy constructor since it copies the elements in the array in a vector
     *
     * @param lengths Dimensions vector of the resulting object
     * @param values Actual matrix values, C array format (T*)
     */
    NDArray(vector<std::uint16_t> lengths, T *values) {
// TODO: forse values può essere convertita direttamente in un vector?
        // Data checks
        if (lengths.size() == 0 || lengths[0] == 0)
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
     * @brief Construct a new NDArray object when values are already in a vector
     * Almost a move constructor, since it copies the address of both
     * vectors
     *
     * @param lengths Dimensions vector of the resulting object
     * @param values Actual matrix values, already in vector format
     */
    NDArray(vector<std::uint16_t> lengths, vector<T> values)
    {
        // Data checks
        if (lengths.size() == 0 || lengths[0] == 0)
            throw "Requested 0 dimensioned array";

        this->shape = lengths;

        uint16_t values_length = 1;
        for (uint16_t i : lengths)
            values_length = values_length * i;

        if (values.size() != values_length)
            throw "Matrix dimensions and data length mismatch";

        this->value = values;
    }

    /**
     * @brief Get the value in position given a vector with a precise location
     *
     * @param pos a vector with a position
     * @return vector<T> value referenced by pos
     */
    NDArray<T> getPosition(vector<T> pos) {

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

        if (new_shape.size() == 0)
            new_shape.push_back(1);
        return NDArray<T>(new_shape, output_temp);
    }

    /**
     * @brief Sum operation between two NDArrays
     * 
     * @param other Other NDArray summed to this one
     * @return NDArray<T> Result of sum
     */
    NDArray<T> operator+(const NDArray<T> other)
    {
        // Compatibility shape check
        if (shape != other.shape)
            throw "Array shapes don't match";

        // Output vector
        vector<T> out;


        for (unsigned int i = 0; i < value.size(); i++)
        {
            out.push_back(value[i] + other.value[i]);
        }

        return NDArray(this->shape, out);
    }

    /**
     * @brief Subtraction operation between two NDArrays
     *
     * @param other Other NDArray subtracted to this one
     * @return NDArray<T> Result of subtraction
     */
    NDArray<T> operator-(const NDArray<T> other)
    {
        // Compatibility shape check
        if (shape != other.shape)
            throw "Array shapes don't match";
        vector<T> out = {};
// TODO: forse snellire? copiare un vector in output ed eseguire l'operazione in loco
        for (unsigned int i = 0; i < value.size(); i++)
        {
            out.push_back(value[i] - other.value[i]);
        }

        return NDArray(this->shape, out);
    }

    /**
     * @brief Function to directly address the underlaying vector
     * 
     * @param index index of the referenced element
     * @return T type of the element in the data structure
     */
    T operator[](unsigned int index){
        if (index < this->value.size())
            return this->value[index];
        else
            throw "Out of bound indexing";
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
    vector<T> getValue()
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
     * @brief Dot divide a matrix with another. ToDo: Controlli grandezze array e valori siano corretti/compatibibli
     *  tipo se un valore é di tipo int e l'altro tipo uint cast di che tipo (int imo)
     *
     * @return
     */
    template<class K>
    vector<double> dotdivide(const NDArray<K> other) {
        if(shape != other.shape)
            throw "Array shapes don't match";

        vector<double> out = {};

        for(unsigned int i = 0; i < value.size(); i++){
            out.push_back(value[i]/(double)other.value[i]);
        }

        return out;
    }

    /** @brief
     *
     */
    vector<T> dottimes(const NDArray<T> other)
    {
        if (shape != other.shape)
            throw "Array shapes don't match";

        vector<T> out = {};

        for (unsigned int i = 0; i < value.size(); i++)
        {
            out.push_back(value[i] * other.value[i]);
        }
    }

    // TODO: errore di compilazione     parameter ‘npartitions’ set but not used [-Werror=unused-but-set-parameter]
    /*
    void fromrandom(std::vector<uint16_t> shape={1}, int npartitions=1, int seed=42) {
        this->shape = shape;
        int num_values = 1;
        for(uint16_t i: shape){
            num_values = num_values * i;
        }
        npartitions = 2;

        std::random_device dev;
        std::mt19937 rng(seed);
        std::uniform_real_distribution<float> dist6(1, 6); // distribution in range [1, 6]
        for (int k = 0; k < num_values; k++)
        {
            this->value.push_back(dist6(rng));
        }
        std::cout << "OK";
        return;
    }*/

    

    /**
     * @brief Dot function a matrix with another.
     *
     * @return
     */
    template <class OP>
    vector<T> element_wise(const NDArray<T> other, OP op)
    {
        if (shape != other.shape)
            throw "Array shapes don't match";
        vector<T> out = {};

        for (unsigned int i = 0; i < value.size(); i++)
        {
            out.push_back(op(value[i], other.value[i]));
        }

        return out;
    }


    /**
     * @brief Clip values in an array above and below provided values
     *
     * @param min_value min value to clip
     * @param max_value max value to clip
     */
    void clip(const T& min_value, const T& max_value) {
                
        transform(std::begin(value), std::end(value), std::begin(value),
                       [&] (const T& v) { return clamp(v, min_value, max_value); });
    }

    /**
     * @brief Retrieves first element if matrix
     * 
     * @return T First value
     */
    T first()
    {
        return this->value[0];
    }

    /**
     * @brief Function to keep interface consistent. Just a pointwise sum
     * 
     * @param other Structure to sum to caller
     * @return NDArray<T> Object result of sum
     */
    NDArray<T> plus(NDArray<T> other){
        return *this + other;
    }

    /**
     * @brief Function to keep interface consistent. Just a pointwise subtraction
     *
     * @param other Structure to subtract to caller
     * @return NDArray<T> Object result of subtraction
     */
    NDArray<T> minus(NDArray<T> other)
    {
        return *this - other;
    }

// TODO: Output object o in place? (come clip)
// TODO: scorrere più dimensioni (value_shape)?
    /**
     * @brief Applied the supplied function to every element in matrix
     * 
     * @param func Unary function 
     * @return NDArray<T> Structure with result
     */
    NDArray<T> map(T (*func)(T))
    {
        //transform(std::begin(value), std::end(value), value.begin(), func);
        vector<T> output = value;
        output.reserve(this->value.size());
        transform(output.begin(), output.end(), output.begin(), func);
        
        return NDArray(this->shape, output);
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

    /**
     * @brief Extract the underlaying array
     * 
     * @return T* pointer to start of array (same as contained vector)
     */
    T *toarray(){
        return &(this->value)[0];
    }

    

    /**
     * @brief Count how many elements there are in every matrix along the first dimension
     *
     * @return multiplication of dimension sizes except first
     */
    int count()
    {
        // Multiplication of elements indexed [1 .. shape.size())
        int size = 1;
        for (unsigned int i = 1; i < shape.size(); i++)
            size *= shape[i];
        return size;
    }

    /**
     * @brief Applies a function which should evaluate to boolean, along the first axis
     *
     * @param func A function that accepts data of type NDArray<T>
     * @return NDArray<T> Filtered data
     */
    NDArray<T> filter(bool (*func)(NDArray<T>)){
        int count = 0;
        vector<T> output;

        // Cycling through the first dimension
        for (int i = 0; i < shape[0]; i++){
            NDArray<T> temp = this->getPosition({i});
            if (func(temp))
            {
                for (int j = 0; j < temp.size(); j++){
                    output.push_back(temp[j]);
                }
                //output.insert(output.end(), temp.getValue().begin(), temp.getValue().end());
                count++;
            }
        }

        // Generating new shape. Overwrites only first dimension
        vector<uint16_t> new_shape = this->shape;
        if (count == 0)
            new_shape = {0};
        else
            new_shape[0] = count;

        return NDArray(new_shape, output);
    }

    T max()
    {
        return max(this->value);
    }
    T min()
    {
        return min(this->value);
    }
    T mean()
    {
        return this->sum() / value.size();
    }
    T sum(){
        // return sum = accumulate(value.begin(), value.end(), 0.0); old with error
        return accumulate(value.begin(), value.end(), 0.0);
    }
    T std(){
        double sq_sum = inner_product(value.begin(), value.end(), value.begin(), 0.0);
        return sqrt(sq_sum / value.size() - mean() * mean());
    }
    T var()
    {
        double sq_sum = inner_product(value.begin(), value.end(), value.begin(), 0.0);
        return sq_sum / value.size() - mean() * mean();
    }
    
};