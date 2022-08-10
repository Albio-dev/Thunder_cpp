#include "ndarray.hpp"

/**
 * @brief Function to keep interface consistent. Just a pointwise sum
 *
 * @param other Structure to sum to caller
 * @return NDArray<T> Object result of sum
 */
template <class T>
template <class K>
NDArray<T> NDArray<T>::plus(NDArray<K> other)
{
    return *this + other;
}

/**
 * @brief Function to keep interface consistent. Just a pointwise subtraction
 *
 * @param other Structure to subtract to caller
 * @return NDArray<T> Object result of subtraction
 */
template <class T>
template <class K>
NDArray<T> NDArray<T>::minus(NDArray<K> other)
{
    return *this - other;
}
/**
 * @brief Dot divide a matrix with another. ToDo: Controlli grandezze array e valori siano corretti/compatibibli
 *  tipo se un valore é di tipo int e l'altro tipo uint cast di che tipo (int imo)
 *
 * @return
 */
template <class T>
template <class K>
NDArray<T> NDArray<T>::dotdivide(const NDArray<K> other)
{
    return *this / other;
}

/** @brief Given two NDArray with the same shape. Multiply one element in position n with his corresponding
 * elem in position n.
 *
 * @param other second element of multiplication
 * @return out a vector with multiplied values
 */
template <class T>
template <class K>
NDArray<T> NDArray<T>::dottimes(const NDArray<K> other)
{
    return *this * other;
}
