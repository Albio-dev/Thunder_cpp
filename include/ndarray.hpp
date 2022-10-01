#pragma once

#include <algorithm>
#include <deque>
#include <forward_list>
#include <functional>
#include <iostream>
#include <list>
#include <random>
#include <type_traits>
#include <vector>

#include "images.hpp"
#include "series.hpp"

template <class T> class ndarray {

  /// @var Actual values vector
  std::vector<T> value;
  /// @var Matrix size
  std::vector<uint16_t> shape;

protected:
  // Constructors
  ndarray(const std::vector<std::uint16_t> lengths, const T *values);
  ndarray(const std::vector<std::uint16_t> lengths, const std::vector<T> values);

public:
  // Converters
  explicit operator Images<T>() const;
  explicit operator Series<T>() const;

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
  [[nodiscard]] const T &operator[](const uint16_t index) const;

  // Operator wrapper
  template <class K>[[nodiscard]] ndarray<T> plus(const ndarray<K> other) const;
  template <class K>
  [[nodiscard]] ndarray<T> minus(const ndarray<K> other) const;
  template <class K>
  [[nodiscard]] ndarray<T> dotdivide(const ndarray<K> other) const;
  template <class K>
  [[nodiscard]] ndarray<T> dottimes(const ndarray<K> other) const;

  // vector Wrappers
  [[nodiscard]] uint16_t size() const;
  [[nodiscard]] const std::vector<T> &getValue() const;
  [[nodiscard]] const std::vector<uint16_t> &getShape() const;
  [[nodiscard]] const T &first() const;
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
  [[nodiscard]] ndarray<T> reshape(const std::vector<uint16_t> new_shape) const;

public:
  // Initializers
  [[nodiscard]] static ndarray<T>
  fromrandom(const std::vector<uint16_t> shape = {2, 2}, const int seed = 42);
  [[nodiscard]] static ndarray<T> frombinary(const std::vector<uint16_t> new_shape,
                                             const std::string path);

  [[nodiscard]] static ndarray<T> fromarray(const std::vector<uint16_t> shape,
                                            const T *input);
  [[nodiscard]] static ndarray<T> fromlist(const std::vector<uint16_t> shape,
                                           const std::list<T> l = {});
  [[nodiscard]] static ndarray<T> fromlist(const std::list<T> l = {});
  [[nodiscard]] static ndarray<T> fromvector(const std::vector<uint16_t> shape,
                                             const std::vector<T> input);
  [[nodiscard]] static ndarray<T> fromvector(const std::vector<T> input);
  [[nodiscard]] static ndarray<T> fromdeque(const std::vector<uint16_t> shape,
                                            const std::deque<T> input);
  [[nodiscard]] static ndarray<T> fromdeque(const std::deque<T> input);
  [[nodiscard]] static ndarray<T> fromforward_list(const std::vector<uint16_t> shape,
                                                   const std::forward_list<T> input);
  [[nodiscard]] static ndarray<T> fromforward_list(const std::forward_list<T> input);

  // Functions
  // In place
  void clip(const T &min_value, const T &max_value);
  void map(T (*func)(T));

  // Returning
  [[nodiscard]] ndarray<T> filter(bool (*func)(T)) const;
  [[nodiscard]] ndarray<T> filter(const ndarray<T> input, bool (*func)(T)) const;

  [[nodiscard]] ndarray<T> applyFunc(const ndarray<T> input,
                                     std::function<T(ndarray<T>)> func) const;
  [[nodiscard]] ndarray<T> max() const;
  [[nodiscard]] static ndarray<T> max(const ndarray<T> input);
  [[nodiscard]] ndarray<T> min() const;
  [[nodiscard]] static ndarray<T> min(const ndarray<T> input);
  [[nodiscard]] ndarray<T> sum() const;
  [[nodiscard]] static ndarray<T> sum(const ndarray<T> input);
  [[nodiscard]] ndarray<T> mean() const;
  [[nodiscard]] static ndarray<T> mean(const ndarray<T> input);
  [[nodiscard]] ndarray<T> std() const;
  [[nodiscard]] static ndarray<T> std(const ndarray<T> input);
  [[nodiscard]] ndarray<T> var() const;
  [[nodiscard]] static ndarray<T> var(const ndarray<T> input);
};

#include "ndarray/ndarray_constructors.i.hpp"
#include "ndarray/ndarray_converters.i.hpp"
#include "ndarray/ndarray_functions.i.hpp"
#include "ndarray/ndarray_initializers.i.hpp"
#include "ndarray/ndarray_operator_overload.i.hpp"
#include "ndarray/ndarray_operator_wrapper.i.hpp"
#include "ndarray/ndarray_utils.i.hpp"
#include "ndarray/ndarray_wrapper.i.hpp"