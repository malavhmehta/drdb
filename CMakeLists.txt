cmake_minimum_required(VERSION 3.25)
project(drdb)

set(CMAKE_CXX_STANDARD 20)

add_executable(drdb main.cc src/debug.h src/kv/encoder.cc src/kv/encoder.h src/exception.h src/kv/range.cc src/kv/range.h)
