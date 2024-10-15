#include "Assembly.h"

static void* CalculateCallAddress(void* from, void* to) {
	uintptr_t calculatedAddr = reinterpret_cast<uintptr_t>(to) - reinterpret_cast<uintptr_t>(from) - 5;
	return reinterpret_cast<void*>(calculatedAddr);
}

namespace assembly
{
	void* PlaceCall(void* destination, void* addressToCall, size_t nopGapSize) {
		void* destStep = memory::WriteElements(destination, '\xE8', CalculateCallAddress(destination, addressToCall));
		return NopFill(destStep, nopGapSize);
	}

	void* PlaceJump(void* destination, void* addressToJump, size_t nopGapSize) {
		void* destStep = memory::WriteElements(destination, '\xE9', CalculateCallAddress(destination, addressToJump));
		return NopFill(destStep, nopGapSize);
	}

	void* NopFill(void* toPlace, size_t howMany) {
		return memory::Fill(toPlace, '\x90', howMany);
	}

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
}
