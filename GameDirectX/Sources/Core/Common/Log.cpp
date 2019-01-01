#include "Log.hpp"



namespace core
{
void Log::begin(LPCWSTR fileName)
{
#ifdef _DEBUG
	AllocConsole();
	bindStdIO();

	file.open(fileName);
	if (!file)
		ERR("File open failed.\n");

	debug(L"Log begun");
#endif
}

void Log::end()
{
#ifdef _DEBUG
	debug(L"Log ended");

	//FreeConsole(); // FIXME: free the console
	file.close();
#endif
}

std::string Log::errorAsString(DWORD error)
{
	if (!error)
		return std::string();

	LPSTR messageBuffer{ nullptr };
	TRY(FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, error, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), reinterpret_cast<LPSTR>(&messageBuffer), 0, nullptr));

	std::string message{ messageBuffer };

	LocalFree(messageBuffer);

	return message;
}

void Log::bindStdIO()
{
	bindStd(stdout, STD_OUTPUT_HANDLE, "w");
	bindStd(stderr, STD_ERROR_HANDLE, "w");
	bindStd(stdin, STD_INPUT_HANDLE, "r");

	std::wcout.clear();
	std::cout.clear();
	std::wcerr.clear();
	std::cerr.clear();
	std::wcin.clear();
	std::cin.clear();

	debug(L"Std IO binded");
}

void Log::bindStd(FILE * stdfile, DWORD handle, LPCSTR mode)
{
	FILE * dummyFile{ nullptr };
	freopen_s(&dummyFile, "nul", mode, stdfile);

	if (HANDLE stdHandle{ GetStdHandle(handle) }; stdHandle != INVALID_HANDLE_VALUE)
		if (int fileDescriptor{ _open_osfhandle(reinterpret_cast<intptr_t>(stdHandle), _O_TEXT) }; fileDescriptor != -1)
			if (FILE * file{ _fdopen(fileDescriptor, mode) }; file && !_dup2(_fileno(file), _fileno(stdfile)))
				setvbuf(stdfile, nullptr, _IONBF, 0);
}

std::wofstream Log::file;
}
