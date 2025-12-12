cmake_minimum_required(VERSION 4.1)
project(MapReduceInC C)

set(CMAKE_C_STANDARD 11)

# Use CMAKE_SOURCE_DIR to put the bin folder in your main project folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

add_executable(
        #MapReduceInC main.c
        main.c
        LinkedListImplementation.c
        ReadFileReturnArrayOfWords.c
)
