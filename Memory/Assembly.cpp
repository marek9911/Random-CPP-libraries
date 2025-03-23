#include "Assembly.h"
#ifdef _WIN64
#include <Windows.h>
#include <vector>

namespace jumpTable 
{
	struct PageInfo
	{
		void* begin;
		void* end;
		size_t freeSpace;
	};
	std::vector<PageInfo> pages;

	void* TryAllocatePage(void* address, size_t pageSize) {
		MEMORY_BASIC_INFORMATION mbi;
		if (VirtualQuery(address, &mbi, sizeof(mbi))) {
			if (mbi.State == MEM_FREE) {
				void* allocated = VirtualAlloc(mbi.BaseAddress, pageSize, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READ);
				if (allocated) {
					return allocated;
				}
			}
		}
		return nullptr;
	}

	PageInfo AllocatePageCloseTo(void* addrCloseTo) {
		SYSTEM_INFO sysInfo;
		GetSystemInfo(&sysInfo);

		uintptr_t alignedAddr = reinterpret_cast<uintptr_t>(addrCloseTo);
		alignedAddr -= alignedAddr % sysInfo.dwPageSize;
		alignedAddr += sysInfo.dwPageSize;
		int direction = 1;
		int offset = 0;
		while (true) {
			void* pageAddr = TryAllocatePage(reinterpret_cast<void*>(alignedAddr), sysInfo.dwPageSize);
			if (pageAddr) {
				return PageInfo{
					.begin = pageAddr,
					.end = reinterpret_cast<char*>(pageAddr) + sysInfo.dwPageSize,
					.freeSpace = sysInfo.dwPageSize,
				};
			}
			++offset;
			direction *= -1;
			alignedAddr += static_cast<int>(sysInfo.dwPageSize) * (offset * direction);
		}
	}

	void* GetMemCloseTo(void* address, size_t size) {
		if (pages.empty() || pages.back().freeSpace < size) {
			pages.push_back(AllocatePageCloseTo(address));
		}
		auto& pageInfo = pages.back();
		pageInfo.freeSpace -= size;
		return reinterpret_cast<char*>(pageInfo.end) - pageInfo.freeSpace - size;
	}

	void* PlaceJumpTo(void* from, void* to) {
		void* closeAddr = GetMemCloseTo(from, 14);
		memory::WriteElements(closeAddr, '\xFF', '\x25', 0, to);
		return closeAddr;
	}
}
#endif

static uint32_t CalculateCallAddress(void* from, void* to) {
	uintptr_t calculatedAddr = reinterpret_cast<uintptr_t>(to) - reinterpret_cast<uintptr_t>(from) - 5;
	return static_cast<uint32_t>(calculatedAddr);
}

namespace assembly
{
	void* PlaceCall(void* destination, void* addressToCall, size_t nopGapSize) {
		#ifdef _WIN64
		addressToCall = jumpTable::PlaceJumpTo(destination, addressToCall);
		#endif
		void* destStep = memory::WriteElements(destination, '\xE8', CalculateCallAddress(destination, addressToCall));
		return NopFill(destStep, nopGapSize);
	}

	void* PlaceJump(void* destination, void* addressToJump, size_t nopGapSize) {
		#ifdef _WIN64
		addressToJump = jumpTable::PlaceJumpTo(destination, addressToJump);
		#endif
		void* destStep = memory::WriteElements(destination, '\xE9', CalculateCallAddress(destination, addressToJump));
		return NopFill(destStep, nopGapSize);
	}

	void* NopFill(void* toPlace, size_t howMany) {
		return memory::Fill(toPlace, '\x90', howMany);
	}

	#ifndef _WIN64
	void RawCallDynamic(void* addressToCall, int callConvention, void* returnVariable, int returnType, int parametersSize, void* parameters) {
		int* aStart = (int*)parameters - 1;
		int* aEnd = (int*)((uintptr_t)aStart + parametersSize);
		uint64_t numRet = 0;
		uint64_t fltRet = 0;
		switch (callConvention) {
			case _STDCALL:
			case _CDECL: {
				_asm {
					mov eax, addressToCall
					mov ebx, parametersSize
					mov esi, aEnd
					mov edi, aStart
					test ebx, ebx // if parameterSize is 0 then call
					jz CdeclCall
				}
			CSPush:
				_asm {
					push [esi]
					sub esi, 4
					cmp esi, edi
					jne CSPush

					cmp callConvention, _STDCALL
					je StdcallCall
				}

			CdeclCall:
				_asm {
					call eax
					add esp, ebx
				}
				break;

			StdcallCall:
				_asm {
					call eax
				}
				break;
			}
			//case _FASTCALL:
			case _THISCALL: {
				_asm {
					mov eax, addressToCall
					mov ebx, parametersSize
					mov esi, aEnd
					mov edi, aStart
					test ebx, ebx // if parameterSize is 0 then call
					jz TFCall
					/*cmp callConvention, _FASTCALL
					je FRegisters*/
				}
			TRegisters:
				_asm {
					add edi, 4
					mov ecx, [edi]
					cmp esi, edi // if parameterSize is 1 then call
					je TFCall
					jmp TFPush // else push more
				}
			FRegisters: // fastcall broken
				_asm {
					add edi, 4
					mov ecx, [edi]
					cmp esi, edi // if parameterSize is 1 then call
					je TFCall

					add edi, 4
					mov edx, [edi]
					cmp esi, edi // if parameterSize is 2 then call
					je TFCall // else push more
				}

			TFPush:
				_asm {
					push [esi]
					sub esi, 4
					cmp esi, edi
					jne TFPush
				}

			TFCall:
				_asm {
					call eax
				}
				break;
			}
			default:
				break;
		}
		_asm {
			mov DWORD PTR [numRet], eax
			mov DWORD PTR [numRet + 4], edx
		}
		switch (returnType) {
			case _BYTE: {
				*(uint8_t*)returnVariable = *(uint8_t*)&numRet;
				break;
			}
			case _WORD: {
				*(uint16_t*)returnVariable = *(uint16_t*)&numRet;
				break;
			}
			case _DWORD: {
				*(uint32_t*)returnVariable = *(uint32_t*)&numRet;
				break;
			}
			case _QWORD: {
				*(uint64_t*)returnVariable = *(uint64_t*)&numRet;
				break;
			}
			case _FLOAT: {
				__asm fstp QWORD PTR [fltRet]
				*(float*)returnVariable = (float)*(double*)&fltRet;
				break;
			}
			case _DOUBLE: {
				__asm fstp QWORD PTR [fltRet]
				*(double*)returnVariable = *(double*)&fltRet;
				break;
			}
			case _VOID:
			default:
				break;
		}
	}

	void RawCall(void* addressToCall, int callConvention, void* returnVariable, int returnType, int parametersSize, ...) {
		RawCallDynamic(addressToCall, callConvention, returnVariable, returnType, parametersSize, &parametersSize + 1);
	}
	#endif
}
