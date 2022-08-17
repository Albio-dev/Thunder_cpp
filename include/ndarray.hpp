#pragma once

#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
#include <list>
#include <random>
#include <type_traits>

#include "series.hpp"
#include "images.hpp"

template <class T>
class ndarray{
    
    
    /// @var Actual values vector
    std::vector<T> value;
    /// @var Matrix size
    std::vector<uint16_t> shape;

    protected:

    // Constructors
    /**
     * @brief Construct a new ndarray object when values are given in a C array
     * Basically a copy constructor since it copies the elements in the array in a vector
     *
     * @param lengths Dimensions vector of the resulting object
     * @param values Actual matrix values, C array format (T*)
     */
    ndarray(std::vector<std::uint16_t> lengths, T *values);
    /**
     * @brief Construct a new ndarray object when values are already in a vector
     * Almost a move constructor, since it copies the address of both
     * vectors
     *
     * @param lengths Dimensions vector of the resulting object
     * @param values Actual matrix values, already in vector format
     */
    ndarray(std::vector<std::uint16_t> lengths, std::vector<T> values);

    public:

    // Converters
    operator Images<T>();
    operator Series<T>();
    

    // Operator overload
    /**
     * @brief Dot function a matrix with another.
     *
     * @return
     */
    template <class OP, class K>
    ndarray<T> element_wise(const ndarray<K> other, OP op);
    template <class K>
    ndarray<T> operator+(const ndarray<K> other);
    /**
     * @brief Subtraction operation between two ndarrays
     *
     * @param other Other ndarray subtracted to this one
     * @return ndarray<T> Result of subtraction
     */
    template <class K>
    ndarray<T> operator-(const ndarray<K> other);
    template <class K>
    ndarray<T> operator*(const ndarray<K> other);
    template <class K>
    ndarray<T> operator/(const ndarray<K> other);
    /**
     * @brief Function to directly address the underlaying vector
     *
     * @param index index of the referenced element
     * @return T type of the element in the data structure
     */
    T operator[](unsigned int index);

    // Operator wrapper
    template <class K>
    ndarray<T> plus(ndarray<K> other);

    template <class K>
    ndarray<T> minus(ndarray<K> other);
    /**
     * @brief Dot divide a matrix with another. ToDo: Controlli grandezze array e valori siano corretti/compatibibli
     *  tipo se un valore é di tipo int e l'altro tipo uint cast di che tipo (int imo)
     *
     * @return
     */
    template <class K>
    ndarray<T> dotdivide(const ndarray<K> other);
    /** @brief Given two ndarray with the same shape. Multiply one element in position n with his corresponding
     * elem in position n.
     *
     * @param other second element of multiplication
     * @return out a vector with multiplied values
     */
    template <class K>
    ndarray<T> dottimes(const ndarray<K> other);

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
    ndarray<T> getPosition(std::vector<uint16_t> pos);
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
    int count(ndarray<T> input);
    static ndarray<T> transpose(ndarray<T> input);
    void reshape(std::vector<uint16_t> new_shape);

    // Initializers
     /** @brief Initialize with random values this->value
     *
     * @param shape a vector with the desired dimension
     * @param seed seed value for the random function
     */
    static ndarray<T> fromrandom(std::vector<uint16_t> shape = {2, 2}, int seed = 42);
    /**
     * @brief Passed a list assign all values to current data structure
     * as one dimensional matrix.
     *
     */
    static ndarray<T> fromlist(std::list<T> l = {});
    // ToDo: https://en.cppreference.com/w/cpp/filesystem/path
    /** @brief Read a file as is to the class with some checks on possible errors
     *
     * @param shape a vector with the desired dimension
     * @param path path to a file
     */
    static ndarray<T> frombinary(std::vector<uint16_t> new_shape, std::string path);
    
    static ndarray<T> fromarray(std::vector<uint16_t> shape, T *input);
    static ndarray<T> fromarray(std::vector<uint16_t> shape, std::vector<T> input);
    static ndarray<T> fromarray(std::vector<T> input);

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
     * @return ndarray<T> Structure with result
     */
    void map(T (*func)(T));



    /**
     * @brief Applies a function which should evaluate to boolean, along the first axis
     *
     * @param func A function that accepts data of type ndarray<T>
     * @return ndarray<T> Filtered data
     */
    ndarray<T> filter(bool (*func)(T));
    ndarray<T> filter(ndarray<T> input, bool (*func)(T));
    ndarray<T> applyFunc(ndarray<T> input, std::function<T(ndarray<T>)> func);
    /**
     * @brief Returns a vector of max values.
     * If matrix is monodimensional returns a single max value, if there is more than a
     * dimension, it cycles through the first returning the maximum along all other dimensions.
     *
     * @return ndarray<T> Structure containing the vector of maximum value(s)
     */
    ndarray<T> max();
    static ndarray<T> max(ndarray<T> input);
    /**
     * @brief Returns a vector of min values.
     * If matrix is monodimensional returns a single min value, if there is more than a
     * dimension, it cycles through the first returning the minimum along all other dimensions.
     *
     * @return ndarray<T> Structure containing the vector of minimum value(s)
     */
    ndarray<T> min();
    static ndarray<T> min(ndarray<T> input);
    /**
     * @brief Returns a vector of sum values.
     * If matrix is monodimensional returns a single sum value, if there is more than a
     * dimension, it cycles through the first returning the sum along all other dimensions.
     *
     * @return ndarray<T> Structure containing the vector of sum value(s)
     */
    ndarray<T> sum();
    static ndarray<T> sum(ndarray<T> input);
    /**
     * @brief Returns a vector of mean values.
     * If matrix is monodimensional returns a single mean value, if there is more than a
     * dimension, it cycles through the first returning the mean along all other dimensions.
     *
     * @return ndarray<T> Structure containing the vector of mean value(s)
     */
    ndarray<T> mean();
    static ndarray<T> mean(ndarray<T> input);
    /**
     * @brief Returns a vector of standard deviation values.
     * If matrix is monodimensional returns a single standard deviation value, if there is more than a
     * dimension, it cycles through the first returning the standard deviation along all other dimensions.
     *
     * @return ndarray<T> Structure containing the vector of standard deviation value(s)
     */

    ndarray<T> std();
    static ndarray<T> std(ndarray<T> input);
    /**
     * @brief Returns a vector of variance values.
     * If matrix is monodimensional returns a single variance value, if there is more than a
     * dimension, it cycles through the first returning the variance along all other dimensions.
     *
     * @return ndarray<T> Structure containing the vector of variance value(s)
     */
    ndarray<T> var();
    static ndarray<T> var(ndarray<T> input);

};

#include "ndarray/ndarray_constructors.i.hpp"
#include "ndarray/ndarray_converters.i.hpp"
#include "ndarray/ndarray_functions.i.hpp"
#include "ndarray/ndarray_initializers.i.hpp"
#include "ndarray/ndarray_operator_overload.i.hpp"
#include "ndarray/ndarray_operator_wrapper.i.hpp"
#include "ndarray/ndarray_utils.i.hpp"
#include "ndarray/ndarray_wrapper.i.hpp"