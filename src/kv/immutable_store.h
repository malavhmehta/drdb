#ifndef DRDB_IMMUTABLE_STORE_H
#define DRDB_IMMUTABLE_STORE_H

#include "../types.h"

class Iterator;
class Range;

class ImmutableStore
{
private:
	virtual bool
	do_get(const Record& key, Record& out_value) = 0;

	virtual std::unique_ptr<Iterator>
	do_scan(const Range& range) = 0;

public:
	bool
	get(const Record& key, Record& out_value);

	std::unique_ptr<Iterator>
	scan(const Range& range);
};

#endif	// DRDB_IMMUTABLE_STORE_H
