#include "../ndarray.hpp"

/**
 * @brief Clip ndarray above and below provided values
 * and stores the result in place
 *
 * @tparam T Underlaying data type
 * @param min_value Minimum allowed value
 * @param max_value Maximum allowed value
 */
template <class T>
void ndarray<T>::clip(const T &min_value, const T &max_value) {
  transform(std::begin(value), std::end(value), std::begin(value),
            [&](const T &v) { return std::clamp(v, min_value, max_value); });
}

/**
 * @brief Applies the supplied unary function to every element in matrix
 * and stores the result in place
 *
 * @tparam T Underlaying data type
 * @param func Unary function
 */
template <class T> void ndarray<T>::map(T (*func)(T)) {
  std::transform(std::begin(value), std::end(value), value.begin(), func);
}
/**
 * @brief For every element evaluates a function to boolean and keeps the value
 * when true
 *
 * @tparam T Underlaying data type
 * @param func Unary boolean function
 * @return ndarray<T> Values that evaluates to true
 */
template <class T> ndarray<T> ndarray<T>::filter(bool (*func)(T)) const{
  std::vector<T> output;
  std::vector<uint16_t> new_shape;

  for (uint16_t i = 0; i < value.size(); i++) {
    if (func(value[i]))
      output.push_back(value[i]);
  }
  new_shape.push_back(output.size());
  return ndarray(new_shape, output);
}
/**
 * @brief For every element evaluates a function to boolean on the supplied
 * ndarray and keeps the value when true
 *
 * @tparam T Underlaying data type
 * @param input input ndarray to filter
 * @param func Unary boolean function
 * @return ndarray<T> Values that evaluates to true
 */
template <class T>
ndarray<T> ndarray<T>::filter(const ndarray<T> input, bool (*func)(T)) const{
  return input.filter(func);
}

/**
 * @brief Applies a function to the supplied ndarray. Evaluates along the first
 * dimension e.g. ndarray [3, 2, 2] -> func([1, :, :]), func([2, :, :]),
 * func([3, :, :])
 *
 * @tparam T Underlaying data type
 * @param input input ndarray to apply the function to
 * @param func Unary boolean function
 * @return ndarray<T> Values that evaluates to true
 */
template <class T>
ndarray<T> ndarray<T>::applyFunc(const ndarray<T> input,
                                 std::function<T(ndarray<T>)> func) const{
  std::vector<T> output_value;
  std::vector<uint16_t> output_shape;

  ndarray<T> shapeholder = input;
  // Single dimension case
  if (input.getShape().size() == 1)
    // Was [n], reshape into [1, n]
    shapeholder = input.reshape({1, input.getShape()[0]});

  // Along the first dimension
  for (uint16_t i = 0; i < shapeholder.getShape()[0]; i++) {
    // Extract all other dimensions
    ndarray<T> temp = shapeholder.getPosition({i});

    if (temp.shape.size() != 1)
      temp = temp.reshape({(uint16_t)(temp.shape[0] * temp.count())});

    // Append function result along those dimensions
    output_value.push_back(func(temp));
  }
  output_shape = {shapeholder.getShape()[0]};

  return ndarray(output_shape, output_value);
}

/**
 * @brief Returns ndarray of max values
 *
 * @tparam T Underlaying data type
 * @return ndarray<T> Ndarray of maximum values
 */
template <class T> ndarray<T> ndarray<T>::max() const{
  return applyFunc(
      *this, [](ndarray<T> a) { return *max_element(a.begin(), a.end()); });
}
/**
 * @brief Returns ndarray of max values of the supplied ndarray
 *
 * @tparam T Underlaying data type
 * @param input Input ndarray
 * @return ndarray<T> Ndarray of maximum values
 */
template <class T> ndarray<T> ndarray<T>::max(const ndarray<T> input){
  return input.max();
}

/**
 * @brief Returns ndarray of min values
 *
 * @tparam T Underlaying data type
 * @return ndarray<T> Ndarray of minimum values
 */
template <class T> ndarray<T> ndarray<T>::min() const{
  return applyFunc(
      *this, [](ndarray<T> a) { return *min_element(a.begin(), a.end()); });
}
/**
 * @brief Returns ndarray of min values of the supplied ndarray
 *
 * @tparam T Underlaying data type
 * @param input Input ndarray
 * @return ndarray<T> Ndarray of minimum values
 */
template <class T> ndarray<T> ndarray<T>::min(const ndarray<T> input){
  return input.min();
}

/**
 * @brief Returns ndarray of sums of values
 *
 * @tparam T Underlaying data type
 * @return ndarray<T> Ndarray of sums
 */
template <class T> ndarray<T> ndarray<T>::sum() const{
  return applyFunc(
      *this, [](ndarray<T> a) { return accumulate(a.begin(), a.end(), 0.0); });
}
/**
 * @brief Returns ndarray of sums of values of the supplied ndarray
 *
 * @tparam T Underlaying data type
 * @param input Input ndarray
 * @return ndarray<T> Ndarray of sums
 */
template <class T> ndarray<T> ndarray<T>::sum(const ndarray<T> input){
  return input.sum();
}

/**
 * @brief Returns ndarray of mean values
 *
 * @tparam T Underlaying data type
 * @return ndarray<T> Ndarray of means
 */
template <class T> ndarray<T> ndarray<T>::mean() const{
  return applyFunc(*this, [](ndarray<T> a) { return a.sum()[0] / a.count(); });
}
/**
 * @brief Returns ndarray of mean values of the supplied ndarray
 *
 * @tparam T Underlaying data type
 * @param input Input ndarray
 * @return ndarray<T> Ndarray of means
 */
template <class T> ndarray<T> ndarray<T>::mean(const ndarray<T> input){
  return input.mean();
}

/**
 * @brief Returns ndarray of standard deviation values
 *
 * @tparam T Underlaying data type
 * @return ndarray<T> Ndarray of standard deviations
 */
template <class T> ndarray<T> ndarray<T>::std() const{
  return applyFunc(*this, [](ndarray<T> a) {
    T total = 0;
    for (int i = 0; i < a.count(); i++) {
      total += (a[i] - a.mean()[0]) * (a[i] - a.mean()[0]);
    }
    return sqrt(total / a.count());
  });
}
/**
 * @brief Returns ndarray of standard deviation values of the supplied ndarray
 *
 * @tparam T Underlaying data type
 * @param input Input ndarray
 * @return ndarray<T> Ndarray of standard deviations
 */
template <class T> ndarray<T> ndarray<T>::std(const ndarray<T> input){
  return input.std();
}

/**
 * @brief Returns ndarray of variance values
 *
 * @tparam T Underlaying data type
 * @return ndarray<T> Ndarray of variances
 */
template <class T> ndarray<T> ndarray<T>::var() const{
  return applyFunc(*this, [](ndarray<T> a) {
    T total = 0;
    for (int i = 0; i < a.count(); i++) {
      total += (a[i] - a.mean()[0]) * (a[i] - a.mean()[0]);
    }
    return (total / a.count());
  });
}
/**
 * @brief Returns ndarray of variance values of the supplied ndarray
 *
 * @tparam T Underlaying data type
 * @param input Input ndarray
 * @return ndarray<T> Ndarray of variances
 */
template <class T> ndarray<T> ndarray<T>::var(const ndarray<T> input){
  return input.var();
}
