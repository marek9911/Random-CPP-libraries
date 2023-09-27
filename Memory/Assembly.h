#pragma once
#include "Memory.h"

#ifdef _WIN64
#error "This library only support x86 architecture"
#endif

#define _CDECL 1
#define _STDCALL 2
#define _THISCALL 3
#define _FASTCALL 4

#define _VOID 0
#define _BYTE 1
#define _WORD 2
#define _DWORD 3
#define _QWORD 4
#define _FLOAT 5
#define _DOUBLE 6

typedef uintptr_t _this;

class Assembly
{
	public:
		static void PlaceCall(base_offset toPlace, uintptr_t toCallAddress, size_t nopGapSize = 0);
		static void PlaceJump(base_offset toPlace, uintptr_t toJumpAddress, size_t nopGapSize = 0);
		static void NopFill(base_offset toPlace, size_t howMany);

		static void RawCallDynamic(void* addressToCall, int callConvention, void* returnVariable, int returnType, int parametersSize, void* parameters);
		static void RawCall(void* addressToCall, int callConvention, void* returnVariable, int returnType, int parametersSize, ...);

	private:
		static void PlaceInstructionPtr(base_offset toPlace, uintptr_t finalAddress, uint8_t opcode, size_t nopGapSize);
};