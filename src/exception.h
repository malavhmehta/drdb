#ifndef DRDB_EXCEPTION_H
#define DRDB_EXCEPTION_H

#include <exception>
#include <string>

#include "debug.h"

class Exception : public std::exception
{
    public:
	template <typename... Args>
	explicit Exception(const std::string& fmt, Args... args) : err(format(fmt, args...))
	{
	}

	[[nodiscard]] const char*
	what() const noexcept override
	{
		return err.c_str();
	}

    private:
	const std::string err;
};

#endif	// DRDB_EXCEPTION_H
