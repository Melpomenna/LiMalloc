#!/bin/bash

CMAKE_VERSION=$(cmake --version | awk '{print $3; exit}')

version_ge() {
    IFS=. read -r -a ver1 <<< "$1"
    IFS=. read -r -a ver2 <<< "$2"
    
    for i in 0 1; do
        if [[ "${ver1[i]}" -gt "${ver2[i]}" ]]; then
            return 0
        elif [[ "${ver1[i]}" -lt "${ver2[i]}" ]]; then
            return 1
        fi
    done
    return 0
}

if command -v cmake > /dev/null 2>&1; then
    if version_ge "$CMAKE_VERSION" "3.6"; then
        echo "CMake version: $CMAKE_VERSION. All right!"
    else
        echo "CMake version: $CMAKE_VERSION must be greater. Trying to update..."
        brew install cmake
        CMAKE_VERSION=$(cmake --version | awk '{print $3; exit}')
        if version_ge "$CMAKE_VERSION" "3.6"; then
            echo "CMake version: $CMAKE_VERSION. All right!"
        else
            echo "Please upgrade CMake to version 3.6 or greater."
            exit 1
        fi
    fi
else
    if command -v brew > /dev/null 2>&1; then
        echo "CMake not found. Installing CMake..."
        brew install cmake
    else
        echo "Please install Homebrew to install CMake: https://brew.sh/"
        exit 1
    fi
fi