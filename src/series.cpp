//
// Created by Aleardo on 03/08/22.
//

#include "../include/series.hpp"

template <class T> class Series : public ndarray<T> {

  friend class ndarray<T>;

  /**
   * @brief Construct a new Series object
   *
   * @param shape Series shape
   * @param input Input data vector
   */
  Series(std::vector<uint16_t> shape, std::vector<T> input)
      : ndarray<T>(shape, input) {}

public:
  /**
   * @brief Utility to prepare the matrix for processing by base functions
   * Squares the matrix collapsing all dimensions but last. E.g matrix (2, 3, 2)
   * becomes (6, 2) It then gets transposed so that the resulting matrix is (2,
   * 6).
   *
   * @return NDArray<T> Square matrix transposed. Collapses all dimensions
   * except last.
   */
  [[nodiscard]] ndarray<T> prepareMat() {

    // Saving previous dimensions for restoring them later
    std::vector<uint16_t> old_shape = ndarray<T>::getShape();
    // Collapses all dimensions but last
    ndarray<T>::reshape(
        {(uint16_t)count(),
         ndarray<T>::getShape()[ndarray<T>::getShape().size() - 1]});

    // Get the transpose
    ndarray<T> temp = ndarray<T>::transpose(*this);

    // Restore old dimensions
    ndarray<T>::reshape(old_shape);

    return temp;
  }

  [[nodiscard]] T getPosition(std::vector<uint16_t> indexes) {

    ndarray<T>::getPosition(indexes);
    return NULL;
  }

  /**
   * @brief Creates an Series from a C-style array with a given shape
   *
   * @tparam T Underlaying data type
   * @param shape Final ndarray shape
   * @param input Input array
   * @return Series<T> Resulting Series
   */
  [[nodiscard]] static Series<T> fromarray(std::vector<uint16_t> shape,
                                           T *input) {
    // Multiplies all elements in lengths together
    uint64_t values_length = 1;
    for (auto i : shape)
      values_length *= i;
    return fromvector(shape, {input, input + values_length});
  }

  /**
   * @brief Creates an Series from a given list. Assumes 1 by list size
   *
   * @tparam T Underlaying data type
   * @param l Input list
   * @return Series<T> Resulting Series 1 by list length
   */
  [[nodiscard]] static Series<T> fromlist(std::list<T> l) {
    if (l.size() == 0)
      throw "List empty. Need to have a non empty list assigned.";

    return fromvector({l.size()}, {l.begin(), l.end()});
  }

  /**
   * @brief Creates an Series from a given list and with given shape
   *
   * @tparam T Underlaying data type
   * @param l Input list
   * @return Series<T> Resulting Series
   */
  [[nodiscard]] static Series<T> fromlist(std::vector<uint16_t> shape,
                                          std::list<T> l) {
    return fromvector(shape, {l.begin(), l.end()});
  }

  /**
   * @brief Creates an Series from a given vector. Supposes 1 by vector length
   *
   * @tparam T Underlaying data type
   * @param input Input vector
   * @return Series<T> Resulting Series
   */
  [[nodiscard]] static Series<T> fromvector(std::vector<T> input) {
    return fromvector({static_cast<uint16_t>(input.size())}, input);
  }
  /**
   * @brief Wrapper of the costructor from an input vector
   *
   * @param shape Desired shape of the data
   * @param input Data vector
   * @return Series<T> Resulting Series object
   */
  [[nodiscard]] static Series<T> fromvector(std::vector<uint16_t> shape,
                                            std::vector<T> input) {
    return Series(shape, input);
  }

  /**
   * @brief Creates an Series from a given dequeue. Supposes 1 by vector length
   *
   * @tparam T Underlaying data type
   * @param input Input dequeue
   * @return Series<T> Resulting Series
   */
  [[nodiscard]] static Series<T> fromdeque(std::deque<T> input) {
    return fromvector({static_cast<uint16_t>(input.size())},
                      {input.begin(), input.end()});
  }
  /**
   * @brief Creates an Series from a given dequeue with a given shape
   *
   * @tparam T Underlaying data type
   * @param shape Final Series shape
   * @param input Input dequeue
   * @return Series<T> Resulting Series
   */
  [[nodiscard]] static Series<T> fromdeque(std::vector<uint16_t> shape,
                                           std::deque<T> input) {
    return fromvector(shape, {input.begin(), input.end()});
  }

  /**
   * @brief Creates an Series from a given forward_list. Supposes 1 by vector
   * length
   *
   * @tparam T Underlaying data type
   * @param input Input forward_list
   * @return Series<T> Resulting Series
   */
  [[nodiscard]] static Series<T> fromforward_list(std::forward_list<T> input) {
    return fromvector({static_cast<uint16_t>(input.size())},
                      {input.begin(), input.end()});
  }
  /**
   * @brief Creates an Series from a given forward_list with a given shape
   *
   * @tparam T Underlaying data type
   * @param shape Final Series shape
   * @param input Input forward_list
   * @return Series<T> Resulting Series
   */
  [[nodiscard]] static Series<T> fromforward_list(std::vector<uint16_t> shape,
                                                  std::forward_list<T> input) {
    return fromvector(shape, {input.begin(), input.end()});
  }

  /** @brief Return an example series object with random values
   *
   * @param shape a vector with the desired dimensions
   * @param seed seed value for the random function
   * @return Series<T> Resulting series object
   */
  [[nodiscard]] static Series<T>
  fromrandom(std::vector<uint16_t> shape = {100, 10}, int seed = 42) {
    return static_cast<Series<T>>(ndarray<T>::fromrandom(shape, seed));
  }

  /**
   * @brief Loads data from text files. Assumes data is formatted by rows with
   * spaced elements
   *
   * @param path Path to file to read
   * @return Series<T> Resulting series object
   */
  [[nodiscard]] static Series<T> fromtext(std::string path) {
    std::vector<T> output;
    std::string line;
    std::ifstream text_file(path);
    if (text_file.is_open()) {
      while (getline(text_file, line)) {
        std::istringstream stream(line);
        std::string segment;

        while (std::getline(stream, segment, ' ')) {
          if (std::is_same<T, float>::value) {
            std::cout << std::stof(segment) << " ";
            output.push_back(std::stof(segment));
          }
          if (std::is_same<T, int>::value) {
            std::cout << std::stoi(segment) << " ";
            output.push_back(std::stoi(segment));
          }
        }
      }

      text_file.close();
    } else {
      throw "Unable to open file. Some error occurred!";
    }

    return Series<T>({static_cast<uint16_t>(output.size())}, output);
  }

  /** @brief Construct this class with a default base series from random.
   *
   */

  /**
   * @brief Return an example series object with random values
   *
   * @return Series<T> Resulting series object
   */
  [[nodiscard]] static Series<T> fromexample() { return fromrandom({25}, 42); }

  /**
   * @brief Counts how many least-dimensioned elements there are.
   * e.g (2, 3, 2) = 6
   *
   * @return int Number of least dimensioned elements
   */
  [[nodiscard]] int count() {

    int output = 1;

    // Multiplies all dimensions except last
    for (uint16_t i = 0; i < ndarray<T>::getShape().size() - 1; i++) {
      output *= ndarray<T>::getShape()[i];
    }

    return output;
  }

  /**
   * @brief Filter function wrapper from ndarray
   *
   * @param func Boolean function to use as filter
   * @return Series<T> Resulting series object
   */
  [[nodiscard]] Series<T> filter(bool (*func)(T)) {
    return static_cast<Series<T>>(ndarray<T>::filter(prepareMat(), func));
  }
  /**
   * @brief Gets the max of all least-dimensioned elements
   * Given a series (2, 3, 2) -> (1, 1, 2) -> (2)
   *
   * @return Series<T> Serie of max elements
   */
  [[nodiscard]] Series<T> max() {
    return static_cast<Series<T>>(ndarray<T>::max(prepareMat()));
  }
  /**
   * @brief Gets the min of all least-dimensioned elements
   * Given a series (2, 3, 2) -> (1, 1, 2) -> (2)
   *
   * @return Series<T> Serie of min elements
   */
  [[nodiscard]] Series<T> min() {
    return static_cast<Series<T>>(ndarray<T>::min(prepareMat()));
  }
  /**
   * @brief Gets the sum of all least-dimensioned elements
   * Given a series (2, 3, 2) -> (1, 1, 2) -> (2)
   *
   * @return Series<T> Serie of sum elements
   */
  [[nodiscard]] Series<T> sum() {
    return static_cast<Series<T>>(ndarray<T>::sum(prepareMat()));
  }
  /**
   * @brief Gets the mean of all least-dimensioned elements
   * Given a series (2, 3, 2) -> (1, 1, 2) -> (2)
   *
   * @return Series<T> Serie of means
   */
  [[nodiscard]] Series<T> mean() {
    return static_cast<Series<T>>(ndarray<T>::mean(prepareMat()));
  }
  /**
   * @brief Gets the standard deviation of all least-dimensioned elements
   * Given a series (2, 3, 2) -> (1, 1, 2) -> (2)
   *
   * @return Series<T> Serie of standard deviations
   */
  [[nodiscard]] Series<T> std() {
    return static_cast<Series<T>>(ndarray<T>::std(prepareMat()));
  }
  /**
   * @brief Gets the variance of all least-dimensioned elements
   * Given a series (2, 3, 2) -> (1, 1, 2) -> (2)
   *
   * @return Series<T> Serie of variances
   */
  [[nodiscard]] Series<T> var() {
    return static_cast<Series<T>>(ndarray<T>::var(prepareMat()));
  }
};