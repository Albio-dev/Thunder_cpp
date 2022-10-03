
/**
 * @brief Dot function a matrix with another.
 *
 * @tparam T caller ndarray's type
 * @tparam OP type of binary operation
 * @tparam K type of other ndarray
 * @param other ndarray to operate with
 * @param op function to apply to every element
 * @return ndarray<T> ndarray result of op
 */
template <class T>
template <class OP, class K>
ndarray<T> ndarray<T>::element_wise(const ndarray<K> other, OP op) const {
  if (!(std::is_arithmetic_v<K>))
    throw "Argument tipe not arithmetic";
  if (shape != other.shape)
    throw "Array shapes don't match";

  std::vector<K> out;

  // TODO: forse snellire? copiare un vector in output ed eseguire l'operazione
  // in loco
  for (unsigned int i = 0; i < value.size(); i++) {
    out.push_back(op(value[i], other.value[i]));
  }

  return ndarray(shape, out);
}

/**
 * @brief  Sum operation between two ndarrays
 *
 * @tparam T caller ndarray's type
 * @tparam K type of other ndarray
 * @param other other ndarray to sum to this one
 * @return ndarray<T> ndarray result
 */
template <class T>
template <class K>
ndarray<T> ndarray<T>::operator+(const ndarray<K> other) const {
  return ndarray::element_wise(other, std::plus<T>());
}

/**
 * @brief  Subtraction operation between two ndarrays
 *
 * @tparam T caller ndarray's type
 * @tparam K type of other ndarray
 * @param other other ndarray to sum to this one
 * @return ndarray<T> ndarray result
 */
template <class T>
template <class K>
ndarray<T> ndarray<T>::operator-(const ndarray<K> other) const {
  return ndarray::element_wise(other, std::minus<T>());
}

/**
 * @brief  Multiplication operation between two ndarrays
 *
 * @tparam T caller ndarray's type
 * @tparam K type of other ndarray
 * @param other other ndarray to sum to this one
 * @return ndarray<T> ndarray result
 */
template <class T>
template <class K>
ndarray<T> ndarray<T>::operator*(const ndarray<K> other) const {
  return ndarray::element_wise(other, std::multiplies<T>());
}

/**
 * @brief  Division operation between two ndarrays
 *
 * @tparam T caller ndarray's type
 * @tparam K type of other ndarray
 * @param other other ndarray to sum to this one
 * @return ndarray<T> ndarray result
 */
template <class T>
template <class K>
ndarray<T> ndarray<T>::operator/(const ndarray<K> other) const {
  // ToDo: study how it works
  if (!std::is_arithmetic_v<K>)
    throw "Argument tipe not arithmetic";
  return ndarray::element_wise(other, std::divides<T>());
}

/**
 * @brief Indexes the underlying vector
 *
 * @tparam T caller ndarray's type
 * @param index index to retrieve the value from
 * @return T value type
 */
template <class T> const T &ndarray<T>::operator[](const uint16_t index) const {
  if (index < value.size())
    return value[index];
  else
    throw "Out of bound indexing";
}
