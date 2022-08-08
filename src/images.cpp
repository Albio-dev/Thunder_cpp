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