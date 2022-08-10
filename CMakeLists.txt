cmake_minimum_required(VERSION 3.23)
project(Proj_cpp_2022)

# At least c++17 is required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(TARGET_NAME "Thundercpp")

# set(BASE 
#         src/ndarray/ndarray_constructors.cpp
#         src/ndarray/ndarray_converters.cpp
#         src/ndarray/ndarray_functions.cpp
#         src/ndarray/ndarray_initializers.cpp
#         src/ndarray/ndarray_operator_overload.cpp
#         src/ndarray/ndarray_operator_wrapper.cpp
#         src/ndarray/ndarray_utils.cpp
#         src/ndarray/ndarray_wrapper.cpp)
set(SRC
        # ${BASE}
        src/images.cpp
        src/series.cpp)
set(LIB
        include/ndarray.hpp
        include/images.hpp
        include/series.hpp)

add_library(thunder ${SRC})
target_include_directories(thunder PUBLIC include)

add_compile_options(-std=c++17 -Wall -Wextra -Wpedantic -Werror -g)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    include_directories(SYSTEM /usr/local/Cellar/libpng/1.6.37/include/
            /usr/local/Cellar/libtiff/4.4.0_1/include/
            /usr/local/Cellar/jpeg/9e/include/)
    find_library(TIFF_LIB tiff HINTS /usr/local/Cellar/libtiff/4.4.0_1/lib)
    find_library(PNG_LIB png HINTS /usr/local/Cellar/libpng/1.6.37/lib)
    find_library(JPEG_LIB jpeg HINTS /usr/local/Cellar/jpeg/9e/lib)
else ()
    set(TIFF_LIB "tiff")
    set(PNG_LIB "png")
    set(JPEG_LIB "jpeg")
endif ()

add_executable(${TARGET_NAME} main.cpp)

target_link_libraries(${TARGET_NAME} PRIVATE thunder ${TIFF_LIB} ${PNG_LIB} ${JPEG_LIB})


# Docs
add_custom_target(
        doc ALL
        COMMAND doxygen ../Doxyfile
)

# Testing

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(TEST_TARGET "test_Thundercpp")


    enable_testing()
    add_executable(${TEST_TARGET} test/images_test.cpp )
#    add_executable(${TEST_TARGET} test/series_test.cpp ${SRC})
#    target_link_libraries(${TEST_TARGET} -Wl,--whole-archive)

#    add_executable(${TEST_TARGET} test/ndarray_test.cpp test/series_test.cpp test/images_test.cpp ${SRC})

    if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        find_library(CATCH2 catch2 HINTS /usr/local/Cellar/catch2/3.1.0/lib)
    else ()
        set(CATCH2 "")
    endif ()


    target_include_directories(${TEST_TARGET} PRIVATE include)
    target_link_libraries(${TEST_TARGET} PRIVATE thunder ${CATCH2})

    add_custom_target(build_and_test
            COMMAND ${CMAKE_COMMAND} --build ${PROJECT_BINARY_DIR} --target ${TEST_TARGET}
            COMMAND ${CMAKE_COMMAND} --build ${PROJECT_BINARY_DIR} --target test
            )


    # set(CMAKE_INSTALL_PREFIX ".")
    # install(TARGETS ${TARGET_NAME} DESTINATION ../bin)

    # add_custom_target(coverage ALL
    #         COMMAND mkdir -p ../doc/coverage
    #         COMMAND lcov --capture --directory .. --output-file coverage.info
    #         COMMAND lcov --extract coverage.info '*/src/*' --output-file ../doc/coverage/coverage.info
    #         COMMAND lcov --list ../doc/coverage/coverage.info
    #         COMMAND genhtml -o ../doc/coverage ../doc/coverage/coverage.info
    #         )
endif ()
# Testing

# add_executable(test_ndarray test/ndarray_test.cpp)
# target_compile_options(test_ndarray PRIVATE --coverage)
# target_link_libraries(test_ndarray PRIVATE gcov)

# add_executable(test_series  test/series_test.cpp)
# target_compile_options(test_series PRIVATE --coverage)
# target_link_libraries(test_series PRIVATE gcov)

# add_executable(test_images  test/images_test.cpp)
# target_compile_options(test_images PRIVATE --coverage)
# target_link_libraries(test_images PRIVATE gcov)

# add_custom_target(
#         test ALL
#         COMMAND ./test_ndarray
#         COMMAND ./test_series
#         COMMAND ./test_images
# )

# add_custom_target(
#         format ALL
#         COMMAND clang-format --style=file:../.clang-tidy -i  ../src/*
# )


#COMMAND ../utils/tester.sh)