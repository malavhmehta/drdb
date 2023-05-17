#ifndef DRDB_ENCODER_H
#define DRDB_ENCODER_H

#include "../types.h"

class Encoder
{
public:
	static constexpr size_t METADATA_SIZE = 2;
	static constexpr size_t MAX_RECORD_SIZE = (1 << (METADATA_SIZE * 8)) - 2;
	static const Record TOMBSTONE_VALUE;

public:
	static Record
	encode_bytes(const Record& input, size_t from = 0, size_t to = -1);

	static size_t
	decode_size(const Record& metadata, size_t from = 0);

	static bool
	is_tombstone(const Record& metadata, size_t from = 0);

	static Record
	decode_bytes(const Record& encoded, size_t from = 0, size_t to = -1);
};

#endif	// DRDB_ENCODER_H
