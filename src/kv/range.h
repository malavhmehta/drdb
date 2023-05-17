#ifndef DRDB_RANGE_H
#define DRDB_RANGE_H

#include <cstdint>
#include <vector>

struct Bound
{
	enum class Type
	{
		Open,
		Closed,
		Prefix
	};

	Type type;
	std::vector<uint8_t> key;
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

	[[nodiscard]] std::vector<uint8_t>
	get_start() const;

	[[nodiscard]] std::vector<uint8_t>
	get_end() const;

	Ordering
	compare(const std::vector<uint8_t>& key);
};

#endif	// DRDB_RANGE_H
