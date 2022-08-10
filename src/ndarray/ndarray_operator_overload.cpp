#include "ndarray.hpp"

/**
 * @brief Dot function a matrix with another.
 *
 * @return
 */
template <class OP>
NDArray::element_wise(const NDArray<T> other, OP op)
{
    if (shape != other.shape)
        throw "Array shapes don't match";
    vector<T> out = {};

    // TODO: forse snellire? copiare un vector in output ed eseguire l'operazione in loco
    for (unsigned int i = 0; i < value.size(); i++)
    {
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
NDArray::operator+(const NDArray<T> other)
{
    return NDArray::element_wise(other, std::plus<T>);
}
/**
 * @brief Subtraction operation between two NDArrays
 *
 * @param other Other NDArray subtracted to this one
 * @return NDArray<T> Result of subtraction
 */
NDArray::operator-(const NDArray<T> other)
{
    return NDArray::element_wise(other, std::minus<T>);
}

NDArray::operator*(const NDArray<T> other)
{
    return NDArray::element_wise(other, std::multiplies<T>);
}

NDArray::operator/(const NDArray<T> other)
{
    return NDArray::element_wise(other, std::divides<T>);
}

/**
 * @brief Function to directly address the underlaying vector
 *
 * @param index index of the referenced element
 * @return T type of the element in the data structure
 */
NDArray::operator[](unsigned int index)
{
    if (index < this->value.size())
        return this->value[index];
    else
        throw "Out of bound indexing";
}
