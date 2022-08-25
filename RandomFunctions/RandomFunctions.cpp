#include "RandomFunctions.h"
#include <string.h>
#include <iostream>

const wchar_t* RandomFunctions::LPCSTRtoLPCWSTR(const char* str) {
	size_t wchSize = strlen(str) * sizeof(wchar_t) + sizeof(wchar_t);
	size_t endPos = sizeof(wchar_t);
	wchar_t* wstr = new wchar_t[wchSize];
	char* byteWSTR = (char*)wstr;
	for (size_t i0 = 0; i0 < wchSize - sizeof(wchar_t);) {
		#pragma warning(disable:6386) // Bogus warning
		byteWSTR[i0] = str[i0++ / sizeof(wchar_t)];
		#pragma warning(default:6386)
		for (size_t i1 = i0; i1 < endPos; i1++) {
			byteWSTR[i1] = '\x0';
			i0++;
		}
		endPos += sizeof(wchar_t);
	}
	for (size_t i = wchSize - sizeof(wchar_t); i < wchSize; i++) {
		byteWSTR[i] = '\x0';
	}
	return (const wchar_t*)wstr;
}

const char* RandomFunctions::LPCWSTRtoLPCSTR(const wchar_t* wstr) {
	#pragma warning(disable:6305) // Bogus warning
	size_t chSize = wcslen(wstr) + sizeof(char);
	#pragma warning(default:6305)
	size_t zeroByteCheck = 0;
	char* str = new char[chSize];
	char* byteWSTR = (char*)wstr;
	char currentChar;
	for (size_t i0 = 0; i0 < chSize - sizeof(char); i0++) {
		for (size_t i1 = i0 * sizeof(wchar_t) + 1; i1 < i0 * sizeof(wchar_t) + sizeof(wchar_t); i1++) {
			if (byteWSTR[i1] == '\x0') {
				zeroByteCheck++;
			}
		}
		currentChar = byteWSTR[i0 * sizeof(wchar_t)];
		if (zeroByteCheck == sizeof(wchar_t) - 1 && (currentChar >= 0x20 && currentChar < 0x7F)) {
			str[i0] = currentChar;
		}
		else {
			str[i0] = '?';
		}
		zeroByteCheck = 0;
	}
	str[chSize - sizeof(char)] = '\x0';
	return (const char*)str;
}

char RandomFunctions::BoolsToByte(bool arr[8]) {
	unsigned char byte = arr[0];
	for (int i = 0; i < 8; i++) {
		byte <<= 1;
		byte |= arr[i];
	}
	return byte;
}

bool* RandomFunctions::ByteToBools(unsigned char byte) {
	unsigned char shift = byte;
	bool* arr = new bool[8];
	for (int i = 7; i >= 0; i--) {
		arr[i] = shift % 2;
		shift >>= 1;
	}
	return arr;
}

void RandomFunctions::hexDumpA(void* ptr, size_t size) {
	unsigned char* chptr = (unsigned char*)ptr;
	std::cout << std::hex << std::uppercase;
	for (size_t i = 0; i < size; i++) {
		if (*chptr < 0x10) {
			std::cout << "0";
		}
		std::cout << (int)*(chptr++) << " ";
	}
	std::cout << std::dec << std::endl;
}

void RandomFunctions::hexDumpW(void* ptr, size_t size) {
	unsigned char* chptr = (unsigned char*)ptr;
	std::wcout << std::hex << std::uppercase;
	for (size_t i = 0; i < size; i++) {
		if (*chptr < 0x10) {
			std::wcout << L"0";
		}
		std::wcout << (int)*(chptr++) << L" ";
	}
	std::wcout << std::dec << std::endl;
}