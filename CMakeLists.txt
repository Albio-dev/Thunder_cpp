cmake_minimum_required(VERSION 3.23)
project(Proj_cpp_2022)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

# Use C++11
set(CMAKE_CXX_STANDARD 11)
# Require (at least) it
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Don't use e.g. GNU extension (like -std=gnu++11) for portability
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS " -g -O0 -Wall -Wextra -pedantic -Werror -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

#set(OBJECT_DIR ${CMAKE_BINARY_DIR}/CMakeFiles/RunAdder.dir)
#message("-- Object files will be output to: ${OBJECT_DIR}")

#SET(GCC_COVERAGE_COMPILE_FLAGS "-g -O0 -coverage -fprofile-arcs -ftest-coverage")
#SET(GCC_COVERAGE_LINK_FLAGS    "-coverage -lgcov")

#SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
#SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )

set(TARGET_NAME "outfile")
add_executable(test_outfile src/test_coverage.cpp)
add_executable(${TARGET_NAME} src/helloworld.cpp)

#target_compile_options(test_outfile PRIVATE -coverage)

enable_testing()
add_test(NAME Test1
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
        COMMAND ./outfile) # command can be anything

add_custom_target(
        format ALL
        COMMAND clang-format --style=file:../.clang-tidy -i  ../src/*
)
add_custom_target(
        doc ALL
        COMMAND doxygen ../Doxyfile
)

set(CMAKE_INSTALL_PREFIX ".")
install(TARGETS ${TARGET_NAME} DESTINATION ../bin)

#add_custom_target(
#        install ALL
#        COMMAND mv ${TARGET_NAME} ../bin/${TARGET_NAME}
#)

#set_tests_properties(Test1
#                     PROPERTIES PASS_REGULAR_EXPRESSION "Hello Worldd!")