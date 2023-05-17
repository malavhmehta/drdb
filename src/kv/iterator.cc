#include "iterator.h"

Iterator::operator bool() const { return is_valid; }

std::vector<uint8_t>
Iterator::operator*() const
{
	return value;
}

void
Iterator::operator++()
{
	if (!do_get_value(value))
		is_valid = false;
}