#include "ndarray.hpp"

/**
 * @brief Function to keep interface consistent. Just a pointwise sum
 *
 * @param other Structure to sum to caller
 * @return NDArray<T> Object result of sum
 */
NDArray<T> plus(NDArray<T> other)
{
    return *this + other;
}

/**
 * @brief Function to keep interface consistent. Just a pointwise subtraction
 *
 * @param other Structure to subtract to caller
 * @return NDArray<T> Object result of subtraction
 */
NDArray<T> minus(NDArray<T> other)
{
    return *this - other;
}
/**
 * @brief Dot divide a matrix with another. ToDo: Controlli grandezze array e valori siano corretti/compatibibli
 *  tipo se un valore é di tipo int e l'altro tipo uint cast di che tipo (int imo)
 *
 * @return
 */
template <class K>
vector<double> dotdivide(const NDArray<K> other)
{
    if (shape != other.shape)
        throw "Array shapes don't match";

    vector<double> out = {};

    for (unsigned int i = 0; i < value.size(); i++)
    {
        out.push_back(value[i] / (double)other.value[i]);
    }

    return out;
}

/** @brief Given two NDArray with the same shape. Multiply one element in position n with his corresponding
 * elem in position n.
 *
 * @param other second element of multiplication
 * @return out a vector with multiplied values
 */
vector<T> dottimes(const NDArray<T> other)
{
    if (shape != other.shape)
        throw "Array shapes don't match";

    vector<T> out = {};

    for (unsigned int i = 0; i < value.size(); i++)
    {
        out.push_back(value[i] * other.value[i]);
    }

    return out;
}
