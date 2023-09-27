#include "RandomFunctions.h"
#include <iostream>
#include <Windows.h>

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

std::string RandomFunctions::AsciiDump(const char* bytes, size_t size) {
	std::string ascii;
	for (size_t i = 0; i < size; i++) {
		if ((bytes[i] >= 32) && (bytes[i] <= 126)) {
			ascii += bytes[i];
		}
		else {
			ascii += '.';
		}
	}
	return ascii;
}

std::string RandomFunctions::hexDump(const char* bytes, size_t size) {
	#define HINIBBLE(x) (((((unsigned char)x) >> 4) | 0xF0) ^ 0xF0)
	#define LONIBBLE(x) ((((unsigned char)x) | 0xF0) ^ 0xF0)
	const char* arr = "0123456789ABCDEF";
	std::string hex;
	for (size_t i = 0; i < size; i++) {
		hex += arr[HINIBBLE(bytes[i])];
		hex += arr[LONIBBLE(bytes[i])];
		hex += ' ';
	}
	hex.pop_back();
	return hex;
}

int RandomFunctions::nwprintf(const char* _Format, ...) {
	// String formatting
	va_list args;
	va_start(args, _Format);
	size_t length = vsnprintf(NULL, 0, _Format, args);
	char* buffer = (char*)malloc(length * sizeof(char) + sizeof(char));
	if (buffer == NULL) {
		return -1;
	}
	int result = vsprintf_s(buffer, length + 1, _Format, args);
	va_end(args);

	// Getting console cursor coordinates
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD coord;
	if (GetConsoleScreenBufferInfo(hConsoleOutput, &csbi)) {
		coord = csbi.dwCursorPosition;
	}
	else {
		return -1;
	}

	// Printing to the console
	DWORD charactersWritten;
	WriteConsoleOutputCharacterA(
		hConsoleOutput,
		buffer,
		(DWORD)strlen(buffer),
		coord,
		&charactersWritten
	);

	// Move and calculate cursor position
	int consoleW = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	if ((coord.X + (SHORT)charactersWritten) >= consoleW) {
		coord.X = ((SHORT)charactersWritten - (consoleW - coord.X));
		coord.Y += (coord.X / consoleW) + 1;
		coord.X %= consoleW;
	}
	else {
		coord.X += (SHORT)charactersWritten;
	}
	SetConsoleCursorPosition(hConsoleOutput, coord);

	free(buffer);
	return charactersWritten;
}
int RandomFunctions::wnwprintf(const wchar_t* _Format, ...) {
	// String formatting
	va_list args;
	va_start(args, _Format);
	size_t length = vswprintf(NULL, 0, _Format, args);
	wchar_t* buffer = (wchar_t*)malloc(length * sizeof(wchar_t) + sizeof(wchar_t));
	if (buffer == NULL) {
		return -1;
	}
	int result = vswprintf_s(buffer, length + 1, _Format, args);
	va_end(args);

	// Getting console cursor coordinates
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD coord;
	if (GetConsoleScreenBufferInfo(hConsoleOutput, &csbi)) {
		coord = csbi.dwCursorPosition;
	}
	else {
		return -1;
	}

	// Printing to the console
	DWORD charactersWritten;
	WriteConsoleOutputCharacterW(
		hConsoleOutput,
		buffer,
		(DWORD)wcslen(buffer),
		coord,
		&charactersWritten
	);

	// Move and calculate cursor position
	int consoleW = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	if ((coord.X + (SHORT)charactersWritten) >= consoleW) {
		coord.X = ((SHORT)charactersWritten - (consoleW - coord.X));
		coord.Y += (coord.X / consoleW) + 1;
		coord.X %= consoleW;
	}
	else {
		coord.X += (SHORT)charactersWritten;
	}
	SetConsoleCursorPosition(hConsoleOutput, coord);

	free(buffer);
	return charactersWritten;
}