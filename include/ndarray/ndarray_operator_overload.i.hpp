
/**
 * @brief Dot function a matrix with another.
 *
 * @return
 */
template <class T>
template <class OP, class K>
NDArray<T> NDArray<T>::element_wise(const NDArray<K> other, OP op) {
  if (!(std::is_arithmetic_v<K>))
    throw "Argument tipe not arithmetic";
  if (shape != other.shape)
    throw "Array shapes don't match";
  std::vector<T> out = {};

  // TODO: forse snellire? copiare un vector in output ed eseguire l'operazione
  // in loco
  for (unsigned int i = 0; i < value.size(); i++) {
    out.push_back(op(value[i], other.value[i]));
  }

  return NDArray(shape, out);
}

/**
 * @brief Sum operation between two NDArrays
 *
 * @param other Other NDArray summed to this one
 * @return NDArray<T> Result of sum
 */
template <class T>
template <class K>
NDArray<T> NDArray<T>::operator+(const NDArray<K> other) {
  return NDArray::element_wise(other, std::plus<T>());
}
/**
 * @brief Subtraction operation between two NDArrays
 *
 * @param other Other NDArray subtracted to this one
 * @return NDArray<T> Result of subtraction
 */
template <class T>
template <class K>
NDArray<T> NDArray<T>::operator-(const NDArray<K> other) {
  return NDArray::element_wise(other, std::minus<T>());
}

template <class T>
template <class K>
NDArray<T> NDArray<T>::operator*(const NDArray<K> other) {
  return NDArray::element_wise(other, std::multiplies<T>());
}

template <class T>
template <class K>
NDArray<T> NDArray<T>::operator/(const NDArray<K> other) {
  if (!std::is_arithmetic_v<K>)
    throw "Argument tipe not arithmetic";
  return NDArray::element_wise(other, std::divides<T>());
}

/**
 * @brief Function to directly address the underlaying vector
 *
 * @param index index of the referenced element
 * @return T type of the element in the data structure
 */
template <class T> T NDArray<T>::operator[](unsigned int index) {
  if (index < this->value.size())
    return this->value[index];
  else
    throw "Out of bound indexing";
}
