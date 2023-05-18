#ifndef DRDB_IMMUTABLE_FILE_H
#define DRDB_IMMUTABLE_FILE_H

#include <fstream>

#include "../record.h"

class ImmutableFile
{
private:
	// buffer is 128 kb in size
	static constexpr size_t BUFFER_SIZE = 1 << 17;

	Record buffer;
	size_t start = -1;
	size_t end = -1;
	std::ifstream file;

	void
	read_buffer(size_t offset);

public:
	explicit ImmutableFile(const std::string& file_name);

	bool
	read_record(size_t& offset, Record& out_record);
};

#endif	// DRDB_IMMUTABLE_FILE_H
