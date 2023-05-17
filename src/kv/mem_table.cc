#include "mem_table.h"

bool
MemTable::from_ss_table(const std::string& ss_table_file_name, const std::string& out_file_name)
{
	return false;
}

MemTable::MemTable(const std::string& file_name) {}

std::map<Record, size_t>::const_iterator
MemTable::begin(const Record& key) const
{
	return {};
}

std::map<Record, size_t>::const_iterator
MemTable::end() const
{
	return offset.end();
}
