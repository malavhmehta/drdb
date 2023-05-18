#ifndef DRDB_RECORD_READER_H
#define DRDB_RECORD_READER_H

#include <fstream>

#include "../record.h"

class RecordReader
{
public:
	static bool
	read_record(const Record& buffer, size_t& pos, Record& out_record);

	static bool
	read_buffer(std::ifstream& file, size_t buffer_size, Record& out_buffer);

	static bool
	read_record(std::ifstream& file, Record& out_record);
};

#endif	// DRDB_RECORD_READER_H
