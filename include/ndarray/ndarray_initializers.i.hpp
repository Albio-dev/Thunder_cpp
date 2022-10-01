
/**
 * @brief Creates an ndarray with random values
 *
 * @tparam T Underlaying type
 * @param shape Shape of the new ndarray
 * @param seed Seed for RNG
 * @return ndarray<T> Ndarray with shape shape and random values
 */
template <class T>
ndarray<T> ndarray<T>::fromrandom(const std::vector<uint16_t> shape, const int seed) {
  std::vector<T> output;
  int num_values =
      std::accumulate(shape.begin(), shape.end(), 1, std::multiplies<T>());

  // Workaround, I create a value of type T and check value type
  T value = 0;
  value++;

  std::random_device dev;
  std::default_random_engine rng(seed);
  if (std::is_floating_point<T>::value) {
    std::uniform_real_distribution<T> dist6(1, 100);
    for (int k = 0; k < num_values; k++) {
      output.push_back(dist6(rng));
    }
  } else {
    std::uniform_int_distribution<T> dist6(1, 6);
    for (int k = 0; k < num_values; k++) {
      output.push_back(dist6(rng));
    }
  }

  return ndarray<T>(shape, output);
}

/**
 * @brief Creates an ndarray from a C-style array with a given shape
 *
 * @tparam T Underlaying data type
 * @param shape Final ndarray shape
 * @param input Input array
 * @return ndarray<T> Resulting ndarray
 */
template <class T>
ndarray<T> ndarray<T>::fromarray(const std::vector<uint16_t> shape, const T *input) {
  // Multiplies all elements in lengths together
  uint64_t values_length = 1;
  for (auto i : shape)
    values_length *= i;
  return ndarray<T>(shape, {input, input + values_length});
}

/**
 * @brief Creates an ndarray from a given list. Assumes 1 by list size
 *
 * @tparam T Underlaying data type
 * @param l Input list
 * @return ndarray<T> Resulting ndarray 1 by list length
 */
template <class T> ndarray<T> ndarray<T>::fromlist(const std::list<T> l) {
  if (l.size() == 0)
    throw "List empty. Need to have a non empty list assigned.";

  return fromvector({l.size()}, {l.begin(), l.end()});
}

/**
 * @brief Creates an ndarray from a given list and with given shape
 *
 * @tparam T Underlaying data type
 * @param l Input list
 * @return ndarray<T> Resulting ndarray
 */
template <class T>
ndarray<T> ndarray<T>::fromlist(const std::vector<uint16_t> shape, const std::list<T> l) {
  return fromvector(shape, {l.begin(), l.end()});
}

/**
 * @brief Creates an ndarray from a given vector. Supposes 1 by vector length
 *
 * @tparam T Underlaying data type
 * @param input Input vector
 * @return ndarray<T> Resulting ndarray
 */
template <class T> ndarray<T> ndarray<T>::fromvector(const std::vector<T> input) {
  return fromvector({static_cast<uint16_t>(input.size())}, input);
}
/**
 * @brief Creates an ndarray from a given vector with a given shape
 *
 * @tparam T Underlaying data type
 * @param shape Final ndarray shape
 * @param input Input vector
 * @return ndarray<T> Resulting ndarray
 */
template <class T>
ndarray<T> ndarray<T>::fromvector(const std::vector<uint16_t> shape,
                                  const std::vector<T> input) {
  return ndarray<T>(shape, input);
}

/**
 * @brief Creates an ndarray from a given dequeue. Supposes 1 by vector length
 *
 * @tparam T Underlaying data type
 * @param input Input dequeue
 * @return ndarray<T> Resulting ndarray
 */
template <class T> ndarray<T> ndarray<T>::fromdeque(const std::deque<T> input) {
  return fromvector({static_cast<uint16_t>(input.size())},
                    {input.begin(), input.end()});
}
/**
 * @brief Creates an ndarray from a given dequeue with a given shape
 *
 * @tparam T Underlaying data type
 * @param shape Final ndarray shape
 * @param input Input dequeue
 * @return ndarray<T> Resulting ndarray
 */
template <class T>
ndarray<T> ndarray<T>::fromdeque(const std::vector<uint16_t> shape,
                                 const std::deque<T> input) {
  return fromvector(shape, {input.begin(), input.end()});
}

/**
 * @brief Creates an ndarray from a given forward_list. Supposes 1 by vector
 * length
 *
 * @tparam T Underlaying data type
 * @param input Input forward_list
 * @return ndarray<T> Resulting ndarray
 */
template <class T>
ndarray<T> ndarray<T>::fromforward_list(const std::forward_list<T> input) {
  return fromvector({static_cast<uint16_t>(input.size())},
                    {input.begin(), input.end()});
}
/**
 * @brief Creates an ndarray from a given forward_list with a given shape
 *
 * @tparam T Underlaying data type
 * @param shape Final ndarray shape
 * @param input Input forward_list
 * @return ndarray<T> Resulting ndarray
 */
template <class T>
ndarray<T> ndarray<T>::fromforward_list(const std::vector<uint16_t> shape,
                                        const std::forward_list<T> input) {
  return fromvector(shape, {input.begin(), input.end()});
}

/**
 * @brief Read file and writes it directly into ndarray
 *
 * @tparam T Underlaying data type
 * @param new_shape Final ndarray shape
 * @param path Input file path
 * @return ndarray<T> Resulting ndarray
 */
// ToDo: https://en.cppreference.com/w/cpp/filesystem/path
template <class T>
ndarray<T> ndarray<T>::frombinary(const std::vector<uint16_t> new_shape,
                                  const std::string path) {
  // ToDo: try to use std::filesystem::path
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
  // int dimension = (int)(fileSize / sizeof(T));
  // Maybe I should use this code for file.read directly on this->value
  // this->value.reserve(dimension);

  /*
  if (NDArray<T>::get_current_dimension() != dimension)
      throw "File is larger or shorter then expected.";
  */
  std::vector<T> vec(fileSize / sizeof(T));
  file.read(reinterpret_cast<char *>(vec.data()), vec.size() * sizeof(T));

  return ndarray<T>(new_shape, vec);
}
