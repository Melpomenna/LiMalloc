![](./misc/images/project.png)

# LiMalloc

[![Build Status](https://dev.azure.com/mellpomeNn/LiMalloc/_apis/build/status%2FMelpomenna.LiMalloc?branchName=main)](https://dev.azure.com/mellpomeNn/LiMalloc/_build/latest?definitionId=2&branchName=main)

LiMalloc is a custom memory allocator library written in C. It is designed for efficient and flexible memory management, suitable for use in performance-critical applications.

## Features

- Custom memory allocation and deallocation
- Optimized for speed and low fragmentation
- Thread-safe (if enabled)
- Configurable block sizes and alignment
- C++20 compatible
- C 11 compatible

## Getting Started

### Prerequisites and Usings

- CMake >= 3.19
- Visual Studio 2022, Apple Clang, or GCC for building
- Work on Windows, Linux and MacOS is supported
- [GoogleTest (GTest)](https://github.com/google/googletest) for unit testing
- [Google Benchmark](https://github.com/google/benchmark) for performance testing

### Building the Project

1. Clone the repository:
```sh
    git clone <repository-url>
    cd LiMalloc
```

2. 
Build on Windows:
```sh
    cmake --preset=release-Windows
    cmake --build . --preset=release-Windows
```
Build on Linux/MacOS:
```sh
    make
    make build
``` 

### Running Tests

Unit tests are written using GTest. To run the tests:
On Windows
```sh
ctest --preset=release-Windows
```

On Linux/MacOS:
```sh
make tests
```

## Usage

Include the LiMalloc header in your project and use the provided allocator classes/functions to manage memory.
## Contributing

Contributions are welcome! Please open issues or submit pull requests for bug fixes or new features.

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.
