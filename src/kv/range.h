#ifndef DRDB_RANGE_H
#define DRDB_RANGE_H

#include "../types.h"

struct Bound
{
	enum class Type
	{
		Open,
		Closed,
		Prefix
	};

	Type type;
	Record key;
};

class Range
{
	enum class Ordering
	{
		Before,
		Middle,
		After
	};

	Bound start;
	Bound end;

public:
	Range(Bound start, Bound end) : start{std::move(start)}, end{std::move(end)} {}

	[[nodiscard]] Record
	get_start() const;

	[[nodiscard]] Record
	get_end() const;

	Ordering
	compare(const Record& key);
};

#endif	// DRDB_RANGE_H
