#include "iterator.h"

bool
Iterator::is_valid() const
{
	return valid;
}

Record
Iterator::get_value() const
{
	return value;
}

void
Iterator::get_next()
{
	if (!do_get_next(value))
		valid = false;
}
