//
// Created by Aleardo on 03/08/22.
//

#include "series.hpp"

template<class T>
class Series: public NDArray<T>{
public:
    Series() = default;

    Series(std::vector<uint16_t> shape, std::vector<T> input){
        NDArray<T>::shape = shape;
        NDArray<T>::value = input;           
    }

    static Series<T> fromArray(std::vector<uint16_t> shape, std::vector<T> input){
        return Series<T>(shape, input);
    }

    T getPosition(std::vector<uint16_t> indexes) {

        NDArray<T>::getPosition(indexes);
        return NULL;
    }

    //ToDo
    T frombinary() {
        return NULL;
    }

    /** @brief The only use of this class is for auto instancing these three default values to a standard. Then call
     * subclass constructor to create the real values
     *
     * @param shape a vector with the desired dimension
     * @param seed seed value for the random function
     */
    void fromrandom(std::vector<uint16_t> shape={100, 10}, int seed=42) {
        NDArray<T>::fromrandom(shape, seed);
        return;
    }


    /** @brief Loads series data from text files. Assumes data are formatted as rows,
     * where each record is a row of numbers separated by spaces e.g. 'v v v v v'.
     * You can optionally specify a fixed number of initial items per row to skip / discard.
     *
     *
     */
    void fromtext(std::string path) {
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
                        this->value.push_back(std::stof(segment));

                    }
                    if (std::is_same<T, int>::value) {
                        std::cout << std::stoi(segment) << " ";
                        this->value.push_back(std::stoi(segment));
                    }
                }

            }

            text_file.close();
        }else{
            throw "Unable to open file. Some error occurred!";
        }

        return ;
    }

    /** @brief Construct this class with a default base series from random.
     *
     */
    void fromexample() {
        fromrandom({25}, 42);
        return;
    }

    /**
     * @brief Utility to prepare the matrix for processing by base functions
     * Squares the matrix collapsing all dimensions but last. E.g matrix (2, 3, 2) becomes (6, 2)
     * It then gets transposed so that the resulting matrix is (2, 6).
     * 
     * @return NDArray<T> Square matrix transposed. Collapses all dimensions except last.
     */
    NDArray<T> prepareMat(){

        // Saving previous dimensions for restoring them later
        std::vector<uint16_t> old_shape = NDArray<T>::shape;
        // Collapses all dimensions but last
        NDArray<T>::reshape({count(), NDArray<T>::getShape()[NDArray<T>::getShape().size()-1]});

        // Get the transpose
        NDArray<T> temp = NDArray<T>::transpose(*this);

        // Restore old dimensions
        NDArray<T>::reshape(old_shape);

        return temp;
    }

    int count(){
        
        int output = 1;

        for (int i = 0; i < NDArray<T>::getShape().size() -1; i++){
            output *= NDArray<T>::shape[i];
        }

        return output;
    }

    Series<T> filter(){
        return NDArray<T>::filter(prepareMat());
    }
    Series<T> max()
    {
        return NDArray<T>::max(prepareMat());
    }
    Series<T> min()
    {
        return NDArray<T>::min(prepareMat());
    }
    Series<T> mean()
    {
        return NDArray<T>::mean(prepareMat());
    }
    Series<T> std()
    {
        return NDArray<T>::std(prepareMat());
    }
    Series<T> sum()
    {
        return NDArray<T>::sum(prepareMat());
    }
    Series<T> var()
    {
        return NDArray<T>::var(prepareMat());
    }
};