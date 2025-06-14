cmake_minimum_required(VERSION 3.31)
project(tex C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests/$<CONFIGURATION>")


include_directories(include)
set(PUBLIC_PATH include/tex)
set(SOURCE_PATH src)

add_subdirectory("thirdparty/SDL")



set(HEADERS     ${PUBLIC_PATH}/texer.h
                ${PUBLIC_PATH}/texer.h
                ${PUBLIC_PATH}/error.h)

set(SOURCES     ${SOURCE_PATH}/load.c
                ${SOURCE_PATH}/load.h
                ${SOURCE_PATH}/common.c
                ${SOURCE_PATH}/common.h
                ${SOURCE_PATH}/texer.c
                ${SOURCE_PATH}/error.c
                ${SOURCE_PATH}/stb_image.h)

add_library(tex SHARED
        ${HEADERS}
        ${SOURCES}
)
target_link_libraries(tex SDL3::Headers SDL3::SDL3)
add_subdirectory(tests)

