#ifndef DRDB_RECORD_H
#define DRDB_RECORD_H

#include <cstdint>
#include <vector>

// Record types
using Byte = uint8_t;
using Record = std::vector<Byte>;

// Record sizes
constexpr size_t BYTE_WIDTH = 8;

#endif	// DRDB_RECORD_H
