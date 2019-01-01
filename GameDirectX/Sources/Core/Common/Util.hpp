#pragma once

#include <sstream>



namespace core
{
template <typename ... Args> struct match : Args... { using Args::operator()...; };
template <typename ... Args> match(Args...) -> match<Args...>;

template <typename ... Args>
std::wstring toWString(Args &&... args)
{
	std::wstringstream stream;
	stream << std::boolalpha;
	(stream << ... << std::forward<Args>(args));

	return std::move(stream.str());
}

template <typename ... Args>
std::string toString(Args &&... args)
{
	std::stringstream stream;
	stream << std::boolalpha;
	(stream << ... << std::forward<Args>(args));

	return std::move(stream.str());
}
}
