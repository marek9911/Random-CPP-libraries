#pragma once
#include "Memory/Memory.h"

#ifndef _WIN64
#define _CDECL 1
#define _STDCALL 2
#define _THISCALL 3

#define _VOID 0
#define _BYTE 1
#define _WORD 2
#define _DWORD 3
#define _QWORD 4
#define _FLOAT 5
#define _DOUBLE 6
#endif

typedef uintptr_t _this;

namespace assembly
{
	void* PlaceCall(void* destination, void* addressToCall, size_t nopGapSize = 0);
	void* PlaceJump(void* destination, void* addressToJump, size_t nopGapSize = 0);
	void* NopFill(void* destination, size_t howMany);

	#ifndef _WIN64
	void RawCallDynamic(void* addressToCall, int callConvention, void* returnVariable, int returnType, int parametersSize, void* parameters);
	void RawCall(void* addressToCall, int callConvention, void* returnVariable, int returnType, int parametersSize, ...);
	#endif
};