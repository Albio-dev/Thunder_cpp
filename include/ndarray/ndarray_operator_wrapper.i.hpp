/**
 * @brief Wrapper for sum operation. This is for interface coherence with the
 * python version
 *
 * @tparam T Caller ndarray's type
 * @tparam K Other ndarray's type
 * @param other Other ndarray to sum with this one
 * @return ndarray<T> Resulting ndarray
 */
template <class T>
template <class K>
ndarray<T> ndarray<T>::plus(const ndarray<K> other) const {

  return *this + other;
}

/**
 * @brief Wrapper for subtraction operation. This is for interface coherence
 * with the python version
 *
 * @tparam T Caller ndarray's type
 * @tparam K Other ndarray's type
 * @param other Other ndarray to subtract to this one
 * @return ndarray<T> Resulting ndarray
 */
template <class T>
template <class K>
ndarray<T> ndarray<T>::minus(const ndarray<K> other) const {
  return *this - other;
}
/**
 * @brief Wrapper for dot division operation. This is for interface coherence
 * with the python version
 *
 * @tparam T Caller ndarray's type
 * @tparam K Other ndarray's type
 * @param other Other ndarray to dot divide with this one
 * @return ndarray<T> Resulting ndarray
 */
template <class T>
template <class K>
ndarray<T> ndarray<T>::dotdivide(const ndarray<K> other) const {
  return *this / other;
}

/**
 * @brief Wrapper for dot multiplication operation. This is for interface
 * coherence with the python version
 *
 * @tparam T Caller ndarray's type
 * @tparam K Other ndarray's type
 * @param other Other ndarray to multiply to this one
 * @return ndarray<T> Resulting ndarray
 */
template <class T>
template <class K>
ndarray<T> ndarray<T>::dottimes(const ndarray<K> other) const {
  return *this * other;
}
