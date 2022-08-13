//
// Created by Aleardo on 03/08/22.
//
#pragma once

#ifndef PROJ_CPP_2022_IMAGES_HPP
#define PROJ_CPP_2022_IMAGES_HPP

#define cimg_display 0
#define cimg_use_png 1
#define cimg_use_tiff 1
#define cimg_use_jpeg 1

#define cimg_OS 1

#include "../third_party/CImg.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

template <class T> class Images;

#include "ndarray.hpp"

#endif // PROJ_CPP_2022_IMAGES_HPP