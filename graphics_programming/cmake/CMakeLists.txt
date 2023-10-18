# Set the C compiler (replace with the actual path to your C compiler)
set(CMAKE_C_COMPILER "C:/msys64/mingw64/bin/gcc.exe")

# Set the C++ compiler (replace with the actual path to your C++ compiler)
set(CMAKE_CXX_COMPILER "C:/msys64/mingw64/bin/g++.exe")

# Specify the generator to use (GNU Make)
set(CMAKE_GENERATOR "Unix Makefiles")

# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Define project
project(graphics_programming)

# Add source files
file(GLOB SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/../src/*.cpp
    ${CMAKE_SOURCE_DIR}/../src/*.c
)

# Set the desired output directory for the executable
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/../build")

# Create an executable from source files
add_executable(main ${SOURCE_FILES})

# Add include directories for headers
target_include_directories(main PRIVATE
    ${CMAKE_SOURCE_DIR}/../dependencies/include
)

# Link libraries
target_link_libraries(main PRIVATE
    ${CMAKE_SOURCE_DIR}/../dependencies/lib/libglfw3.a
    opengl32
    gdi32
)
