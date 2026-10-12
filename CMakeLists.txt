cmake_minimum_required(VERSION 3.16)

project(AA_Lab1 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wpedantic)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB SOURCES "src/*.c")

add_executable(lab1 ${SOURCES})