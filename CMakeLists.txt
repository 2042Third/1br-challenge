cmake_minimum_required(VERSION 3.28)
project(OneBillionRows)

set(CMAKE_CXX_STANDARD 17)

# Add the include directory to the include path
include_directories(
    .
    cpp-mmf
)

add_executable(OneBillionRows
    main.cpp
    cc20_file.cpp
    cpp-mmf/memory_mapped_file.cpp
    FileReader.cpp
    FileReader.h
    City.h
    City.cpp
)
