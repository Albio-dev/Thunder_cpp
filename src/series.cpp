//
// Created by Aleardo on 03/08/22.
//

#include "../include/series.hpp"

template<class T>
class Series: public ndarray<T>{
    //Series() = default;

    friend class ndarray<T>;

    Series(std::vector<uint16_t> shape, std::vector<T> input) : ndarray<T>(shape, input){}
public:
    /**
     * @brief Utility to prepare the matrix for processing by base functions
     * Squares the matrix collapsing all dimensions but last. E.g matrix (2, 3, 2) becomes (6, 2)
     * It then gets transposed so that the resulting matrix is (2, 6).
     *
     * @return NDArray<T> Square matrix transposed. Collapses all dimensions except last.
     */
    ndarray<T> prepareMat()
    {

        // Saving previous dimensions for restoring them later
        std::vector<uint16_t> old_shape = ndarray<T>::getShape();
        // Collapses all dimensions but last
        ndarray<T>::reshape({(uint16_t)count(), ndarray<T>::getShape()[ndarray<T>::getShape().size() - 1]});

        // Get the transpose
        ndarray<T> temp = ndarray<T>::transpose(*this);

        // Restore old dimensions
        ndarray<T>::reshape(old_shape);

        return temp;
    }



    
    T getPosition(std::vector<uint16_t> indexes) {

        ndarray<T>::getPosition(indexes);
        return NULL;
    }

    static Series<T> fromarray(std::vector<uint16_t> shape, std::vector<T> input)
    {
        return Series<T>(shape, input);
    }

    /** @brief The only use of this class is for auto instancing these three default values to a standard. Then call
     * subclass constructor to create the real values
     *
     * @param shape a vector with the desired dimension
     * @param seed seed value for the random function
     */
    static Series<T> fromrandom(std::vector<uint16_t> shape = {100, 10}, int seed = 42)
    {
        return static_cast<Series<T>>(ndarray<T>::fromrandom(shape, seed));
    }

    /** @brief Loads series data from text files. Assumes data are formatted as rows,
     * where each record is a row of numbers separated by spaces e.g. 'v v v v v'.
     * You can optionally specify a fixed number of initial items per row to skip / discard.
     *
     *
     */
    static Series<T> fromtext(std::string path)
    {
        std::vector<T> output;
        std::string line;
        std::ifstream text_file (path);
        if (text_file.is_open())
        {
            while ( getline (text_file,line) )
            {
                std::istringstream stream(line);
                std::string segment;

                while(std::getline(stream, segment, ' '))
                {
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
        }else{
            throw "Unable to open file. Some error occurred!";
        }

        return Series<T>({static_cast<uint16_t>(output.size())}, output);
    }

    /** @brief Construct this class with a default base series from random.
     *
     */
    static Series<T> fromexample()
    {
        return fromrandom({25}, 42);
    }

    

    /**
     * @brief Counts how many least-dimensioned elements there are. 
     * e.g (2, 3, 2) = 6
     * 
     * @return int Number of least dimensioned elements
     */
    int count(){
        
        int output = 1;

        // Multiplies all dimensions except last
        for (uint16_t i = 0; i < ndarray<T>::getShape().size() -1; i++){
            output *= ndarray<T>::getShape()[i];
        }

        return output;
    }


    Series<T> filter(bool (*func)(T)){
        return static_cast<Series<T>>(ndarray<T>::filter(prepareMat(), func));
    }
    /**
     * @brief Gets the max of all least-dimensioned elements
     * Given a series (2, 3, 2) -> (1, 1, 2) -> (2)
     * 
     * @return Series<T> Serie of max elements 
     */
    Series<T> max()
    {
        return static_cast<Series<T>>(ndarray<T>::max(prepareMat()));
    }
    /**
     * @brief Gets the min of all least-dimensioned elements
     * Given a series (2, 3, 2) -> (1, 1, 2) -> (2)
     * 
     * @return Series<T> Serie of min elements 
     */
    Series<T> min()
    {
        return static_cast<Series<T>>(ndarray<T>::min(prepareMat()));
    }
    /**
     * @brief Gets the sum of all least-dimensioned elements
     * Given a series (2, 3, 2) -> (1, 1, 2) -> (2)
     * 
     * @return Series<T> Serie of sum elements 
     */
    Series<T> sum()
    {
        return static_cast<Series<T>>(ndarray<T>::sum(prepareMat()));
    }
    /**
     * @brief Gets the mean of all least-dimensioned elements
     * Given a series (2, 3, 2) -> (1, 1, 2) -> (2)
     * 
     * @return Series<T> Serie of means 
     */
    Series<T> mean()
    {
        return static_cast<Series<T>>(ndarray<T>::mean(prepareMat()));
    }
    /**
     * @brief Gets the standard deviation of all least-dimensioned elements
     * Given a series (2, 3, 2) -> (1, 1, 2) -> (2)
     *
     * @return Series<T> Serie of standard deviations
     */
    Series<T> std()
    {
        return static_cast<Series<T>>(ndarray<T>::std(prepareMat()));
    }
    /**
     * @brief Gets the variance of all least-dimensioned elements
     * Given a series (2, 3, 2) -> (1, 1, 2) -> (2)
     *
     * @return Series<T> Serie of variances
     */
    Series<T> var()
    {
        return static_cast<Series<T>>(ndarray<T>::var(prepareMat()));
    }
};