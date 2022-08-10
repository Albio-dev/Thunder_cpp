cmake_minimum_required(VERSION 3.23)
project(Proj_cpp_2022)


set(CMAKE_CXX_STANDARD 17)              # Use C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)     # Require (at least) it

set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "-O0 -Wall -Wextra -pedantic -Werror")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

set(TARGET_NAME "Thunder")
add_executable(${TARGET_NAME} src/main.cpp)
-L/usr/X11R6/lib -lm -lpthread -lX11
#target_link_libraries(${TARGET_NAME} PRIVATE libpng-dev libtiff-dev libjpeg-dev )
