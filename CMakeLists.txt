cmake_minimum_required(VERSION 3.25)
project(drdb)

set(CMAKE_CXX_STANDARD 20)

add_executable(drdb main.cc src/debug.h src/kv/encoder.cc src/kv/encoder.h src/exception.h src/kv/range.cc src/kv/range.h src/kv/iterator.cc src/kv/iterator.h src/kv/aggregate_iterator.cc src/kv/aggregate_iterator.h src/types.h src/kv/immutable_store.cc src/kv/immutable_store.h src/kv/mem_table.cc src/kv/mem_table.h src/kv/file_reader.cc src/kv/file_reader.h)
