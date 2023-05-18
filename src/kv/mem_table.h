#ifndef DRDB_MEM_TABLE_H
#define DRDB_MEM_TABLE_H

#include <map>
#include <string>

#include "../record.h"

class MemTable
{
	std::map<Record, size_t> offset;

public:
	explicit MemTable(const std::string& file_name);

	[[nodiscard]] std::map<Record, size_t>::const_iterator
	begin(const Record& key) const;

	[[nodiscard]] std::map<Record, size_t>::const_iterator
	end() const;
};

#endif	// DRDB_MEM_TABLE_H
