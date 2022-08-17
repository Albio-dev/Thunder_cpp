
/**
 * @brief Encapsulates underlaying vector size
 *
 * @return int Number of elements in vector
 */
template <class T>
int ndarray<T>::size()
{
    return this->value.size();
}

template <class T>
uint16_t ndarray<T>::getCount()
{
    return this->dimCount;
}

/**
 * @brief Get the Data vector stored
 *
 * @return vector<T> of the contained data
 */
template <class T>
std::vector<T> ndarray<T>::getValue()
{
    return this->value;
}

/**
 * @brief Get the Shape vector
 *
 * @return vector<uint16_t> shape vector: every position is the dimension size
 */
template <class T>
std::vector<uint16_t> ndarray<T>::getShape()
{
    return this->shape;
}

/**
 * @brief Retrieves first element if matrix
 *
 * @return T First value
 */
template <class T>
T ndarray<T>::first()
{
    return this->value[0];
}

template <class T>
auto ndarray<T>::begin()
{
    return value.begin();
}

template <class T>
auto ndarray<T>::end()
{
    return value.end();
}