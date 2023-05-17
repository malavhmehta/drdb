#include "iterator.h"

Iterator::operator bool() const { return is_valid; }

Record
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