#include "aggregate_iterator.h"

AggregateIterator::AggregateIterator(std::vector<std::unique_ptr<Iterator>> _iters)
    : iters{std::move(_iters)}
{
	for (size_t i = 0; i < iters.size(); ++i)
	{
		if (iters[i])
			iter_heap.emplace(iters[i]->get_value(), i);
	}

	get_next();
}

bool
AggregateIterator::do_get_next(Record& out_value)
{
	if (iter_heap.empty())
		return false;

	auto [value, index] = iter_heap.top();
	out_value = std::move(value);
	Iterator* iter = iters[index].get();
	iter->get_next();
	if (iter->is_valid())
		iter_heap.emplace(iter->get_value(), index);

	return true;
}
