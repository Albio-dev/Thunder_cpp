cmake_minimum_required(VERSION 3.23)
project(Proj_cpp_2022)

# At least c++17 is required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


#set(CMAKE_CXX_FLAGS "-O0 -Wall -Wextra -pedantic -Werror")
#set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)
set(TARGET_NAME "Thundercpp")
set(BASE 
        src/ndarray/ndarray_converters.cpp
        src/ndarray/ndarray_functions.cpp
        src/ndarray/ndarray_initializers.cpp
        src/ndarray/ndarray_operator_overload.cpp
        src/ndarray/ndarray_operator_wrapper.cpp
        src/ndarray/ndarray_utils.cpp
        src/ndarray/ndarray_wrapper.cpp)
set(SRC
        ${BASE}
        src/images.cpp
        src/series.cpp)
set(LIB
        include/ndarray.hpp
        include/images.hpp
        include/series.hpp)

add_library(thunder ${LIB} ${SRC})
target_include_directories(thunder PUBLIC include)

add_compile_options(-std=c++17 -Wall -Wextra -Wpedantic -Werror -g)

add_executable(${TARGET_NAME} main.cpp)
target_link_libraries(${TARGET_NAME} PRIVATE thunder)

# Docs
add_custom_target(
        doc ALL
        COMMAND doxygen ../Doxyfile
)

# Testing
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(TEST_TARGET "test_Thundercpp")
        enable_testing()
        add_executable(${TEST_TARGET} test/ndarray_test.cpp test/series_test.cpp test/images_test.cpp)
        target_include_directories(${TEST_TARGET} PRIVATE include)
        target_link_libraries(${TEST_TARGET} PRIVATE gcov thunder)

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
endif()
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