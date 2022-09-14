
/**
 * @brief Encapsulates underlaying vector size
 *
 * @return int Number of elements in vector
 */

/**
 * @brief Wrapper for underlaying structure data count
 *
 * @tparam T ndarray type
 * @return uint16_t number of elements stored
 */
template <class T> uint16_t ndarray<T>::size() const { return value.size(); }

/**
 * @brief Get the Data vector stored
 *
 * @return vector<T> of the contained data
 */
template <class T> const std::vector<T> &ndarray<T>::getValue() const {
  return value;
}

/**
 * @brief Get the Shape vector
 *
 * @return vector<uint16_t> shape vector: every position is the dimension size
 */
template <class T> const std::vector<uint16_t> &ndarray<T>::getShape() const {
  return shape;
}

/**
 * @brief Retrieves first element if matrix
 *
 * @return T First value
 */
template <class T> const T &ndarray<T>::first() const { return this->value[0]; }

template <class T> auto ndarray<T>::begin() const { return value.begin(); }

template <class T> auto ndarray<T>::end() const { return value.end(); }