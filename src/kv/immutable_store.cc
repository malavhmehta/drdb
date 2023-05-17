#include "immutable_store.h"

#include "iterator.h"

bool
ImmutableStore::get(const Record &key, Record &out_value)
{
	return do_get(key, out_value);
}

std::unique_ptr<Iterator>
ImmutableStore::scan(const Range &range)
{
	return do_scan(range);
}
