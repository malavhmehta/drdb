#ifndef DRDB_AGGREGATE_ITERATOR_H
#define DRDB_AGGREGATE_ITERATOR_H

#include <cstdint>
#include <queue>
#include <utility>
#include <vector>

#include "iterator.h"

class AggregateIterator : public Iterator
{
private:
	using HeapEntry = std::pair<std::vector<uint8_t>, size_t>;

	std::vector<Iterator> iters;
	std::priority_queue<HeapEntry, std::vector<HeapEntry>, std::greater<>> iter_heap;

	bool
	do_get_value(std::vector<uint8_t>& ret_value) override;

public:
	explicit AggregateIterator(std::vector<Iterator> iters);
};

#endif	// DRDB_AGGREGATE_ITERATOR_H
