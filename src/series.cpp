//
// Created by Aleardo on 03/08/22.
//

#include "series.hpp"

template<class T>
class Series: public NDArray<T>{
public:
    Series() = default;

    T getPosition(std::vector<uint16_t> indexes) {

        NDArray<T>::getPosition(indexes);
        return NULL;
    }

    //ToDo
    T frombinary() {
        return NULL;
    }

    /** @brief
     *
     */
    /* Disabled for compile errors
    void fromrandom(std::vector<uint16_t> shape={100, 10}, int npartitions=1, int seed=42) {
        NDArray<T>::fromrandom(shape, npartitions, seed);
        return;
    }*/


    /** @brief Loads series data from text files. Assumes data are formatted as rows,
     * where each record is a row of numbers separated by spaces e.g. 'v v v v v'.
     * You can optionally specify a fixed number of initial items per row to skip / discard.
     *
     *
     */
    void fromtext(std::string path) {
        std::string line;
        std::ifstream myfile2 (path);
        if (myfile2.is_open())
        {
            while ( getline (myfile2,line) )
            {
                std::istringstream stream(line);
                std::string segment;

                while(std::getline(stream, segment, ' '))
                {
                    std::cout << std::stod(segment) << " ";
                    this->value.push_back(std::stod(segment));
                }

            }

            myfile2.close();
        }else{
            throw "Unable to open file. Some error occurred!";
        }

        return ;
    }

};