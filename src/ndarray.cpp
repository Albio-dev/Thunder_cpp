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

    uint16_t dimCount;

    /**
     * @brief Construct a new NDArray object
     */
    //NDArray() = default;
    virtual ~NDArray() = default;

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

        this->dimCount = count();
    }

    /**
     * @brief Construct a new NDArray object when values are already in a vector
     * Almost a move constructor, since it copies the address of both
     * vectors
     *
     * @param lengths Dimensions vector of the resulting object
     * @param values Actual matrix values, already in vector format
     */
    NDArray(vector<std::uint16_t> lengths, vector<T> values) {
        // Data checks
        if (lengths.size() == 0 || lengths[0] == 0)
            throw "Requested 0 dimensioned array";

        this->shape = lengths;

        uint16_t values_length = 1;
        for (uint16_t i: lengths)
            values_length = values_length * i;

        if (values.size() != values_length)
            throw "Matrix dimensions and data length mismatch";

        this->value = values;

        this->dimCount = count();
    }

    operator Series<T>() {
        return Series<T>(shape, value);
    }

    /**
     * @brief Get the value in position given a vector with a precise location
     *
     * @param pos a vector with a position
     * @return vector<T> value referenced by pos
     */
    NDArray<T> getPosition(vector<uint16_t> pos) {

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
            for (unsigned int k = shape.size() - 1; k != i; k--) {
                subDimensionSize *= shape[k];
            }

            // Shift index by input * chunk size
            startIndex = startIndex + pos[i] * subDimensionSize;

        }

        vector<uint16_t> new_shape;
        // Starting from the missing dimension calculates the size of the identified matrix
        int endindex = 1;
        for (unsigned int i = lastdim; i < shape.size(); i++) {
            endindex *= shape[i];
            new_shape.push_back(shape[i]);
        }
        endindex += startIndex;

        // Temporary output structure
        vector<T> output_temp;

        // Extract data in range
        do {
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
    NDArray<T> operator+(const NDArray<T> other) {
        // Compatibility shape check
        if (shape != other.shape)
            throw "Array shapes don't match";

        // Output vector
        vector<T> out;


        for (unsigned int i = 0; i < value.size(); i++) {
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
    NDArray<T> operator-(const NDArray<T> other) {
        // Compatibility shape check
        if (shape != other.shape)
            throw "Array shapes don't match";
        vector<T> out;
// TODO: forse snellire? copiare un vector in output ed eseguire l'operazione in loco
        for (unsigned int i = 0; i < value.size(); i++) {
            out.push_back(value[i] - other.value[i]);
        }

        return NDArray(this->shape, out);
    }

    NDArray<T> operator*(const NDArray<T> other) {
        // Compatibility shape check
        if (shape != other.shape)
            throw "Array shapes don't match";
        vector<T> out;
// TODO: forse snellire? copiare un vector in output ed eseguire l'operazione in loco
        for (unsigned int i = 0; i < value.size(); i++) {
            out.push_back(value[i] * other.value[i]);
        }

        return NDArray(this->shape, out);
    }

    NDArray<T> operator/(const NDArray<T> other) {
        // Compatibility shape check
        if (shape != other.shape)
            throw "Array shapes don't match";
        vector<T> out;
// TODO: forse snellire? copiare un vector in output ed eseguire l'operazione in loco
        for (unsigned int i = 0; i < value.size(); i++) {
            out.push_back(value[i] / other.value[i]);
        }

        return NDArray(this->shape, out);
    }

    /**
     * @brief Function to directly address the underlaying vector
     * 
     * @param index index of the referenced element
     * @return T type of the element in the data structure
     */
    T operator[](unsigned int index) {
        if (index < this->value.size())
            return this->value[index];
        else
            throw "Out of bound indexing";
    }

/*
    ostream& operator<<(ostream& stream, const NDArray& a){
        for 

    }
*/
    /**
     * @brief Encapsulates underlaying vector size
     * 
     * @return int Number of elements in vector
     */
    int size() {
        return this->value.size();
    }

    uint16_t getCount(){
        return this->dimCount;
    }

    /**
     * @brief Get the Data vector stored
     *
     * @return vector<T> of the contained data
     */
    vector<T> getValue() {
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
     * @brief Dot divide a matrix with another. ToDo: Controlli grandezze array e valori siano corretti/compatibibli
     *  tipo se un valore é di tipo int e l'altro tipo uint cast di che tipo (int imo)
     *
     * @return
     */
    template<class K>
    vector<double> dotdivide(const NDArray<K> other) {
        if (shape != other.shape)
            throw "Array shapes don't match";

        vector<double> out = {};

        for (unsigned int i = 0; i < value.size(); i++) {
            out.push_back(value[i] / (double) other.value[i]);
        }

        return out;
    }

    /** @brief Given two NDArray with the same shape. Multiply one element in position n with his corresponding
     * elem in position n.
     *
     * @param other second element of multiplication
     * @return out a vector with multiplied values
     */
    vector<T> dottimes(const NDArray<T> other) {
        if (shape != other.shape)
            throw "Array shapes don't match";

        vector<T> out = {};

        for (unsigned int i = 0; i < value.size(); i++) {
            out.push_back(value[i] * other.value[i]);
        }

        return out;
    }

    /** @brief Initialize with random values this->value
     *
     * @param shape a vector with the desired dimension
     * @param seed seed value for the random function
     */
    void fromrandom(std::vector<uint16_t> shape = {2, 2}, int seed = 42) {
        this->shape = shape;
        this->value.clear();
        int num_values = get_current_dimension();

        // ToDo: Works only with float values not int
        std::random_device dev;
        std::default_random_engine rng(seed);
        std::uniform_real_distribution<T> dist6(1, 100);
        for (int k = 0; k < num_values; k++) {
            this->value.push_back(dist6(rng));
        }

        return;
    }


    /**
     * @brief Dot function a matrix with another.
     *
     * @return
     */
    template<class OP>
    vector<T> element_wise(const NDArray<T> other, OP op) {
        if (shape != other.shape)
            throw "Array shapes don't match";
        vector<T> out = {};

        for (unsigned int i = 0; i < value.size(); i++) {
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
    void clip(const T &min_value, const T &max_value) {

        transform(std::begin(value), std::end(value), std::begin(value),
                  [&](const T &v) { return clamp(v, min_value, max_value); });
    }

    /**
     * @brief Retrieves first element if matrix
     * 
     * @return T First value
     */
    T first() {
        return this->value[0];
    }

    auto begin() {
        return value.begin();
    }

    auto end() {
        return value.end();
    }

    /**
     * @brief Function to keep interface consistent. Just a pointwise sum
     * 
     * @param other Structure to sum to caller
     * @return NDArray<T> Object result of sum
     */
    NDArray<T> plus(NDArray<T> other) {
        return *this + other;
    }

    /**
     * @brief Function to keep interface consistent. Just a pointwise subtraction
     *
     * @param other Structure to subtract to caller
     * @return NDArray<T> Object result of subtraction
     */
    NDArray<T> minus(NDArray<T> other) {
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
    NDArray<T> map(T (*func)(T)) {
        //transform(std::begin(value), std::end(value), value.begin(), func);
        vector<T> output = value;
        output.reserve(this->value.size());
        transform(output.begin(), output.end(), output.begin(), func);

        return NDArray(this->shape, output);
    }


    /**
     * @brief Passed a list assign all values to current data structure
     * as one dimensional matrix.
     *
     */
    void fromlist(std::list<T> l = {}) {
        if (l.size() == 0)
            throw "List empty. Need to have a non empty list assigned.";

        this->shape = {l.size()};
        this->value.reserve(l.size());
        this->value.assign(l.begin(), l.end());

        return;
    }

    /**
     * @brief Extract the underlaying array
     * 
     * @return T* pointer to start of array (same as contained vector)
     */
    T *toarray(){
        vector<T> new_value = value;
        return &(new_value)[0];
    }

// TODO: To be protected, internal function
    static NDArray<T> transpose(NDArray<T> input){

        if (input.getShape().size() != 2){
            throw "Wrong size for transposition. Expected NxM";
        }

        uint16_t N = input.getShape()[0];
        uint16_t M = input.getShape()[1];
        int size = (N * M);

// TODO: attenzione allo 0 per altri tipi
        vector<T> output(size, 0);

        for (uint16_t i = 0; i < size; i++){
            output[i] = input[M * (i % N) + (i / N)];
        }

        return NDArray<T>({M, N}, output);
    }

    void reshape(vector<uint16_t> new_shape)
    {
        shape = new_shape;
    }

    /**
     * @brief Count how many elements there are in every matrix along the first dimension
     *
     * @return multiplication of dimension sizes except first
     */
    int count() {
        // Multiplication of elements indexed [1 .. shape.size())
        int size = 1;
        for (unsigned int i = 1; i < shape.size(); i++)
            size *= shape[i];
        return size;
    }
    int count(NDArray<T> input){
        return input.count();
    }

    /**
     * @brief Applies a function which should evaluate to boolean, along the first axis
     *
     * @param func A function that accepts data of type NDArray<T>
     * @return NDArray<T> Filtered data
     */
    NDArray<T> filter(bool (*func)(NDArray<T>)) {
        int count = 0;
        vector<T> output;

        // Cycling through the first dimension
        for (uint16_t i = 0; i < shape[0]; i++) {
            NDArray<T> temp = this->getPosition({i});
            if (func(temp)) {
                for (int j = 0; j < temp.size(); j++) {
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

    NDArray<T> filter(NDArray<T> input, bool (*func)(NDArray<T>))
    {
        return input.filter(func);
    }

    /**
     * @brief Returns a vector of max values.
     * If matrix is monodimensional returns a single max value, if there is more than a 
     * dimension, it cycles through the first returning the maximum along all other dimensions.
     * 
     * @return NDArray<T> Structure containing the vector of maximum value(s)
     */
    NDArray<T> max() {
        vector<T> output;
        vector<uint16_t> new_shape;

        // Single dimension case
        if (shape.size() == 1) {
            // The maximum along the only dimension present
            output.push_back(*max_element(value.begin(), value.end()));
            new_shape = {1};
        } else {
            for (uint16_t i = 0; i < shape[0]; i++) {
                // Extract all other dimensions
                NDArray<T> temp = this->getPosition({i});
                // Append maximum along those dimensions
                output.push_back(*max_element(temp.begin(), temp.end()));

                new_shape = {shape[0]};
            }
        }

        return NDArray(new_shape, output);
    }
    static NDArray<T> max(NDArray<T> input){
        return input.max();
    }
    /**
     * @brief Returns a vector of min values.
     * If matrix is monodimensional returns a single min value, if there is more than a 
     * dimension, it cycles through the first returning the minimum along all other dimensions.
     * 
     * @return NDArray<T> Structure containing the vector of minimum value(s)
     */
    NDArray<T> min() {
        vector<T> output;
        vector<uint16_t> new_shape;

        // Single dimension case
        if (shape.size() == 1) {
            // The minimum along the only dimension present
            output.push_back(*min_element(value.begin(), value.end()));
            new_shape = {1};
        } else {
            for (uint16_t i = 0; i < shape[0]; i++) {
                // Extract all other dimensions
                NDArray<T> temp = this->getPosition({i});
                // Append minimum along those dimensions                
                output.push_back(*min_element(temp.begin(), temp.end()));

                new_shape = {shape[0]};
            }
        }

        return NDArray(new_shape, output);
    }
    static NDArray<T> min(NDArray<T> input)
    {
        return input.min();
    }

    /**
     * @brief Returns a vector of sum values.
     * If matrix is monodimensional returns a single sum value, if there is more than a 
     * dimension, it cycles through the first returning the sum along all other dimensions.
     * 
     * @return NDArray<T> Structure containing the vector of sum value(s)
     */
    NDArray<T> sum() {
        vector<T> output;
        vector<uint16_t> new_shape;

        // Single dimension case
        if (shape.size() == 1) {
            // The sum along the only dimension present
            output.push_back(accumulate(value.begin(), value.end(), 0.0));
            new_shape = {1};
        } else {
            for (uint16_t i = 0; i < shape[0]; i++) {
                // Extract all other dimensions
                NDArray<T> temp = this->getPosition({i});
                // Append sum along those dimensions                
                output.push_back(accumulate(temp.begin(), temp.end(), 0.0));

                new_shape = {shape[0]};
            }
        }

        return NDArray(new_shape, output);
    }
    static NDArray<T> sum(NDArray<T> input)
    {
        return input.sum();
    }

    /**
     * @brief Returns a vector of mean values.
     * If matrix is monodimensional returns a single mean value, if there is more than a 
     * dimension, it cycles through the first returning the mean along all other dimensions.
     * 
     * @return NDArray<T> Structure containing the vector of mean value(s)
     */
    NDArray<T> mean() {
        vector<T> output;
        vector<uint16_t> new_shape;

        // Single dimension case
        if (shape.size() == 1) {
            // The mean along the only dimension present
            output.push_back(accumulate(value.begin(), value.end(), 0.0) / shape[0]);
            new_shape = {1};
        } else {
            for (uint16_t i = 0; i < shape[0]; i++) {
                // Extract all other dimensions
                NDArray<T> temp = this->getPosition({i});
                // Append mean along those dimensions                
                output.push_back(accumulate(temp.begin(), temp.end(), 0.0) / count());

                new_shape = {shape[0]};
            }
        }

        return NDArray(new_shape, output);
    }
    static NDArray<T> mean(NDArray<T> input)
    {
        return input.mean();
    }

    /**
     * @brief Returns a vector of standard deviation values.
     * If matrix is monodimensional returns a single standard deviation value, if there is more than a 
     * dimension, it cycles through the first returning the standard deviation along all other dimensions.
     * 
     * @return NDArray<T> Structure containing the vector of standard deviation value(s)
     */
    NDArray<T> std() {
        vector<T> output;
        vector<uint16_t> new_shape;

        // Single dimension case
        if (shape.size() == 1) {
            // The standard deviation along the only dimension present
            T total = 0;
            for (int i = 0; i < shape[0]; i++) {
                total += (value[i] - mean()[0]) * (value[i] - mean()[0]);
            }
            output.push_back(sqrt(total / (shape[0] - 1)));
            new_shape = {1};
        } else {
            for (uint16_t i = 0; i < shape[0]; i++) {
                // Extract all other dimensions
                NDArray<T> temp = this->getPosition({i});
                T total = 0;
                for (int j = 0; j < getCount(); j++)
                {
                    total += (temp[j] - mean()[i]) * (temp[j] - mean()[i]);
                }
                output.push_back((T) sqrt(total / getCount()/*((getCount() == 1) ? (getCount()) : (getCount() - 1))*/));
                // Append standard deviation along those dimensions

                new_shape = {shape[0]};
            }
        }

        return NDArray(new_shape, output);
    }
    static NDArray<T> std(NDArray<T> input)
    {
        return input.std();
    }

    /**
     * @brief Returns a vector of variance values.
     * If matrix is monodimensional returns a single variance value, if there is more than a
     * dimension, it cycles through the first returning the variance along all other dimensions.
     *
     * @return NDArray<T> Structure containing the vector of variance value(s)
     */
    NDArray<T> var() {
        vector<T> output;
        vector<uint16_t> new_shape;

        // Single dimension case
        if (shape.size() == 1) {
            // The standard deviation along the only dimension present
            T total = 0;
            for (int i = 0; i < shape[0]; i++) {
                total += (value[i] - mean()[0]) * (value[i] - mean()[0]);
            }
            output.push_back(total / (shape[0] - 1));
            new_shape = {1};
        } else {
            for (uint16_t i = 0; i < shape[0]; i++) {
                // Extract all other dimensions
                NDArray<T> temp = this->getPosition({i});
                T total = 0;
                for (int j = 0; j < count(); j++) {
                    total += (temp[j] - mean()[i]) * (temp[j] - mean()[i]);
                }
                output.push_back(total / (count()/* - 1*/));
                // Append standard deviation along those dimensions

                new_shape = {shape[0]};
            }
        }

        return NDArray(new_shape, output);
    }
    static NDArray<T> var(NDArray<T> input)
    {
        return input.var();
    }

    /**
     * @brief Check if shape is correct or plausibile and return number of elements
     *
     * @return values_length Number of elements in vector
     */
    int get_current_dimension() {
        if (this->shape.size() == 0 || this->shape[0] == 0)
            throw "Requested 0 dimensioned array";

        int values_length = 1;
        for (int i: this->shape){
            if( i < 1)
                throw "One or more dimension less than 1";

            values_length = values_length * i;
        }

        return values_length;
    }

    // ToDo: https://en.cppreference.com/w/cpp/filesystem/path
    /** @brief Read a file as is to the class with some checks on possible errors
     *
     * @param shape a vector with the desired dimension
     * @param path path to a file
     */
    void frombinary(std::vector<uint16_t> new_shape, std::string path) {
        this->shape = new_shape;

        std::ifstream file(path, std::ios::in | std::ios::binary);
        if (!file.is_open())
            throw "Can't open file. Some error occurred.";

        // Disables skipping of leading whitespace by the formatted input functions
        // https://en.cppreference.com/w/cpp/io/manip/skipws
        file.unsetf(std::ios::skipws);

        std::streampos fileSize;
        file.seekg(0, std::ios::end);
        fileSize = file.tellg();
        file.seekg(0, std::ios::beg);

        // reserve capacity in vector
        int dimension = (int) (fileSize / sizeof(T));
        // Maybe I should use this code for file.read directly on this->value
        //this->value.reserve(dimension);

        if (NDArray<T>::get_current_dimension() != dimension)
            throw "File is larger or shorter then expected.";

        std::vector<T> vec(fileSize / sizeof(T));
        file.read(reinterpret_cast<char *>(vec.data()), vec.size() * sizeof(T));

        this->value = vec;

        return;
    }
};