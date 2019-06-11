# OpenCV-YAMLHelper
Minimal header-only library that can easily read YAML files using YAML parser implemented on OpenCV

- You can easily read data that written in YAML files
    - You do **NOT** have to deal with cv::FileStorage and cv::FileNode directly
- You can directly load data into a struct (actualy, implemented by a class)

## Requirement
- OpenCV **3.0** or higher
- A C++ compiler with **C++14** or higher support
- CMake **3.0** or higher (for compiling example program)

## Usage
Please read source code of example program and `include/YAMLHelper.hpp`

### Example Program
The program can be run with following commands

``` sh
$ git clone git@github.com:kyk0910/OpenCV-YAMLHelper.git
$ cd OpenCV-YAMLHelper/example
$ mkdir build && cd build
$ cmake ..
$ make
$ ./example
```

## License
MIT
