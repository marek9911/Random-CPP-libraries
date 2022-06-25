#pragma once
#ifndef MEMORY_H
#define MEMORY_H
#include <vector>
#include <Windows.h>
using namespace std;

class Memory
{
	public:
		Memory(unsigned int pointerAddress, vector<unsigned int> pointerOffsets);
		void Move(int offset);
		void Patch(int value);
		void Display();
		int GetValue();
	private:
		const DWORD* address;
};

#endif
