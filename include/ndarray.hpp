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
    ndarray(std::vector<std::uint16_t> lengths, T *values);    
    ndarray(std::vector<std::uint16_t> lengths, std::vector<T> values);

    public:
    // Converters
    explicit operator Images<T>();
    explicit operator Series<T>();
    
    // Operator overload
    template <class OP, class K>
    [[nodiscard]] ndarray<T> element_wise(const ndarray<K> other, OP op) const;
    template <class K>
    [[nodiscard]] ndarray<T> operator+(const ndarray<K> other) const;
    template <class K>
    [[nodiscard]] ndarray<T> operator-(const ndarray<K> other) const;
    template <class K>
    [[nodiscard]] ndarray<T> operator*(const ndarray<K> other) const;
    template <class K>
    [[nodiscard]] ndarray<T> operator/(const ndarray<K> other) const;
    [[nodiscard]] const T& operator[](const uint16_t index) const;

    // Operator wrapper
    template <class K>
    [[nodiscard]] ndarray<T> plus(const ndarray<K> other) const;
    template <class K>
    [[nodiscard]] ndarray<T> minus(const ndarray<K> other) const;
    template <class K>
    [[nodiscard]] ndarray<T> dotdivide(const ndarray<K> other) const;
    template <class K>
    [[nodiscard]] ndarray<T> dottimes(const ndarray<K> other) const;

    // vector Wrappers
    [[nodiscard]] uint16_t size() const;
    [[nodiscard]] const std::vector<T>& getValue() const;
    [[nodiscard]] const std::vector<uint16_t>& getShape() const;
    [[nodiscard]] const T& first() const;
    [[nodiscard]] auto begin() const;
    [[nodiscard]] auto end() const;

    // Utils
    [[nodiscard]] ndarray<T> getPosition(const std::vector<uint16_t> pos) const;
    [[nodiscard]] int get_current_dimension() const;
    [[nodiscard]] T *toarray() const;
    [[nodiscard]] uint16_t count() const;
    [[nodiscard]] uint16_t count(const ndarray<T> input) const;

    protected:
    [[nodiscard]] static ndarray<T> transpose(const ndarray<T> input);
    void reshape(const std::vector<uint16_t> new_shape);

    public:
    
    // Initializers
    [[nodiscard]] static ndarray<T> fromrandom(std::vector<uint16_t> shape = {2, 2}, int seed = 42);
    [[nodiscard]] static ndarray<T> fromlist(std::list<T> l = {});

    [[nodiscard]] static ndarray<T> frombinary(std::vector<uint16_t> new_shape, std::string path);

    [[nodiscard]] static ndarray<T> fromarray(std::vector<uint16_t> shape, T *input);
    [[nodiscard]] static ndarray<T> fromarray(std::vector<uint16_t> shape, std::vector<T> input);
    [[nodiscard]] static ndarray<T> fromarray(std::vector<T> input);

    // Functions
    // In place
    void clip(const T &min_value, const T &max_value);
    void map(T (*func)(T));

    // Returning
    [[nodiscard]] ndarray<T> filter(bool (*func)(T));
    [[nodiscard]] ndarray<T> filter(ndarray<T> input, bool (*func)(T));

    [[nodiscard]] ndarray<T> applyFunc(ndarray<T> input, std::function<T(ndarray<T>)> func);
    [[nodiscard]] ndarray<T> max();
    [[nodiscard]] static ndarray<T> max(ndarray<T> input);
    [[nodiscard]] ndarray<T> min();
    [[nodiscard]] static ndarray<T> min(ndarray<T> input);
    [[nodiscard]] ndarray<T> sum();
    [[nodiscard]] static ndarray<T> sum(ndarray<T> input);
    [[nodiscard]] ndarray<T> mean();
    [[nodiscard]] static ndarray<T> mean(ndarray<T> input);
    [[nodiscard]] ndarray<T> std();
    [[nodiscard]] static ndarray<T> std(ndarray<T> input);
    [[nodiscard]] ndarray<T> var();
    [[nodiscard]] static ndarray<T> var(ndarray<T> input);

};

#include "ndarray/ndarray_constructors.i.hpp"
#include "ndarray/ndarray_converters.i.hpp"
#include "ndarray/ndarray_functions.i.hpp"
#include "ndarray/ndarray_initializers.i.hpp"
#include "ndarray/ndarray_operator_overload.i.hpp"
#include "ndarray/ndarray_operator_wrapper.i.hpp"
#include "ndarray/ndarray_utils.i.hpp"
#include "ndarray/ndarray_wrapper.i.hpp"