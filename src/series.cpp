//
// Created by Aleardo on 03/08/22.
//

#include "series.hpp"

template<class T> class Series: public NDArray<T>{
    T getPosition(std::vector<uint16_t> indexes) {
        
        NDArray<T>::getPosition(indexes);
        return NULL;
    }

    //ToDo
    T frombinary() {
        return NULL;
    }


    //ToDo
    T fromtext() {
        return NULL;
    }

};