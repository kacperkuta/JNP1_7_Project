cmake_minimum_required(VERSION 3.13)
project(JNP1_7_Project)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -O3 -std=c++03 -fconcepts")


add_executable(JNP main.cpp images.h images.cpp coordinate.h coordinate.cpp color.h color.cpp bmp.h bmp.cpp functional.h functional.cpp test.h test.cpp)