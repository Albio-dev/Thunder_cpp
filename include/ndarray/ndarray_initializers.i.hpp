
/** @brief Initialize with random values this->value
 *
 * @param shape a vector with the desired dimension
 * @param seed seed value for the random function
 */

template <class T>
NDArray<T> NDArray<T>::fromrandom(std::vector<uint16_t> shape, int seed)
{
    //std::vector<T> shape = shape;
    std::vector<T> output;
    int num_values = std::accumulate(shape.begin(), shape.end(), 1, std::multiplies<T>());

    // ToDo: Works only with float values not int
    std::random_device dev;
    std::default_random_engine rng(seed);
    std::uniform_real_distribution<T> dist6(1, 100);
    for (int k = 0; k < num_values; k++)
    {
        output.push_back(dist6(rng));
    }

    return NDArray<T>(shape, output);
}

/**
 * @brief Passed a list assign all values to current data structure
 * as one dimensional matrix.
 *
 */

template <class T>
NDArray<T> NDArray<T>::fromlist(std::list<T> l)
{
    if (l.size() == 0)
        throw "List empty. Need to have a non empty list assigned.";

    //this->shape = {l.size()};
    std::vector<T> output;
    output.reserve(l.size());
    output.assign(l.begin(), l.end());

    return NDArray<T>({l.size()}, output);
}
template <class T>
NDArray<T> NDArray<T>::fromarray(std::vector<T> input){
    return NDArray<T>({static_cast<uint16_t>(input.size())}, input);
}
template <class T>
NDArray<T> NDArray<T>::fromarray(std::vector<uint16_t> shape, std::vector<T> input)
{
    return NDArray<T>(shape, input);
}
template <class T>
NDArray<T> NDArray<T>::fromarray(std::vector<uint16_t> shape, T* input)
{
    return NDArray<T>(shape, input);
}

// ToDo: https://en.cppreference.com/w/cpp/filesystem/path
/** @brief Read a file as is to the class with some checks on possible errors
 *
 * @param shape a vector with the desired dimension
 * @param path path to a file
 */

template <class T>
NDArray<T> NDArray<T>::frombinary(std::vector<uint16_t> new_shape, std::string path)
{
    //this->shape = new_shape;

    std::ifstream file(path, std::ios::in | std::ios::binary);
    if (!file.is_open())
        throw "Can't open file. Some error occurred.";

    // Disables skipping of leading whitespace by the formatted input functions
    // https://en.cppreference.com/w/cpp/io/manip/skipws
    file.unsetf(std::ios::skipws);

    std::streampos fileSize;
    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // reserve capacity in vector
    //int dimension = (int)(fileSize / sizeof(T));
    // Maybe I should use this code for file.read directly on this->value
    // this->value.reserve(dimension);

    /*
    if (NDArray<T>::get_current_dimension() != dimension)
        throw "File is larger or shorter then expected.";
    */
    std::vector<T> vec(fileSize / sizeof(T));
    file.read(reinterpret_cast<char *>(vec.data()), vec.size() * sizeof(T));

    //this->value = vec;

    return NDArray<T>(new_shape, vec);
}
