#ifndef DRDB_AGGREGATE_ITERATOR_H
#define DRDB_AGGREGATE_ITERATOR_H

#include <memory>
#include <queue>
#include <utility>

#include "../record.h"
#include "iterator.h"

class AggregateIterator : public Iterator
{
private:
	using HeapEntry = std::pair<Record, size_t>;

	std::vector<std::unique_ptr<Iterator>> iters;
	std::priority_queue<HeapEntry, std::vector<HeapEntry>, std::greater<>> iter_heap;

	bool
	do_get_next(Record& ret_value) override;

public:
	explicit AggregateIterator(std::vector<std::unique_ptr<Iterator>> iters);
};

#endif	// DRDB_AGGREGATE_ITERATOR_H
