#include "aggregate_iterator.h"

AggregateIterator::AggregateIterator(std::vector<Iterator> _iters) : iters{std::move(_iters)}
{
	for (size_t i = 0; i < iters.size(); ++i)
	{
		if (iters[i])
			iter_heap.emplace(*iters[i], i);
	}

	++(*this);
}

bool
AggregateIterator::do_get_value(std::vector<uint8_t>& ret_value)
{
	if (iter_heap.empty())
		return false;

	auto [value, index] = iter_heap.top();
	ret_value = std::move(value);
	Iterator& iter = iters[index];
	++iter;
	if (iter)
		iter_heap.emplace(*iter, index);

	return true;
}