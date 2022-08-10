#include "ndarray.hpp"

/**
 * @brief Get the value in position given a vector with a precise location
 *
 * @param pos a vector with a position
 * @return vector<T> value referenced by pos
 */
template <class T>
NDArray<T> NDArray<T>::getPosition(std::vector<uint16_t> pos)
{

    // Check indexing
    if (pos.size() > shape.size())
        throw "Wrong dimensional indexing: dimensions mismatch";

    int lastdim = pos.size();

    // Calculate requested element's position up to the specified dimension
    int startIndex = 0;
    for (unsigned int i = 0; i < pos.size(); i++)
    {
        // Check if index out of bounds
        if (pos[i] < 0 || pos[i] >= shape[i])
            throw "Index out of bounds";

        // Calculating chunk size
        int subDimensionSize = 1;
        for (unsigned int k = shape.size() - 1; k != i; k--)
        {
            subDimensionSize *= shape[k];
        }

        // Shift index by input * chunk size
        startIndex = startIndex + pos[i] * subDimensionSize;
    }

    std::vector<uint16_t> new_shape;
    // Starting from the missing dimension calculates the size of the identified matrix
    int endindex = 1;
    for (unsigned int i = lastdim; i < shape.size(); i++)
    {
        endindex *= shape[i];
        new_shape.push_back(shape[i]);
    }
    endindex += startIndex;

    // Temporary output structure
    std::vector<T> output_temp;

    // Extract data in range
    do
    {
        output_temp.push_back(this->value[startIndex]);
        startIndex++;
    } while (startIndex < endindex);

    if (new_shape.size() == 0)
        new_shape.push_back(1);
    return NDArray<T>(new_shape, output_temp);
}

/**
 * @brief Check if shape is correct or plausibile and return number of elements
 *
 * @return values_length Number of elements in vector
 */
template <class T>
int NDArray<T>::get_current_dimension()
{
    if (this->shape.size() == 0 || this->shape[0] == 0)
        throw "Requested 0 dimensioned array";

    int values_length = 1;
    for (int i : this->shape)
    {
        if (i < 1)
            throw "One or more dimension less than 1";

        values_length = values_length * i;
    }

    return values_length;
}

/**
 * @brief Extract the underlaying array
 *
 * @return T* pointer to start of array (same as contained vector)
 */
template <class T>
T *NDArray<T>::toarray()
{
    std::vector<T> new_value = value;
    return &(new_value)[0];
}

/**
 * @brief Count how many elements there are in every matrix along the first dimension
 *
 * @return multiplication of dimension sizes except first
 */
template <class T>
int NDArray<T>::count()
{
    if (shape.size() == 1)
        return shape[0];
    //            reshape({1, shape[0]});

    // Multiplication of elements indexed [1 .. shape.size())
    int size = 1;
    for (unsigned int i = 1; i < shape.size(); i++)
        size *= shape[i];
    return size;
}
template <class T>
int NDArray<T>::count(NDArray<T> input)
{
    return input.count();
}

// TODO: To be protected, internal function
template <class T>
NDArray<T> NDArray<T>::transpose(NDArray<T> input)
{

    if (input.getShape().size() != 2)
    {
        throw "Wrong size for transposition. Expected NxM";
    }

    uint16_t N = input.getShape()[0];
    uint16_t M = input.getShape()[1];
    int size = (N * M);

    // TODO: attenzione allo 0 per altri tipi
    std::vector<T> output(size, 0);

    for (uint16_t i = 0; i < size; i++)
    {
        output[i] = input[M * (i % N) + (i / N)];
    }

    return NDArray<T>({M, N}, output);
}

template <class T>
void NDArray<T>::reshape(std::vector<uint16_t> new_shape)
{
    shape = new_shape;
}