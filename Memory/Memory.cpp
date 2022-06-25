#if __has_include("Console/Console.h")
#include "Console/Console.h"
#endif
#include "Memory.h"
#include <iostream>

using namespace std;

Memory::Memory(unsigned int pointerAddress, std::vector<unsigned int> pointerOffsets)
: address((DWORD*)(*(DWORD*)((uintptr_t)GetModuleHandleA("goofball.exe") + pointerAddress))) {
    if (pointerOffsets.size() > 1)
        for (unsigned int i = 0; i < pointerOffsets.size() - 1; i++)
            address = (DWORD*)(*(DWORD*)(address + pointerOffsets[i] / 4));
    address += pointerOffsets[pointerOffsets.size() - 1] / 4;
    #ifdef CONSOLE_H
    Console::ChangeColor(lightBlue);
    #endif
    std::cout << "New pointer has been attached to 0x" << address << endl;
}

void Memory::Move(int offset) {
    address += offset;
    #ifdef CONSOLE_H
    Console::ChangeColor(blue);
    #endif
    std::cout << "Pointer moved from 0x" << address - offset << " to 0x" << address << endl;
}

void Memory::Patch(int value) {
    *(int*)address = value;
    #ifdef CONSOLE_H
    Console::ChangeColor(lightYellow);
    #endif
    std::cout << "Memory at 0x" << address << " changed to 0x" << uppercase << hex << value << dec << endl;
}

void Memory::Display() {
    #ifdef CONSOLE_H
    Console::ChangeColor(lightPurple);
    #endif
    cout << "Memory at 0x" << address << " is 0x" << uppercase << hex << *(int*)address << endl;
}

int Memory::GetValue() {
    return *(int*)address;
}