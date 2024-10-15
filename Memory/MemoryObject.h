#pragma once
#if __has_include("Memory/Memory.h")
#include "Memory/Memory.h"
#else
#include "Memory.h"
#endif

#include <vector>
#include <cstdarg>

// Define MEMORY_WIDE_OUTPUT to print debug information using wide characters
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

namespace memory
{
	template <typename T>
	class Object
	{
		public:
		// Creates pointer to any object in memory
		Object(uintptr_t pointerAddress, std::vector<intptr_t> pointerOffsets, bool printDebug = false)
			: defaultPointerAddress(pointerAddress), pointerOffsets(pointerOffsets), printDebug(printDebug) {
			this->Refresh();
		}

		// Refreshes address of object pointer (returns 0 if address success)
		bool Refresh() {
			uintptr_t tempAddress = Offset<uintptr_t>(0) + defaultPointerAddress;

			for (size_t i = 0; i < pointerOffsets.size(); i++) {
				if (!CheckReadableAddress((void*)tempAddress)) {
					tempAddress = (*(uintptr_t*)tempAddress) + pointerOffsets[i];
				}
				else {
					PrintDebug(MSG_OBJECT_FAIL, __tstr("Memory object initialization failed: Address is not valid"));
					return true;
				}
			}
			if (CheckWritableAddress((void*)tempAddress)) {
				PrintDebug(MSG_OBJECT_NEW, __tstr("New memory object has been attached to 0x%p"), (T*)tempAddress);
				address = (T*)tempAddress;
				return false;
			}
			PrintDebug(MSG_OBJECT_FAIL, __tstr("Memory object initialization failed: Address is not writable"));
			return true;
		}

		// Changes value of object pointer (returns 0 if address success)
		bool ChangeValue(T value) {
			if (CheckWritableAddress((void*)address)) {
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
			if (CheckWritableAddress((void*)tempAddress)) {
				PrintDebug(MSG_OBJECT_MOVE, __tstr("Memory object has been moved from 0x%p to 0x%p"), (T*)(tempAddress - offset), (T*)tempAddress);
				address = (T*)tempAddress;
				return false;
			}
			PrintDebug(MSG_OBJECT_FAIL, __tstr("Memory object move failed: Address is not writable!"));
			return true;
		}

		// Returns value of object pointer
		T GetValue() {
			if (CheckReadableAddress((void*)address)) {
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
				const unsigned int msgColors[4] = { 0xA, 0xE, 0x9, 0xC };
				va_list argptr;
				va_start(argptr, format);
				#ifdef CONSOLE_H
				console::ChangeColor(msgColors[msgType]);
				#endif
				__tprintf(__tstr("%s "), (__TCHAR)&msgTypes[msgType]);
				#ifdef CONSOLE_H
				console::ChangeColor(WHITE);
				#endif
				__tvprinf(format, argptr);
				__tprintf(__tstr("\n"));
				va_end(argptr);
			}
		}
	};
}
