cmake_minimum_required(VERSION 3.23)
project(Proj_cpp_2022)


set(CMAKE_CXX_STANDARD 17)              # Use C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)     # Require (at least) it
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "-O0 -Wall -Wextra -pedantic -Werror -lpng -ltiff -ljpeg")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

link_directories(/usr/lib/x86_64-linux-gnu)
# find_library(PNG png)
# find_library(TIFF tiff HINT /usr/lib/x86_64-linux-gnu)
# find_library(JPEG jpeg)

find_package(TIFF REQUIRED)
set(SOURCE_FILES src/main.cpp)
add_executable(CImgProject ${SOURCE_FILES})

target_link_libraries(CImgProject PUBLIC ${PNG} ${TIFF} ${JPEG})
add_compile_options(CImgProject "-lpng -ltiff -ljpeg")
set_target_properties( CImgProject PROPERTIES COMPILE_FLAGS "-lpng -ltiff -ljpeg")


# # You can alter these according to your needs, e.g if you don't need to display images - set(YOU_NEED_X11 0)
# set(YOU_NEED_X11 1)
# set(YOU_NEED_PNG 0)
# set(YOU_NEED_JPG 0)

# if(${YOU_NEED_X11} EQUAL 1)
#     message(STATUS "Looking for X11...")
#     find_package(X11 REQUIRED)
#     include_directories(${X11_INCLUDE_DIR})
#     target_link_libraries(CImgProject ${X11_LIBRARIES})
# #else()
#     #target_compile_definitions(CImgProject PRIVATE cimg_display=0)
# endif()

# if(${YOU_NEED_JPG} EQUAL 1)
#     message(STATUS "Looking for libjpg...")
#     find_package(JPEG REQUIRED)
#     include_directories(${JPEG_INCLUDE_DIR})
#     target_link_libraries (CImgProject ${JPEG_LIBRARY})
#     target_compile_definitions(CImgProject PRIVATE cimg_use_jpeg=1)
# endif()

# if(${YOU_NEED_PNG} EQUAL 1)
#     message(STATUS "Looking for libpng...")
#     find_package(PNG REQUIRED)
#     include_directories(${PNG_INCLUDE_DIRS})
#     target_link_libraries (CImgProject ${PNG_LIBRARIES})
#     target_compile_definitions(CImgProject PRIVATE cimg_use_png=1)
# endif()

#target_compile_options(CImgProject "-png -lm -lpthread -lX11")