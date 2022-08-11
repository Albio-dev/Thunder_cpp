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

        #add_subdirectory(third_party/Catch2)
        set(CATCH_INCLUDE_DIR third_party/catch)
        add_library(Catch2 INTERFACE)
        target_include_directories(Catch2 INTERFACE ${CATCH_INCLUDE_DIR})

        if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
            set(CATCH_INCLUDE_DIR third_party)
        else ()
            set(CATCH_INCLUDE_DIR third_party/catch2)
        endif ()
        target_include_directories(Catch2 INTERFACE ${CATCH_INCLUDE_DIR})



        set(TEST_SRC
                test/ndarray_test.cpp   
                test/series_test.cpp 
                test/images_test.cpp)
        set(TEST_TARGET "test_Thundercpp")
        

        add_library(test_sources OBJECT ${TEST_SRC})
        target_link_libraries(test_sources Catch2 )
        target_include_directories(test_sources PRIVATE include)

        add_executable(${TEST_TARGET} test/test.cpp )
        if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
            target_link_libraries(${TEST_TARGET} PRIVATE Catch2 test_sources )
        else ()
            target_link_libraries(${TEST_TARGET} PRIVATE Catch2 gcov test_sources )
        endif ()
        target_compile_options(${TEST_TARGET} PUBLIC "--coverage")


        add_custom_target(coverage ALL
                COMMAND mkdir -p ../doc/coverage
                COMMAND lcov -c -i -d .. -o baseline.info --rc lcov_branch_coverage=1
                COMMAND ./test_Thundercpp
                COMMAND lcov --capture --directory .. --output-file coverage.info --rc lcov_branch_coverage=1
                COMMAND lcov -a baseline.info -a coverage.info -o coverage_results.info --rc lcov_branch_coverage=1
                COMMAND lcov --extract coverage_results.info '*${PROJECT_SOURCE_DIR}/include/*' '${PROJECT_SOURCE_DIR}/src/*' --output-file ../doc/coverage/coverage_results.info --rc lcov_branch_coverage=1
                COMMAND lcov --list ../doc/coverage/coverage_results.info --rc lcov_branch_coverage=1
                COMMAND genhtml -o ../doc/coverage ../doc/coverage/coverage_results.info
                )
endif()

# add_custom_target(
#         format ALL
#         COMMAND clang-format --style=file:../.clang-tidy -i  ../src/*
# )
