#!/bin/bash

# Set the source files and output binary
SOURCE_FILES="main.cpp app.cpp object_item.cpp"
OUTPUT_BINARY="app"

# Compile the source files
g++ -std=c++11 -o $OUTPUT_BINARY $SOURCE_FILES `sdl2-config --cflags --libs` `pkg-config --cflags --libs cairo`

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    echo "Build successful. Output binary: $OUTPUT_BINARY"
else
    echo "Build failed."
    exit 1
fi


./app