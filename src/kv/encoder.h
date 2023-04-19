#ifndef DRDB_ENCODER_H
#define DRDB_ENCODER_H

#include <vector>

namespace kv
{
class Encoder
{
    public:
	static constexpr size_t METADATA_SIZE = 2;
	static constexpr size_t MAX_RECORD_SIZE = (1 << (METADATA_SIZE * 8)) - 2;
	static const std::vector<uint8_t> TOMBSTONE_VALUE;

    public:
	static std::vector<uint8_t>
	encode_bytes(const std::vector<uint8_t>& input, size_t from = 0, size_t to = -1);

	static size_t
	decode_size(const std::vector<uint8_t>& metadata, size_t from = 0);

	static bool
	is_tombstone(const std::vector<uint8_t>& metadata, size_t from = 0);

	static std::vector<uint8_t>
	decode_bytes(const std::vector<uint8_t>& encoded, size_t from = 0, size_t to = -1);
};
}  // namespace kv

#endif	// DRDB_ENCODER_H
