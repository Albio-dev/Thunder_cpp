cmake_minimum_required(VERSION 3.23)
project(Proj_cpp_2022)


set(CMAKE_CXX_STANDARD 17)              # Use C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)     # Require (at least) it

set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "-O0 -Wall -Wextra -pedantic -Werror")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

set(TARGET_NAME "Thunder")
add_executable(${TARGET_NAME} src/main.cpp src/ndarray.cpp src/series.cpp src/images.cpp)
target_compile_options(${TARGET_NAME} PRIVATE --coverage)
target_link_libraries(${TARGET_NAME} PRIVATE gcov)

# Testing
add_executable(test_ndarray test/ndarray_test.cpp)
target_compile_options(test_ndarray PRIVATE --coverage)
target_link_libraries(test_ndarray PRIVATE gcov)

add_executable(test_series  test/series_test.cpp)
target_compile_options(test_series PRIVATE --coverage)
target_link_libraries(test_series PRIVATE gcov)

add_custom_target(
        test ALL
        COMMAND ./test_ndarray
        COMMAND ./test_series
)

# add_custom_target(
#         format ALL
#         COMMAND clang-format --style=file:../.clang-tidy -i  ../src/*
# )

add_custom_target(
        doc ALL
        COMMAND doxygen ../Doxyfile
)


set(CMAKE_INSTALL_PREFIX ".")
install(TARGETS ${TARGET_NAME} DESTINATION ../bin)

add_custom_target(coverage ALL
                COMMAND mkdir -p ../doc/coverage
                COMMAND lcov --capture --directory .. --output-file coverage.info
                COMMAND lcov --extract coverage.info '*/src/*' --output-file ../doc/coverage/coverage.info
                COMMAND lcov --list ../doc/coverage/coverage.info
                COMMAND genhtml -o ../doc/coverage ../doc/coverage/coverage.info 
                )


                #COMMAND ../utils/tester.sh)       