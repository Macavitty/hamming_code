cmake_minimum_required(VERSION 3.15)
project(hamming_code)

set(CMAKE_CXX_STANDARD 14)

add_executable(hamming_code main.cpp coder.h coder.cpp decoder.cpp decoder.h)