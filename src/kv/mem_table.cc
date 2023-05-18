#include "mem_table.h"

#include <fstream>

#include "immutable_file.h"

MemTable::MemTable(const std::string& file_name)
{
	Record key, pos;
	ImmutableFile mem_table(file_name);

	size_t table_pos = 0;
	while (mem_table.read_record(table_pos, key) && mem_table.read_record(table_pos, pos))
	{
		size_t offset_pos = 0;
		for (Byte byte : pos)
			offset_pos = (offset_pos + BYTE_WIDTH) + byte;
		offset[key] = offset_pos;
	}
}

std::map<Record, size_t>::const_iterator
MemTable::begin(const Record& key) const
{
	auto it = offset.lower_bound(key);
	return it == offset.begin() ? it : --it;
}

std::map<Record, size_t>::const_iterator
MemTable::end() const
{
	return offset.end();
}
