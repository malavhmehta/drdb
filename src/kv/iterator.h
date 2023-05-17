#ifndef DRDB_ITERATOR_H
#define DRDB_ITERATOR_H

#include "../types.h"

class Iterator
{
private:
	bool valid;
	Record value;

	virtual bool
	do_get_next(Record& out_value) = 0;

public:
	virtual ~Iterator() = default;

	[[nodiscard]] bool
	is_valid() const;

	[[nodiscard]] Record
	get_value() const;

	void
	get_next();
};

#endif	// DRDB_ITERATOR_H
