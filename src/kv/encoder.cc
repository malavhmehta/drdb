#include "encoder.h"

#include "../exception.h"

namespace
{
void
write_encoded_size(size_t size, Record& result)
{
	constexpr size_t bits = 8;
	constexpr size_t mask = 0b11111111;

	for (size_t i = 0; i < Encoder::METADATA_SIZE; ++i, size >> bits)
		result[i] = static_cast<Byte>(size & mask);
}
}  // namespace

const Record Encoder::TOMBSTONE_VALUE = {0x00, 0x00};

Record
Encoder::encode_bytes(const Record& input, size_t from, size_t to)
{
	if (to == -1)
		to = input.size();
	size_t input_size = to - from;

	if (!(from < to && to <= input.size()) || input_size > MAX_RECORD_SIZE)
		throw Exception("can't encode input bytes of size %zu from %zu to %zu",
				input.size(), from, to);

	Record encoded(input_size + METADATA_SIZE);
	write_encoded_size(input_size + 1, encoded);
	std::copy(input.begin() + from, input.begin() + to, encoded.begin() + METADATA_SIZE);
	return encoded;
}

size_t
Encoder::decode_size(const Record& metadata, size_t from)
{
	size_t to = metadata.size();
	size_t metadata_size = to - from;

	if (from >= to || metadata_size < METADATA_SIZE)
		throw Exception(
		    "can't decode record size from metadata of size %zu from %zu to %zu",
		    metadata.size(), from, to);

	constexpr size_t bits = 8;
	size_t size = 0;
	for (size_t i = from; i < from + METADATA_SIZE; ++i)
		size = (size << bits) + metadata[i];

	if (size > 0)
		--size;
	return size;
}

bool
Encoder::is_tombstone(const Record& metadata, size_t from)
{
	if (from >= metadata.size() || metadata.size() - from < METADATA_SIZE)
		return false;

	for (size_t i = from; i < from + METADATA_SIZE; ++i)
	{
		if (metadata[i] != TOMBSTONE_VALUE[i])
			return false;
	}

	return true;
}

Record
Encoder::decode_bytes(const Record& encoded, size_t from, size_t to)
{
	size_t record_size = decode_size(encoded, from);
	from += METADATA_SIZE;
	if (!(from < to && to < encoded.size()))
		throw Exception(
		    "can't decode bytes from encoding from %zu to %zu, expecting %zu bytes", from,
		    to, record_size);

	Record decoded(record_size);
	std::copy(encoded.begin() + from, encoded.begin() + to, decoded.begin());
	return decoded;
}
