
/**
 * @brief Get the (possibly multidimentional) element in position
 * 
 * @tparam T ndarray data type
 * @param pos Indexes array
 * @return ndarray<T> 
 */
template <class T>
ndarray<T> ndarray<T>::getPosition(const std::vector<uint16_t> pos) const
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
    return ndarray<T>(new_shape, output_temp);
}

// TODO: remove?
/**
 * @brief Check if shape is correct or plausibile and return number of elements
 *
 * @return values_length Number of elements in vector
 */
template <class T>
int ndarray<T>::get_current_dimension() const
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
 * @brief Retrieve the underlaying array
 *
 * @return T* pointer to start of array (same as contained vector)
 */
template <class T>
T *ndarray<T>::toarray() const
{
    std::vector<T> new_value = value;
    return &(new_value)[0];
}

/**
 * @brief Count how many elements there are in every matrix along the first dimension
 *
 * @tparam T ndarray stored type
 * @return uint16_t multiplication of dimension sizes except first
 */
template <class T>
uint16_t ndarray<T>::count() const
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

/**
 * @brief Count how many elements there are in every matrix along the first dimension
 *
 * @tparam T ndarray stored type
 * @param input ndarray object to count on
 * @return uint16_t number of elements along the first dimension
 */
template <class T>
uint16_t ndarray<T>::count(const ndarray<T> input) const
{
    return input.count();
}

/**
 * @brief Transposes the matrix. Accepts only 2-dimensioned matrices
 * 
 * @tparam T type of the ndarray
 * @param input input matrix to transpose
 * @return ndarray<T> transposed matrix
 */
template <class T>
ndarray<T> ndarray<T>::transpose(const ndarray<T> input)
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

    return ndarray<T>({M, N}, output);
}

/**
 * @brief Change shape to the matrix. new dimensions must add up to the previous ones
 * 
 * @tparam T type of wrapped data
 * @param new_shape new shape of data
 */
template <class T>
void ndarray<T>::reshape(const std::vector<uint16_t> new_shape)
{
    if (std::accumulate(new_shape.begin(), new_shape.end(), 1u, std::multiplies<>()) != value.size())
        throw "Reshaping a different number of elements";
    shape = new_shape;
}