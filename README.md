# Thunder

Porting of the original [thunder](https://github.com/thunder-project/thunder) project in Modern C++ (C++17).

## Author

Alberto Carli
Aleardo Lodi VR 463652

## Build and Controls
### Build
Use `cmake` >= 3.23.3 to build the project, simply launch
```bash
mkdir build
cmake -S . -B build
cd build
```

and you can have and use 3 targets:

* `Thundercpp`: Build target thunder 
* `doc`: Creates a `doc` directory containing the HTML documentation
* `coverage`: ToDo
* `test_Thundercpp`: ToDo
* `format`:  ToDo test this

Run them with

```bash
make Thundercpp
make doc
```

If the `-DCMAKE_BUILD_TYPE=Debug` is specified, the following targets will be available:

```bash
make test_Thundercpp
make coverage
make format
```

You can also use the `clean_all` clean the project from the `bin` and `doc` directories.