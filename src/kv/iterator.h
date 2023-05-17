#ifndef DRDB_ITERATOR_H
#define DRDB_ITERATOR_H

#include <cstdint>
#include <vector>

class Iterator
{
private:
	bool is_valid;
	std::vector<uint8_t> value;

	virtual bool
	do_get_value(std::vector<uint8_t>& ret_value) = 0;

public:
	virtual ~Iterator() = default;

	explicit operator bool() const;

	std::vector<uint8_t>
	operator*() const;

	void
	operator++();
};

#endif	// DRDB_ITERATOR_H
