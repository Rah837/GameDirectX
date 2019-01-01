#pragma once

#include <iostream>
#include <fstream>

#include <Windows.h>
#include <fcntl.h>
#include <io.h>

#include "Util.hpp"


#define ERR(msg) { core::Log::error(__LINE__, __FILE__, (msg)); }

#define TRY(exp) { SetLastError(0); exp; DWORD err{ GetLastError() }; if (err) {\
std::string str{ core::Log::errorAsString(err) }; ERR(str); throw std::runtime_error{ str };} }
#define TRY_EXCEP(exp) { try { exp; }catch(std::exception& e){ ERR(e.what()); throw;} }



namespace core
{
class Log final
{
public:
	Log() = delete;

	template <typename ... Args>
	static void debug(Args &&... args)
	{
#ifdef _DEBUG
		SYSTEMTIME time{ 0 };
		GetLocalTime(&time);

		std::wstring string{ toWString(
			L"[", time.wMinute, L":", time.wSecond, L".", time.wMilliseconds,
			L"][Debug] ", args..., WNEW_LINE) };

		std::wcout << string;
		file << string;
#endif
	}

	template <typename T>
	static std::string error(UINT line, LPCSTR fileName, T && error)
	{
		SYSTEMTIME time{ 0 };
		GetLocalTime(&time);

		std::string string{ toString(
			"[", time.wMinute, ":", time.wSecond, ".", time.wMilliseconds,
			"][Error] at line: ", line, " - ", error,
			"at file: ", fileName, NEW_LINE) };
#ifdef _DEBUG
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x000C);
		std::cerr << string;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007);

		file << string.c_str();
#endif

		return std::move(string);
	}

	static void begin(LPCWSTR fileName);
	static void end();
	static std::string errorAsString(DWORD error = S_OK);

	static void bindStdIO();

private:
	static void bindStd(FILE * stdfile, DWORD handle, LPCSTR mode);

	static std::wofstream file;
	static constexpr LPCSTR NEW_LINE = "\x0D\x0A";
	static constexpr LPCWSTR WNEW_LINE = L"\x0D\x0A";
};
}
