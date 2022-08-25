#pragma once
class RandomFunctions
{
	public:
		const wchar_t* LPCSTRtoLPCWSTR(const char* str);
		const char* LPCWSTRtoLPCSTR(const wchar_t* wstr);
		char BoolsToByte(bool arr[8]);
		bool* ByteToBools(unsigned char byte);
		void hexDumpA(void* ptr, size_t size);
		void hexDumpW(void* ptr, size_t size);
};

