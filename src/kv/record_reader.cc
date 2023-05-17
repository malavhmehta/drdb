#include "record_reader.h"

#include "encoder.h"

bool
RecordReader::read_record(const Record& buffer, size_t& pos, Record& out_record)
{
	size_t record_size;
	if (!Encoder::decode_size(buffer, record_size, pos))
		return false;

	if (!Encoder::decode_bytes(buffer, out_record, pos))
		return false;

	pos += Encoder::METADATA_SIZE + record_size;
	return true;
}

bool
RecordReader::read_buffer(std::ifstream& file, size_t buffer_size, Record& out_buffer)
{
	out_buffer.resize(buffer_size);
	for (size_t i = 0; i < buffer_size; ++i)
	{
		if (!file)
			return false;
		file >> out_buffer[i];
	}
	return true;
}

bool
RecordReader::read_record(std::ifstream& file, Record& out_record)
{
	out_record.resize(Encoder::METADATA_SIZE);
	for (size_t i = 0; i < Encoder::METADATA_SIZE; ++i)
	{
		if (!file)
			return false;
		file >> out_record[i];
	}

	size_t record_size;
	if (!Encoder::decode_size(out_record, record_size))
		return false;

	out_record.resize(record_size);
	for (size_t i = 0; i < record_size; ++i)
	{
		if (!file)
			return false;
		file >> out_record[i];
	}

	return true;
}
