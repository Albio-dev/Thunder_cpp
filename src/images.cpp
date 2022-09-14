//
// Created by Aleardo on 03/08/22.
//
#include "../include/images.hpp"

// ToDo: Remove only for macos
#define AVOID_READ_DATA 0

template <class T>
class Images : public ndarray<T>
{

    friend class ndarray<T>;

    /**
     * @brief Construct a new Images object by converting an ndarray object
     * 
     * @param shape Shape of the image object
     * @param input Vector of input data
     */
    Images(std::vector<uint16_t> shape, std::vector<T> input) : ndarray<T>(shape, input) {
        if (shape.size() < 2)
            throw "Image object must have at least 2 dimensions, got 1";
    }

public:

    
    /**
     * @brief Creates an Images from a C-style array with a given shape
     *
     * @tparam T Underlaying data type
     * @param shape Final ndarray shape
     * @param input Input array
     * @return Images<T> Resulting Images
     */
    [[nodiscard]] static Images<T> fromarray(std::vector<uint16_t> shape, T *input)
    {
        // Multiplies all elements in lengths together
        uint64_t values_length = 1;
        for (auto i : shape)
            values_length *= i;
        return fromvector(shape, {input, input + values_length});
    }

    /**
     * @brief Creates an Images from a given list. Assumes 1 by list size
     *
     * @tparam T Underlaying data type
     * @param l Input list
     * @return Images<T> Resulting Images 1 by list length
     */
    [[nodiscard]] static Images<T> fromlist(std::list<T> l)
    {
        if (l.size() == 0)
            throw "List empty. Need to have a non empty list assigned.";

        return fromvector({l.size()}, {l.begin(), l.end()});
    }

    /**
     * @brief Creates an Images from a given list and with given shape
     *
     * @tparam T Underlaying data type
     * @param l Input list
     * @return Images<T> Resulting Images
     */
    [[nodiscard]] static Images<T> fromlist(std::vector<uint16_t> shape, std::list<T> l)
    {
        return fromvector(shape, {l.begin(), l.end()});
    }

    /**
     * @brief Creates an Images from a given vector. Supposes 1 by vector length
     *
     * @tparam T Underlaying data type
     * @param input Input vector
     * @return Images<T> Resulting Images
     */
    [[nodiscard]] static Images<T> fromvector(std::vector<T> input)
    {
        return fromvector({static_cast<uint16_t>(input.size())}, input);
    }
    /**
     * @brief Wrapper of the costructor from an input vector
     *
     * @param shape Desired shape of the data
     * @param input Data vector
     * @return Images<T> Resulting images object
     */
    [[nodiscard]] static Images<T> fromvector(std::vector<uint16_t> shape, std::vector<T> input)
    {
        return Images(shape, input);
    }

    /**
     * @brief Creates an Images from a given dequeue. Supposes 1 by vector length
     *
     * @tparam T Underlaying data type
     * @param input Input dequeue
     * @return Images<T> Resulting Images
     */
    [[nodiscard]] static Images<T> fromdeque(std::deque<T> input)
    {
        return fromvector({static_cast<uint16_t>(input.size())}, {input.begin(), input.end()});
    }
    /**
     * @brief Creates an Images from a given dequeue with a given shape
     *
     * @tparam T Underlaying data type
     * @param shape Final Images shape
     * @param input Input dequeue
     * @return Images<T> Resulting Images
     */
    [[nodiscard]] static Images<T> fromdeque(std::vector<uint16_t> shape, std::deque<T> input)
    {
        return fromvector(shape, {input.begin(), input.end()});
    }

    /**
     * @brief Creates an Images from a given forward_list. Supposes 1 by vector length
     *
     * @tparam T Underlaying data type
     * @param input Input forward_list
     * @return Images<T> Resulting Images
     */
    [[nodiscard]] static Images<T> fromforward_list(std::forward_list<T> input)
    {
        return fromvector({static_cast<uint16_t>(input.size())}, {input.begin(), input.end()});
    }
    /**
     * @brief Creates an Images from a given forward_list with a given shape
     *
     * @tparam T Underlaying data type
     * @param shape Final Images shape
     * @param input Input forward_list
     * @return Images<T> Resulting Images
     */
    [[nodiscard]] static Images<T> fromforward_list(std::vector<uint16_t> shape, std::forward_list<T> input)
    {
        return fromvector(shape, {input.begin(), input.end()});
    }

    /** @brief Construct class with an example image.
     * Default is "dot1_grey.png", usable images are: "dot2_grey.png" and "dot3_grey.png".
     *
     * @param image_name filename that is in /data folder
     * @return Images<T> Resulting images object
     */
    [[nodiscard]] static Images<T> fromexample(std::string image_name = "dot1_grey.png") {
        return frompng("../data/" + image_name);
    }

    /** @brief Takes a path and populate given class. Under the hood check if it is a png or tif image and
     * call the correct function. Default file type is a binary file
     *
     * @param path path to file
     * @return Images<T> Resulting images object
     */
    [[nodiscard]] static Images<T> frompath(std::string path){
        cimg_library::CImg<T> img;
        if (!std::filesystem::exists(path))
            throw "Image not in path";

        try {
            img.load(path.c_str());
        }catch (const cimg_library::CImgIOException& e) {
            throw "Image loading exception caught";
        }

        std::vector<T> output(img.width()*img.depth()*img.height());
        std::vector<uint16_t> shape = {(unsigned short int)img.width(), (unsigned short int)img.height(), (unsigned short int)img.depth()};
        std::copy(output.begin(), output.end(), img.begin());
        return Images(shape, output);


//        std::vector<T> output;
//        std::vector<uint16_t> shape = {(unsigned short int)img.width(), (unsigned short int)img.height(), 3};
//
//        for(int i=0; i < img.width(); i++){
//            for(int j=0; j < img.height(); j++){
//                output.push_back(img(i, j, 0, 0)); // R
//                output.push_back(img(i, j, 0, 1)); // G
//                output.push_back(img(i, j, 0, 2)); // B
//            }
//        }
//
//        return Images(shape, output);
    }

    /** @brief Read a tif image and load data to Image<T>
     *
     * @param path path to .tif file
     * @return Images<T> Resulting images object
     */
    [[nodiscard]] static Images<T> fromtif(std::string path)
    {
        return frompath(path);
    }

    /** @brief Read a png image and load data to Image<T>
     *
     * @param path path to .png file
     * @return Images<T> Resulting images object
     */
    [[nodiscard]] static Images<T> frompng(std::string path)
    {
        return frompath(path);
    }

    /** @brief Create image object with random values
     *
     * @param shape a vector with the desired dimension
     * @param seed seed value for the random function
     * @return Images<T> Resulting images object
     */
    [[nodiscard]] static Images<T> fromrandom(std::vector<uint16_t> shape = {10, 50, 50}, int seed = 42)
    {
        return ndarray<T>::fromrandom(shape, seed);
    }


    /**
     * @brief 
     * 
     * @param str 
     * @param suffix 
     * @return true 
     * @return false 
     */
    [[nodiscard]] bool has_suffix(const std::string &str, const std::string &suffix)
    {
        return str.size() >= suffix.size() &&
               str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
    }
    
    /**
     * @brief Utility to prepare the matrix for processing by base functions
     * Squares the matrix collapsing all dimensions but last 2 and then last 2. E.g matrix (2, 3, 2, 2) becomes (6, 4)
     * It then gets transposed so that the resulting matrix is (4, 6).
     *
     * @return NDArray<T> Square matrix transposed. Collapses all dimensions and then last 2.
     */
    [[nodiscard]] ndarray<T> prepareMat() {

        // Saving previous dimensions for restoring them later
        std::vector<uint16_t> old_shape = ndarray<T>::getShape();
        // Collapses all dimensions but last
        ndarray<T>::reshape({(uint16_t) count(), (uint16_t) (ndarray<T>::getShape()[ndarray<T>::getShape().size() - 1] *
                                                             ndarray<T>::getShape()[ndarray<T>::getShape().size() -
                                                                                    2])});

        // Get the transpose
        ndarray<T> temp = ndarray<T>::transpose(*this);

        // Restore old dimensions
        ndarray<T>::reshape(old_shape);

        return temp;
    }

    /**
     * @brief Counts how many elements with the last 2 dimensions there are.
     * e.g (2, 3, 2) = 2
     *
     * @return int Number of elements
     */
    [[nodiscard]] int count()
    {

        int output = 1;

        // Multiplies all dimensions except last 2
        for (uint16_t i = 0; i < ndarray<T>::getShape().size() - 2; i++) {
            output *= ndarray<T>::getShape()[i];
        }

        return output;
    }

    /**
     * @brief Filter wrapper from ndarray.
     *
     * @param func Boolean function to use as filter
     * @return Images<T> Resulting images object
     */
    [[nodiscard]] Images<T> filter(bool (*func)(T))
    {
        return static_cast<Images<T>>(ndarray<T>::filter(prepareMat(), func));
    }

    /**
     * @brief Gets the max of all matrices in the last 2 dimensions.
     * Given an image (2, 3, 2) -> (1, 1, 2) -> (2)
     *
     * @return Images<T> Contains maximum 2D matrix
     */
    [[nodiscard]] Images<T> max() {
        return static_cast<Images<T>>(ndarray<T>::max(prepareMat()));
    }

    /**
     * @brief Gets the min of all matrices in the last 2 dimensions.
     * Given an image (2, 3, 2) -> (1, 1, 2) -> (2)
     *
     * @return Images<T> Contains minimum 2D matrix
     */
    [[nodiscard]] Images<T> min() {
        return static_cast<Images<T>>(ndarray<T>::min(prepareMat()));
    }

    /**
     * @brief Gets the sum of all matrices in the last 2 dimensions.
     * Given an image (2, 3, 2) -> (1, 1, 2) -> (2)
     *
     * @return Images<T> Contains sum of 2D matrices
     */
    [[nodiscard]] Images<T> sum() {
        return static_cast<Images<T>>(ndarray<T>::sum(prepareMat()));
    }

    /**
     * @brief Gets the mean of all matrices in the last 2 dimensions.
     * Given an image (2, 3, 2) -> (1, 1, 2) -> (2)
     *
     * @return Images<T> Contains mean of 2D matrices
     */
    [[nodiscard]] Images<T> mean() {
        return static_cast<Images<T>>(ndarray<T>::mean(prepareMat()));
    }

    /**
     * @brief Gets the standard deviation of all least-dimensioned elements
     * Given a series (2, 3, 2) -> (1, 1, 2) -> (2)
     *
     * @return Series<T> Serie of standard deviations
     */
    [[nodiscard]] Images<T> std() {
        return static_cast<Images<T>>(ndarray<T>::std(prepareMat()));
    }

    /**
     * @brief Gets the variance of all least-dimensioned elements
     * Given a series (2, 3, 2) -> (1, 1, 2) -> (2)
     *
     * @return Series<T> Serie of variances
     */
    [[nodiscard]] Images<T> var() {
        return static_cast<Images<T>>(ndarray<T>::var(prepareMat()));
    }
};