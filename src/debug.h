#ifndef DRDB_DEBUG_H
#define DRDB_DEBUG_H

#include <memory>
#include <string>

#if !defined(DRDB_DEBUG_LEVEL)
#define DRDB_DEBUG_LEVEL 0
#endif

template <typename... Args>
std::string
format(const std::string &fmt, Args... args)
{
	int res_size = std::snprintf(nullptr, 0, fmt.c_str(), args...) + 1;
	if (res_size <= 0)
		throw std::runtime_error("error formatting");

	auto buf_size = static_cast<size_t>(res_size);
	std::unique_ptr<char[]> buf(new char[buf_size]);
	std::snprintf(buf.get(), buf_size, fmt.c_str(), args...);
	return {buf.get(), buf.get() + buf_size - 1};
}

#define DBG(level) if (DRDB_DEBUG_LEVEL >= level)
#define ERR(...) std::cerr << format(__VA_ARGS__) << std::endl
#define WARN(level, ...) DBG(level) ERR(__VA_ARGS__)

#endif	// DRDB_DEBUG_H
