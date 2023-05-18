#include "immutable_file.h"

#include "encoder.h"

ImmutableFile::ImmutableFile(const std::string& file_name) : file{file_name} {}

void
ImmutableFile::read_buffer(const size_t offset)
{
	size_t actual_size = 0;
	file.seekg(offset);
	buffer.reserve(BUFFER_SIZE);

	char byte;
	for (actual_size = 0; actual_size < BUFFER_SIZE; ++actual_size)
	{
		if (!file)
			continue;
		file.read(&byte, 1);
		buffer[actual_size] = byte;
	}

	buffer.resize(actual_size);
	start = offset;
	end = offset + actual_size;
}

bool
ImmutableFile::read_record(size_t& offset, Record& out_record)
{
	if (offset < start || offset + Encoder::METADATA_SIZE >= end)
		read_buffer(offset);

	size_t record_size;
	if (!Encoder::decode_size(buffer, record_size, offset - start))
		return false;

	if (offset + Encoder::METADATA_SIZE + record_size >= end)
		read_buffer(offset);

	if (!Encoder::decode_bytes(buffer, out_record, offset - start))
		return false;

	offset += Encoder::METADATA_SIZE + record_size;
	return true;
}
