#pragma once
#ifndef MEMORY_H
#define MEMORY_H
#include <vector>
#include <Windows.h>
#include <iostream>

#if __has_include("Console/Console.h")
#include "Console/Console.h"
#elif __has_include("Console.h")
#include "Console.h"
#endif

// Uncomment macro under this line to print debug information (if enabled) using wide characters
//#define MEMORY_WIDE_OUTPUT
#ifndef MEMORY_WIDE_OUTPUT
#define __tcout std::cout
#define __tstr(x) x
#define __tprintf printf
#define __tvprinf vprintf
typedef const char* __TCHAR;
const unsigned int msgTypes[4] = { 0x5D2B5B, 0x5D3D5B, 0x5D1D5B, 0x5D215B };
#else
#define __tcout std::wcout
#define __tstr(x) L##x
#define __tprintf wprintf
#define __tvprinf vwprintf
typedef const wchar_t* __TCHAR;
const unsigned long long msgTypes[4] = { 0x5D002B005B, 0x5D003D005B, 0x5D2194005B, 0x5D0021005B };
#endif

#define MEMORY_SHOW_DEBUG true
#define MSG_OBJECT_NEW 0
#define MSG_OBJECT_CHANGE 1
#define MSG_OBJECT_MOVE 2
#define MSG_OBJECT_FAIL 3

class Memory
{
	public:
		template <class T> class Object {
			public:
				// Creates pointer to any object in memory
				Object(uintptr_t pointerAddress, std::vector<intptr_t> pointerOffsets, bool printDebug = false)
				: defaultPointerAddress(pointerAddress), pointerOffsets(pointerOffsets), printDebug(printDebug) {
					this->Refresh();
				}

				// Refreshes address of object pointer (returns 0 if address success)
				bool Refresh() {
					uintptr_t tempAddress = baseAddress + defaultPointerAddress;

					for (size_t i = 0; i < pointerOffsets.size(); i++) {
						if (!CheckReadableAddress(tempAddress)) {
							tempAddress = (*(uintptr_t*)tempAddress) + pointerOffsets[i];
						}
						else {
							PrintDebug(MSG_OBJECT_FAIL, __tstr("Memory object initialization failed: Address is not valid"));
							return true;
						}
					}
					if (!CheckWritableAddress(tempAddress)) {
						PrintDebug(MSG_OBJECT_NEW, __tstr("New memory object has been attached to 0x%p"), (T*)tempAddress);
						address = (T*)tempAddress;
						return false;
					}
					PrintDebug(MSG_OBJECT_FAIL, __tstr("Memory object initialization failed: Address is not writable"));
					return true;
				}

				// Changes value of object pointer (returns 0 if address success)
				bool ChangeValue(T value) {
					if (!CheckWritableAddress((uintptr_t)address)) {
						PrintDebug(MSG_OBJECT_CHANGE, __tstr("Value of memory object at 0x%p has been changed"), address);
						*address = value;
						return false;
					}
					PrintDebug(MSG_OBJECT_FAIL, __tstr("Memory object value change failed: Address is not writable!"));
					return true;
				}

				// Moves object pointer (refresh will return object pointer to default address) (returns 0 if address success)
				bool Move(intptr_t offset) {
					uintptr_t tempAddress = (uintptr_t)address;
					tempAddress += offset;
					if (!CheckWritableAddress(tempAddress)) {
						PrintDebug(MSG_OBJECT_MOVE, __tstr("Memory object has been moved from 0x%p to 0x%p"), (T*)(tempAddress - offset), (T*)tempAddress);
						address = (T*)tempAddress;
						return false;
					}
					PrintDebug(MSG_OBJECT_FAIL, __tstr("Memory object move failed: Address is not writable!"));
					return true;
				}

				// Returns value of object pointer
				T GetValue() {
					if (!CheckReadableAddress((uintptr_t)address)) {
						return *address;
					}
					PrintDebug(MSG_OBJECT_FAIL, __tstr("Getting value from memory object failed: Address is not readable!"));
					return NULL;
				}

				// Returns address of object pointer
				uintptr_t GetAddress() {
					return (uintptr_t)address;
				}
			private:
				T* address;
				const bool printDebug;
				const uintptr_t defaultPointerAddress;
				const std::vector<intptr_t> pointerOffsets;
				void PrintDebug(int msgType, __TCHAR format, ...) {
					if (printDebug) {
						const unsigned int msgColors[4] = {0xA, 0xE, 0x9, 0xC};
						va_list argptr;
						va_start(argptr, format);
						#ifdef CONSOLE_H
						Console::ChangeColor(msgColors[msgType]);
						#endif
						__tprintf(__tstr("%s "), (__TCHAR)&msgTypes[msgType]);
						#ifdef CONSOLE_H
						Console::ChangeColor(WHITE);
						#endif
						__tvprinf(format, argptr);
						__tprintf(__tstr("\n"));
						va_end(argptr);
					}
				}
		};
		
		// Returns base address of application
		static uintptr_t GetBaseAddress();

		// Hex write to address that may have read only access
		static void HexWrite(uintptr_t pointerWithoutBase, const char* bytes, size_t size = 0);

		// Prints hex dump of address
		static void hexDump(void* ptr, size_t size);

		// Checks if given address is readable (returns 0 if address is readable)
		static bool CheckReadableAddress(uintptr_t address);

		// Checks if given address is writable (returns 0 if address is writable)
		static bool CheckWritableAddress(uintptr_t address);

	private:
		static uintptr_t CalculateBaseAddress();
		static uintptr_t baseAddress;
};
#endif