#pragma once
#ifndef CONSOLE_H
#define CONSOLE_H
#define black 0x0
#define blue 0x1
#define green 0x2
#define aqua 0x3
#define red 0x4
#define purple 0x5
#define yellow 0x6
#define white 0x7
#define gray 0x8
#define lightBlue 0x9
#define lightGreen 0xA
#define lightAqua 0xB
#define lightRed 0xC
#define lightPurple 0xD
#define lightYellow 0xE
#define brightWhite 0xF
#include <map>
#include <string>
#include <Windows.h>
using namespace std;

class Console
{
	public:
		static void CreateNewConsole();
		static void ChangeColor(int color);
		static void ChangeTitle(LPCSTR title);
		
	private:
		static HANDLE hConsole;
};
#endif // !CONSOLE_H



