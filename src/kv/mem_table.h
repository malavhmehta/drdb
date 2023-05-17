#ifndef DRDB_MEM_TABLE_H
#define DRDB_MEM_TABLE_H

#include <map>
#include <string>

#include "../types.h"

class MemTable
{
	std::map<Record, size_t> offset;

public:
	static bool
	from_ss_table(const std::string& ss_table_file_name, const std::string& out_file_name);

	explicit MemTable(const std::string& file_name);

	[[nodiscard]] std::map<Record, size_t>::const_iterator
	begin(const Record& key) const;

	[[nodiscard]] std::map<Record, size_t>::const_iterator
	end() const;
};

#endif	// DRDB_MEM_TABLE_H
