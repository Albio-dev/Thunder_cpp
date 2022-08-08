#include <vector>
#include <cstdint>
#include <cassert>
#include <string>
#include <algorithm>
#include <random>
#include <list>

#include <iostream>
#include "series.hpp"
#include "images.hpp"


template <typename T>
class NDArray;
/*
class NDArray{
    NDArray();// Default constructor

    NDArray(const NDArray &obj);// copy constructor

    NDArray(NDArray&&obj);// move constructor

    NDArray& operator=(const NDArray &obj);// copy assign operator

    NDArray& operator=(NDArray &&obj);// move assign operator

    ~NDArray();// destructor
};*/