//
// Created by Aleardo on 03/08/22.
//
#include <iostream>

#include "images.hpp"
#include <string>

template<class T>
class Images : public NDArray<T> {
public:
    Images() = default;

    T getPosition() {
        return NULL;
    }

    // ToDo: https://en.cppreference.com/w/cpp/filesystem/path
    /** @brief Read a file as is to the class with some checks on possible errors
     *
     * @param shape a vector with the desired dimension
     * @param path path to a file
     */
    void frombinary(std::vector<uint16_t> shape, std::string path) {
        this->shape = shape;

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
        int dimension = (int) (fileSize / sizeof(T));
//        this->value.reserve(dimension); // Maybe I should use this code for file.read directly on this->value

        if (NDArray<T>::get_current_dimension() != dimension)
            throw "File is larger or shorter then expected.";

        std::vector<T> vec(fileSize / sizeof(T));
        file.read(reinterpret_cast<char *>(vec.data()), vec.size() * sizeof(T));

        this->value = vec;

        return;
    }

    /** @brief Construct this class with an example image. Default is "dot1_grey.png", usable images are:
     * "dot2_grey.png" and "dot3_grey.png".
     *
     */
    void fromexample(std::string image_name="dot1_grey.png") {
        frompng("../data/" + image_name);
        return;
    }

    //ToDo
    T fromtif() {
        return NULL;
    }

    //ToDo
    T frompng() {
        return NULL;
    }

    /** @brief ToDo: implement when fromtif and frompng and frombinary works so I can redirect input to correct function
     *
     */
    T frompath() {
        return NULL;
    }

    /** @brief The only use of this class is for auto instancing these three default values to a standard. Then call
     * subclass constructor to create the real values
     *
     * @param shape a vector with the desired dimension
     * @param seed seed value for the random function
     */
    void fromrandom(std::vector<uint16_t> shape = {10, 50, 50}, int seed = 42) {
        NDArray<T>::fromrandom(shape, seed);
        return;
    }

};