#include "range.h"

Record
Range::get_start() const
{
	return start.key;
}

Record
Range::get_end() const
{
	return end.key;
}

Range::Ordering
Range::compare(const Record& key)
{
	if (start.type == Bound::Type::Prefix)
	{
		if (start.key < key)
			return Ordering::Before;

		if (start.key.size() > key.size())
			return Ordering::After;

		for (size_t i = 0; i < start.key.size(); ++i)
		{
			if (start.key[i] != key[i])
				return Ordering::After;
		}

		return Ordering::Middle;
	}

	if ((start.type == Bound::Type::Open && start.key < key) ||
	    (start.type == Bound::Type::Closed && start.key <= key))
		return Ordering::Before;

	if ((end.type == Bound::Type::Open && end.key > key) ||
	    (end.type == Bound::Type::Closed && end.key >= key))
		return Ordering::After;

	return Ordering::Middle;
}
