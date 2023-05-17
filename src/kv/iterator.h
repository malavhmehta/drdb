#ifndef DRDB_ITERATOR_H
#define DRDB_ITERATOR_H

#include "../types.h"

class Iterator
{
private:
	bool is_valid;
	Record value;

	virtual bool
	do_get_value(Record& ret_value) = 0;

public:
	virtual ~Iterator() = default;

	explicit operator bool() const;

	Record
	operator*() const;

	void
	operator++();
};

#endif	// DRDB_ITERATOR_H
