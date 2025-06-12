cmake_minimum_required(VERSION 3.31)
project(tex C)

set(CMAKE_C_STANDARD 99)

add_library(tex STATIC library.c)
