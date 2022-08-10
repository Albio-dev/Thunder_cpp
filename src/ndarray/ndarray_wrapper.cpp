#include "ndarray.hpp"

/**
 * @brief Encapsulates underlaying vector size
 *
 * @return int Number of elements in vector
 */
template <class T>
int NDArray<T>::size()
{
    return this->value.size();
}

template <class T>
uint16_t NDArray<T>::getCount()
{
    return this->dimCount;
}

/**
 * @brief Get the Data vector stored
 *
 * @return vector<T> of the contained data
 */
template <class T>
std::vector<T> NDArray<T>::getValue()
{
    return this->value;
}

/**
 * @brief Get the Shape vector
 *
 * @return vector<uint16_t> shape vector: every position is the dimension size
 */
template <class T>
std::vector<uint16_t> NDArray<T>::getShape()
{
    return this->shape;
}

/**
 * @brief Retrieves first element if matrix
 *
 * @return T First value
 */
template <class T>
T NDArray<T>::first()
{
    return this->value[0];
}

template <class T>
auto NDArray<T>::begin()
{
    return value.begin();
}

template <class T>
auto NDArray<T>::end()
{
    return value.end();
}