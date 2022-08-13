/**
 * @brief Construct a new NDArray object when values are given in a C array
 * Basically a copy constructor since it copies the elements in the array in a
 * vector
 *
 * @param lengths Dimensions vector of the resulting object
 * @param values Actual matrix values, C array format (T*)
 */
template <class T>
NDArray<T>::NDArray(std::vector<std::uint16_t> lengths, T *values) {
  if (!(std::is_arithmetic_v<T>))
    throw "Not arithmetic type";
  // TODO: forse values può essere convertita direttamente in un vector?
  // Data checks
  if (lengths.size() == 0 || lengths[0] == 0)
    throw "Requested 0 dimensioned array";

  this->shape = lengths;

  uint16_t values_length = 1;
  for (uint16_t i : lengths)
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
template <class T>
NDArray<T>::NDArray(std::vector<std::uint16_t> lengths, std::vector<T> values) {

  if (!(std::is_arithmetic_v<T>))
    throw "Not arithmetic type";

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

  this->dimCount = count();
}
