cmake_minimum_required(VERSION 3.31)
project(tex C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests/$<CONFIGURATION>")


include_directories(include)

add_subdirectory("thirdparty/SDL")

add_library(tex SHARED
        src/load.c
        src/stb_image.h
        include/tex/load.h
        src/hash.cpp
        src/texer.c
)
target_link_libraries(tex SDL3::Headers SDL3::SDL3)
add_subdirectory(tests)

