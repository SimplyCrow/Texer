cmake_minimum_required(VERSION 3.31)
project(tex_tests C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 99)
set(LIB_PATH "../thirdparty")
set(MUNIT_PATH "${LIB_PATH}/munit")

set(MUNIT_SOURCE    "${MUNIT_PATH}/munit.c" "${MUNIT_PATH}/munit.h")
include_directories("${MUNIT_PATH}")

add_executable(tex_tests    ${MUNIT_SOURCE}
                            main.c)
target_link_libraries(tex_tests tex)
