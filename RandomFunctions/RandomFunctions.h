#pragma once
#include <string>
#define HINIBBLE(x) (((((unsigned char)(x)) >> 4) | 0xF0) ^ 0xF0)
#define LONIBBLE(x) ((((unsigned char)(x)) | 0xF0) ^ 0xF0)
#define loop(start, end) for(int i = (start); i < (end); i++)

class RandomFunctions
{
	public:
		static const wchar_t* LPCSTRtoLPCWSTR(const char* str);
		static const char* LPCWSTRtoLPCSTR(const wchar_t* wstr);
		static char BoolsToByte(bool arr[8]);
		static bool* ByteToBools(unsigned char byte);
		static void hexDumpA(void* ptr, size_t size);
		static void hexDumpW(void* ptr, size_t size);
		static std::string AsciiDump(const char* bytes, size_t size);
		static std::string hexDump(const char* bytes, size_t size);
		static int nwprintf(const char* _Format, ...);
		static int wnwprintf(const wchar_t* _Format, ...);
};

