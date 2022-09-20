# Thunder

Porting of the original [thunder](https://github.com/thunder-project/thunder) project in Modern C++ (C++17).
A data manipulation library for C++

## Authors

Alberto Carli VR473845
Aleardo Lodi VR463652

## Build and Controls
### Prerequisites
A few dependancies are needed to build:
* `libpng`
* `jpeglib`
* `libtiff`

On linux you could install those by simply running
```bash
sudo apt install libpng-dev jpeglib-dev libtiff-dev
```

### Build
Use `cmake` >= 3.23.3 to build the project, simply launch
```bash
mkdir build
cmake -S . -B build
```
Your executable will be in the bin folder.

Available targets to make in build folder:

* `install`: Builds executable in bin folder
* `Thundercpp`: Build target thunder 
* `doc`: Creates a `doc` directory containing the HTML documentation
* `clean_all`: Clean the project from the `bin` and `doc` directories.

Example usage:

```bash
make -C build install
make -C build Thundercpp
make -C build doc
```

### Test
## Prerequisites
To compile in debug mode the following programs will need to be available on the system:
* lcov

by using 
```bash
sudo apt install lcov
```

If `-DCMAKE_BUILD_TYPE=Debug` is specified while building the makefile, like so
```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
```
the following targets will be available:

* `test_Thundercpp`: Compiles test programs
* `coverage`: Executes tests to calculate coverage. Results are in doc/coverage folder in html format
* `valgrind`: Runs valgrind to check memory leakage
* `scan_build` (static analyzer): Runs a static analysis for bugs with scan_build
* `lizard` (cyclomatic complexity): Runs lizard and prints cyclomatic complexity data
* `linter` (clang-tidy): Applies clang-tidy to the header files
* `format`: Applies clang-format to project

sanitizers are automatically added to compile options:
* -fsanitize=address 
* -fsanitize=undefined 
* -fno-sanitize-recover=all 
* -fsanitize=float-divide-by-zero 
* -fsanitize=float-cast-overflow 
* -fno-sanitize=null 
* -fno-sanitize=alignment 
* -fno-omit-frame-pointer

Example usage:
```bash
make test_Thundercpp
make coverage
make format
```
