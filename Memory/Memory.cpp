#include "Memory.h"
#include "Console\Console.h"
#include <iostream>
#include <Windows.h>
#include <vector>
#include <sstream>

using namespace std;
Memory::Memory(unsigned int pointerAddress, std::vector<unsigned int> pointerOffsets)
: address((DWORD*)(*(DWORD*)((uintptr_t)GetModuleHandleA("goofball.exe") + pointerAddress))) {
    if (pointerOffsets.size() > 1)
        for (unsigned int i = 0; i < pointerOffsets.size() - 1; i++)
            address = (DWORD*)(*(DWORD*)(address + pointerOffsets[i] / 4));
    address += pointerOffsets[pointerOffsets.size() - 1] / 4;
    Console::ChangeColor(lightBlue);
    cout << "New pointer has been attached to 0x" << address << endl;
}

void Memory::Move(int offset) {
    address += offset;
    Console::ChangeColor(blue);
    cout << "Pointer moved from 0x" << address - offset << " to 0x" << address << endl;
}

void Memory::Patch(int value) {
    *(int*)address = value;
    Console::ChangeColor(lightYellow);
    cout << "Memory at 0x" << address << " changed to 0x" << uppercase << hex << value << dec << endl;
}

void Memory::Display() {
    Console::ChangeColor(lightAqua);
    cout << "Memory at 0x" << address << " is 0x" << uppercase << hex << *(int*)address << dec << endl;
}

int Memory::GetValue() {
    return *(int*)address;
}