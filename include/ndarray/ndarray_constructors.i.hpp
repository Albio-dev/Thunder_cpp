/**
 * @brief Construct a new ndarray object when values are already in a vector
 * Almost a move constructor, since it copies the address of both
 * vectors
 *
 * @param lengths Dimensions vector of the resulting object
 * @param values Actual matrix values, already in vector format
 */
template <class T>
ndarray<T>::ndarray(std::vector<std::uint16_t> lengths, std::vector<T> values)
{
    if (!(std::is_arithmetic_v<T>))
        throw "Not arithmetic type";

    // Data checks
    if (lengths.size() == 0 || lengths[0] == 0)
        throw "Requested 0 dimensioned array";

    this->shape = lengths;
    this->value = values;

    // Multiplies all elements in lengths together
    uint64_t values_length = 1;
    for (uint16_t i : lengths)
        values_length *= i;

    if (values.size() != values_length)
        throw "Matrix dimensions and data length mismatch";

}

