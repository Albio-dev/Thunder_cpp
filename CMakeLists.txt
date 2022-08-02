cmake_minimum_required(VERSION 3.23)
project(Proj_cpp_2022)


set(CMAKE_CXX_STANDARD 17)              # Use C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)     # Require (at least) it

set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS " -g -O0 -Wall -Wextra -pedantic -Werror -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

set(TARGET_NAME "outfile")
add_executable(${TARGET_NAME} src/main.cpp src/ndarray.cpp)

# Testing
add_executable(test_outfile src/test_coverage.cpp)
target_compile_options(test_outfile PRIVATE -coverage)

add_custom_target(
        test ALL
        COMMAND ./test_outfile
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
