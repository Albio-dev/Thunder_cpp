cmake_minimum_required(VERSION 3.23)
project(Proj_cpp_2022)

# At least c++17 is required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(TARGET_NAME "Thundercpp")

set(SRC
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
        doc
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

        target_link_libraries(thunder PUBLIC gcov)
        target_compile_options(thunder PUBLIC "--coverage" "-fprofile-arcs" "-ftest-coverage")

        set(TEST_SRC
                test/ndarray_test.cpp   
                test/series_test.cpp 
                test/images_test.cpp)
        set(TEST_TARGET "test_Thundercpp")
        

        add_library(test_sources OBJECT ${TEST_SRC})
        target_link_libraries(test_sources Catch2 )
        target_include_directories(test_sources PUBLIC include)

        add_executable(${TEST_TARGET} test/test.cpp )
        if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
            include_directories(SYSTEM /usr/local/Cellar/libpng/1.6.37/include/
                    /usr/local/Cellar/libtiff/4.4.0_1/include/
                    /usr/local/Cellar/jpeg/9e/include/)
            find_library(TIFF_LIB tiff HINTS /usr/local/Cellar/libtiff/4.4.0_1/lib)
            find_library(PNG_LIB png HINTS /usr/local/Cellar/libpng/1.6.37/lib)
            find_library(JPEG_LIB jpeg HINTS /usr/local/Cellar/jpeg/9e/lib)

            target_link_libraries(${TEST_TARGET} PRIVATE Catch2 test_sources ${TIFF_LIB} ${PNG_LIB} ${JPEG_LIB})
        else ()
            target_link_libraries(${TEST_TARGET} PUBLIC Catch2 gcov test_sources ${TIFF_LIB} ${PNG_LIB} ${JPEG_LIB})
            target_compile_options(${TEST_TARGET} PUBLIC "--coverage" "-fprofile-arcs" "-ftest-coverage")
        endif ()
        target_compile_options(${TEST_TARGET} PUBLIC "--coverage")
        
        #------------------
        # COVERAGE SECTION
        #------------------
        add_custom_target(coverage
                COMMAND mkdir -p ../doc/coverage
                COMMAND lcov -c -i -d .. -o baseline.info --rc lcov_branch_coverage=1
                COMMAND ./test_Thundercpp
                COMMAND lcov --capture --directory .. --output-file coverage.info --rc lcov_branch_coverage=1
                COMMAND lcov -a baseline.info -a coverage.info -o coverage_results.info --rc lcov_branch_coverage=1
                COMMAND lcov --extract coverage_results.info '*${PROJECT_SOURCE_DIR}/include/*' '${PROJECT_SOURCE_DIR}/src/*' --output-file ../doc/coverage/coverage_results.info --rc lcov_branch_coverage=1
                COMMAND lcov --list ../doc/coverage/coverage_results.info --rc lcov_branch_coverage=1
                COMMAND genhtml -o ../doc/coverage ../doc/coverage/coverage_results.info
                )

        #------------------
        # VALGRIND SECTION
        #------------------
        find_program(VALGRIND valgrind)
        
        if (VALGRIND)
            add_custom_target(valgrind
                    COMMAND ${CMAKE_COMMAND} --build . --target ${TARGET_NAME}
                    COMMAND ${VALGRIND} --leak-check=full --show-leak-kinds=all
                    --track-fds=yes --track-origins=yes ./${TARGET_NAME}
                    COMMAND ${VALGRIND} --tool=drd --show-stack-usage=yes ./${TARGET_NAME}
                    )
        endif ()
        
        #------------------
        # SANITIZERS SECTION
        #------------------
        if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
                target_link_libraries(${TARGET_NAME} PRIVATE stdc++)
        endif()
        add_compile_options(-fsanitize=address 
                        -fsanitize=undefined 
                        -fno-sanitize-recover=all 
                        -fsanitize=float-divide-by-zero 
                        -fsanitize=float-cast-overflow 
                        -fno-sanitize=null 
                        -fno-sanitize=alignment 
                        -fno-omit-frame-pointer)

        #------------------
        # STATIC ANALYZER SECTION
        #------------------
        find_program(SCAN scan-build)

        # Making everything, but wrapping with scan-build
        if (SCAN)
                add_custom_target(scan_build
                        COMMAND ${SCAN} make)
        endif()

        #------------------
        # CYCLOMATIC COMPLEXITY SECTION
        #------------------
        find_program(LIZARD lizard)
        if (LIZARD)
                add_custom_target(lizard
                        COMMAND ${LIZARD} ${PROJECT_SOURCE_DIR}/src
                        COMMAND ${LIZARD} ${PROJECT_SOURCE_DIR}/include)
        endif()

        #------------------
        # LINTER SECTION
        #------------------
        find_program(LINTER clang-tidy)

        if(LINTER)
                add_custom_target(linter
                        COMMAND clang-tidy ${PROJECT_SOURCE_DIR}/src/*.cpp -header-filter=.* -- -I${PROJECT_SOURCE_DIR}/include -std=c++17
                )
        endif()

        #------------------
        # CLANG-FORMAT SECTION
        #------------------        
        find_program(FORMAT clang-format)

        if (FORMAT)
                add_custom_target(format 
                        COMMAND ${FORMAT} -i ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/include/*.hpp ${PROJECT_SOURCE_DIR}/include/ndarray/*.i.hpp
                )
        endif()
endif()


# 
#-----------------
# INSTALL SECTION
#-----------------
install(TARGETS ${TARGET_NAME} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)

#------------------
# CLEANING SECTION
#------------------
add_custom_target(clean_all
        COMMAND ${CMAKE_COMMAND} -E echo "Cleaning doc..."
        COMMAND ${CMAKE_COMMAND} -E rm -rf ${PROJECT_SOURCE_DIR}/doc
        COMMAND ${CMAKE_COMMAND} -E echo "Cleaning bin..."
        COMMAND ${CMAKE_COMMAND} -E rm -rf ${PROJECT_SOURCE_DIR}/bin
        COMMAND ${CMAKE_COMMAND} -E echo "Done!"
        )