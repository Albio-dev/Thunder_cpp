cmake_minimum_required(VERSION 3.23)
project(Proj_cpp_2022)


set(CMAKE_CXX_STANDARD 17)              # Use C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)     # Require (at least) it
set(CMAKE_CXX_EXTENSIONS OFF)



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -Wextra -pedantic -Werror")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

find_package(TIFF REQUIRED)


set(SOURCE_FILES src/main.cpp)
add_executable(CImgProject ${SOURCE_FILES})

#target_compile_options(CImgProject -ltiff)

target_link_libraries(CImgProject tiff png jpeg)
