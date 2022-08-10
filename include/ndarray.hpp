#pragma once

#include <vector>
#include <functional>
#include <iostream>
#include <list>

#include "series.hpp"
#include "images.hpp"

template <typename T>
class NDArray{
    public:
    
    /// @var Actual values vector
    std::vector<T> value;
    /// @var Matrix size
    std::vector<uint16_t> shape;

    uint16_t dimCount;

    // COnstructors
    /**
     * @brief Construct a new NDArray object when values are given in a C array
     * Basically a copy constructor since it copies the elements in the array in a vector
     *
     * @param lengths Dimensions vector of the resulting object
     * @param values Actual matrix values, C array format (T*)
     */
    NDArray(std::vector<std::uint16_t> lengths, T *values);
    /**
     * @brief Construct a new NDArray object when values are already in a vector
     * Almost a move constructor, since it copies the address of both
     * vectors
     *
     * @param lengths Dimensions vector of the resulting object
     * @param values Actual matrix values, already in vector format
     */
    NDArray(std::vector<std::uint16_t> lengths, std::vector<T> values);

    // Converters
    operator Images<T>();
    operator Series<T>();
    

    // Operator overload
    /**
     * @brief Dot function a matrix with another.
     *
     * @return
     */
    template <class OP>
    NDArray<T> element_wise(const NDArray<T> other, OP op);
    NDArray<T> operator+(const NDArray<T> other);
    /**
     * @brief Subtraction operation between two NDArrays
     *
     * @param other Other NDArray subtracted to this one
     * @return NDArray<T> Result of subtraction
     */
    NDArray<T> operator-(const NDArray<T> other);
    NDArray<T> operator*(const NDArray<T> other);
    NDArray<T> operator/(const NDArray<T> other);
    /**
     * @brief Function to directly address the underlaying vector
     *
     * @param index index of the referenced element
     * @return T type of the element in the data structure
     */
    T operator[](unsigned int index);

    // vector Wrapper
    /**
     * @brief Encapsulates underlaying vector size
     *
     * @return int Number of elements in vector
     */
    int size();
    uint16_t getCount();
    /**
     * @brief Get the Data vector stored
     *
     * @return vector<T> of the contained data
     */
    std::vector<T> getValue();
    /**
     * @brief Get the Shape vector
     *
     * @return vector<uint16_t> shape vector: every position is the dimension size
     */
    std::vector<uint16_t> getShape();
    T first();
    auto begin();
    auto end();

    // Utils
    /**
     * @brief Get the value in position given a vector with a precise location
     *
     * @param pos a vector with a position
     * @return vector<T> value referenced by pos
     */
    NDArray<T> getPosition(std::vector<uint16_t> pos);
    /**
     * @brief Check if shape is correct or plausibile and return number of elements
     *
     * @return values_length Number of elements in vector
     */
    int get_current_dimension();
    /**
     * @brief Extract the underlaying array
     *
     * @return T* pointer to start of array (same as contained vector)
     */
    T *toarray();
    /**
     * @brief Count how many elements there are in every matrix along the first dimension
     *
     * @return multiplication of dimension sizes except first
     */
    int count();
    int count(NDArray<T> input);
    static NDArray<T> transpose(NDArray<T> input);
    void reshape(std::vector<uint16_t> new_shape);

     /** @brief Initialize with random values this->value
     *
     * @param shape a vector with the desired dimension
     * @param seed seed value for the random function
     */
    void fromrandom(std::vector<uint16_t> shape = {2, 2}, int seed = 42);
    /**
     * @brief Passed a list assign all values to current data structure
     * as one dimensional matrix.
     *
     */
    void fromlist(std::list<T> l = {});
    // ToDo: https://en.cppreference.com/w/cpp/filesystem/path
    /** @brief Read a file as is to the class with some checks on possible errors
     *
     * @param shape a vector with the desired dimension
     * @param path path to a file
     */
    void frombinary(std::vector<uint16_t> new_shape, std::string path);

    // Operator wrapper
    template <class K>
    NDArray<T> plus(NDArray<K> other);

    template <class K>
    NDArray<T> minus(NDArray<K> other);
    /**
     * @brief Dot divide a matrix with another. ToDo: Controlli grandezze array e valori siano corretti/compatibibli
     *  tipo se un valore é di tipo int e l'altro tipo uint cast di che tipo (int imo)
     *
     * @return
     */
    template <class K>
    NDArray<T> dotdivide(const NDArray<K> other);
    /** @brief Given two NDArray with the same shape. Multiply one element in position n with his corresponding
     * elem in position n.
     *
     * @param other second element of multiplication
     * @return out a vector with multiplied values
     */
    template <class K>
    NDArray<T> dottimes(const NDArray<K> other);

    /**
     * @brief Clip values in an array above and below provided values
     *
     * @param min_value min value to clip
     * @param max_value max value to clip
     */
    void clip(const T &min_value, const T &max_value);
    /**
     * @brief Applied the supplied function to every element in matrix
     *
     * @param func Unary function
     * @return NDArray<T> Structure with result
     */
    void map(T (*func)(T));



    /**
     * @brief Applies a function which should evaluate to boolean, along the first axis
     *
     * @param func A function that accepts data of type NDArray<T>
     * @return NDArray<T> Filtered data
     */
    NDArray<T> filter(bool (*func)(NDArray<T>));
    NDArray<T> filter(NDArray<T> input, bool (*func)(NDArray<T>));
    NDArray<T> applyFunc(NDArray<T> input, std::function<T(NDArray<T>)> func);
    /**
     * @brief Returns a vector of max values.
     * If matrix is monodimensional returns a single max value, if there is more than a
     * dimension, it cycles through the first returning the maximum along all other dimensions.
     *
     * @return NDArray<T> Structure containing the vector of maximum value(s)
     */
    NDArray<T> max();
    static NDArray<T> max(NDArray<T> input);
    /**
     * @brief Returns a vector of min values.
     * If matrix is monodimensional returns a single min value, if there is more than a
     * dimension, it cycles through the first returning the minimum along all other dimensions.
     *
     * @return NDArray<T> Structure containing the vector of minimum value(s)
     */
    NDArray<T> min();
    static NDArray<T> min(NDArray<T> input);
    /**
     * @brief Returns a vector of sum values.
     * If matrix is monodimensional returns a single sum value, if there is more than a
     * dimension, it cycles through the first returning the sum along all other dimensions.
     *
     * @return NDArray<T> Structure containing the vector of sum value(s)
     */
    NDArray<T> sum();
    static NDArray<T> sum(NDArray<T> input);
    /**
     * @brief Returns a vector of mean values.
     * If matrix is monodimensional returns a single mean value, if there is more than a
     * dimension, it cycles through the first returning the mean along all other dimensions.
     *
     * @return NDArray<T> Structure containing the vector of mean value(s)
     */
    NDArray<T> mean();
    static NDArray<T> mean(NDArray<T> input);
    /**
     * @brief Returns a vector of standard deviation values.
     * If matrix is monodimensional returns a single standard deviation value, if there is more than a
     * dimension, it cycles through the first returning the standard deviation along all other dimensions.
     *
     * @return NDArray<T> Structure containing the vector of standard deviation value(s)
     */

    NDArray<T> std();
    static NDArray<T> std(NDArray<T> input);
    /**
     * @brief Returns a vector of variance values.
     * If matrix is monodimensional returns a single variance value, if there is more than a
     * dimension, it cycles through the first returning the variance along all other dimensions.
     *
     * @return NDArray<T> Structure containing the vector of variance value(s)
     */
    NDArray<T> var();
    static NDArray<T> var(NDArray<T> input);

};