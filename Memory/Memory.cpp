#include "Memory.h"
#include <Windows.h>
#include <Psapi.h>
#include <iostream>

#define HINIBBLE(x) ((((uint8_t)(x) >> 4) | 0xF0) ^ 0xF0)
#define LONIBBLE(x) (((uint8_t)(x) | 0xF0) ^ 0xF0)

namespace memory
{
	RegionUnlocker::RegionUnlocker(void* region, size_t size) 
	: pageInfo(UnlockRegion(region, size)) {}

	RegionUnlocker::~RegionUnlocker() {
		RestoreRegion(this->pageInfo);
	}

	PageInfo UnlockRegion(void* region, size_t size) {
		PageInfo pageProtection { region, size };
		VirtualProtect(region, size, PAGE_EXECUTE_READWRITE, &pageProtection.pageProtection);
		return pageProtection;
	}

	void RestoreRegion(const PageInfo& pageInfo) {
		DWORD pageProtection;
		VirtualProtect(pageInfo.region, pageInfo.size, pageInfo.pageProtection, &pageProtection);
	}

	void* GetBaseAddress() {
		static void* const baseAddress = GetModuleHandleW(nullptr);
		return baseAddress;
	}

	void* Write(void* destination, const void* source, size_t size) {
		if (size == 0) {
			return destination;
		}
		RegionUnlocker reg(destination, size);
		memcpy(destination, source, size);
		return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(destination) + size);
	}
	
	void* Write(void* destination, const std::string& string) {
		return Write(destination, string.c_str(), string.size() * sizeof(char) + sizeof(char));
	}

	void* Write(void* destination, const std::wstring& string) {
		return Write(destination, string.c_str(), string.size() * sizeof(wchar_t) + sizeof(wchar_t));
	}

	void* Fill(void* destination, uint8_t value, size_t size) {
		if (size == 0) {
			return destination;
		}
		RegionUnlocker reg(destination, size);
		memset(destination, value, size);
		return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(destination) + size);
	}

	std::string HexDump(const void* destination, size_t size) {
		const char* dest = reinterpret_cast<const char*>(destination);
		const char* arr = "0123456789ABCDEF";
		std::string hex;
		for (size_t i = 0; i < size; i++) {
			hex += arr[HINIBBLE(dest[i])];
			hex += arr[LONIBBLE(dest[i])];
			hex += ' ';
		}
		hex.pop_back();
		return hex;
	}

	std::wstring HexDumpW(const void* destination, size_t size) {
		const char* dest = reinterpret_cast<const char*>(destination);
		const wchar_t* arr = L"0123456789ABCDEF";
		std::wstring hex;
		for (size_t i = 0; i < size; i++) {
			hex += arr[HINIBBLE(dest[i])];
			hex += arr[LONIBBLE(dest[i])];
			hex += ' ';
		}
		hex.pop_back();
		return hex;
	}

	bool CheckReadableAddress(const void* address) {
		MEMORY_BASIC_INFORMATION mbi;
		VirtualQuery(address, &mbi, sizeof(mbi));
		return mbi.Protect > 0x01;
	}

	bool CheckWritableAddress(const void* address) {
		MEMORY_BASIC_INFORMATION mbi;
		VirtualQuery(address, &mbi, sizeof(mbi));
		return mbi.Protect == 0x04 || mbi.Protect == 0x08 || mbi.Protect == 0x40 || mbi.Protect == 0x80;
	}
}
