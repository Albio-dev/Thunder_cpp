#include "ndarray.hpp"

/**
 * @brief Encapsulates underlaying vector size
 *
 * @return int Number of elements in vector
 */
int size()
{
    return this->value.size();
}

uint16_t getCount()
{
    return this->dimCount;
}

/**
 * @brief Get the Data vector stored
 *
 * @return vector<T> of the contained data
 */
vector<T> getValue()
{
    return this->value;
}

/**
 * @brief Get the Shape vector
 *
 * @return vector<uint16_t> shape vector: every position is the dimension size
 */
vector<uint16_t> getShape()
{
    return this->shape;
}

/**
 * @brief Retrieves first element if matrix
 *
 * @return T First value
 */
T first()
{
    return this->value[0];
}

auto begin()
{
    return value.begin();
}

auto end()
{
    return value.end();
}