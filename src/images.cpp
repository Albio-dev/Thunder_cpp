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

    //ToDo
    std::vector<int> frombinary(std::string path) {
        std::ofstream myfile;
        myfile.open(path);
        myfile << "Writing this to a file.\n";
        myfile.close();
        std::string line;
        std::ifstream myfile2(path);
        if (myfile2.is_open()) {
            while (getline(myfile2, line)) {
                std::cout << line << '\n';
            }
            myfile2.close();
        } else std::cout << "Unable to open file";


        return std::vector<int>();

        std::ifstream in(path, std::ios::binary);
        while (!in.eof()) {
            std::string text;

            getline(in, text);
            std::cout << "" << text << "\n";
        }

        std::vector<int> numbers;
        int number;
        while (in >> number)
            numbers.push_back(number);


        return numbers;

    }

    //ToDo
    T fromtif() {
        return NULL;
    }

    //ToDo
    T frompath() {
        return NULL;
    }

    //ToDo
    T fromfile() {
        return NULL;
    }

    //ToDo
    T frompng() {
        return NULL;
    }

    /** @brief
 *
 */
    void fromrandom(std::vector<uint16_t> shape = {10, 50, 50}, int npartitions = 1, int seed = 42) {
        NDArray<T>::fromrandom(shape, npartitions, seed);
        return;
    }

};