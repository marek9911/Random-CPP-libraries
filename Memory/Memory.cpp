#if __has_include("Console/Console.h")
#include "Console/Console.h"
#endif
#include "Memory.h"
#include <Psapi.h>
#include <iostream>

uintptr_t Memory::GetBaseAddress() {
	return baseAddress;
}

void Memory::HexWrite(uintptr_t pointerWithoutBase, const char* bytes, size_t size, bool addBaseAddress) {
	#pragma warning(disable:6387)
	uintptr_t ptr = pointerWithoutBase;
	if (addBaseAddress) {
		ptr += GetBaseAddress();
	}
	size_t byteSize = size;
	if (byteSize == 0) {
		byteSize = strlen(bytes) + 1;
	}
	DWORD OldProtection;
	VirtualProtect((LPVOID)(ptr), byteSize, PAGE_EXECUTE_READWRITE, &OldProtection);
	memcpy((LPVOID)ptr, bytes, byteSize);
	VirtualProtect((LPVOID)(ptr), byteSize, OldProtection, NULL);
	#pragma warning(default:6387)
}

void Memory::Fill(uintptr_t pointerWithoutBase, uint8_t value, size_t size, bool addBaseAddress) {
	#pragma warning(disable:6387)
	uintptr_t ptr = pointerWithoutBase;
	if (addBaseAddress) {
		ptr += GetBaseAddress();
	}
	DWORD OldProtection;
	VirtualProtect((LPVOID)(ptr), size, PAGE_EXECUTE_READWRITE, &OldProtection);
	memset((LPVOID)ptr, value, size);
	VirtualProtect((LPVOID)(ptr), size, OldProtection, NULL);
	#pragma warning(default:6387)
}


void Memory::hexDump(void* ptr, size_t size) {
	unsigned char* chptr = (unsigned char*)ptr;
	__tcout << std::hex << std::uppercase;
	for (size_t i = 0; i < size; i++) {
		if (*chptr < 0x10) {
			__tcout << __tstr("0");
		}
		__tcout << (int)*(chptr++) << __tstr(" ");
	}
	__tcout << std::dec << std::endl;
}

bool Memory::CheckReadableAddress(uintptr_t address) {
	MEMORY_BASIC_INFORMATION mbi;
	VirtualQuery((LPCVOID)address, &mbi, sizeof(mbi));
	if (mbi.Protect > 0x01) {
		return false;
	}
	return true;
}

bool Memory::CheckWritableAddress(uintptr_t address) {
	MEMORY_BASIC_INFORMATION mbi;
	VirtualQuery((LPCVOID)address, &mbi, sizeof(mbi));
	if (mbi.Protect == 0x04 || mbi.Protect == 0x08 || mbi.Protect == 0x40 || mbi.Protect == 0x80) {
		return false;
	}
	return true;
}

uintptr_t Memory::CalculateBaseAddress() {
	HANDLE hpr = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId());
	LPWSTR pname = new WCHAR[1024];
	GetProcessImageFileNameW(hpr, pname, 1024);
	std::wstring path = pname;
	delete[] pname;
	path = path.substr(path.find_last_of(L"/\\") + 1);
	return (uintptr_t)GetModuleHandleW(path.c_str());
}

uintptr_t Memory::baseAddress = CalculateBaseAddress();

