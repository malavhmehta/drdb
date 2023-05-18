#ifndef DRDB_IMMUTABLE_STORE_H
#define DRDB_IMMUTABLE_STORE_H

#include <memory>

#include "../record.h"

class Iterator;
class Range;

class ImmutableStore
{
private:
	virtual bool
	do_get(const Record& key, Record& out_value) const = 0;

	[[nodiscard]] virtual std::unique_ptr<Iterator>
	do_scan(const Range& range) const = 0;

public:
	bool
	get(const Record& key, Record& out_value) const;

	[[nodiscard]] std::unique_ptr<Iterator>
	scan(const Range& range) const;
};

#endif	// DRDB_IMMUTABLE_STORE_H
