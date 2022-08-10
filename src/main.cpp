#include <stdio.h>
#include <iostream>


#define cimg_display 0
#define cimg_use_png 1
#define cimg_use_tiff
#define cimg_use_jpeg 1

#define cimg_OS 1

#include "../third_party/CImg.h"

using namespace std;
using namespace cimg_library;

int main() {

    CImg<float> image("../data/singlelayer_png/dot1_grey.png");

    return 0;
}