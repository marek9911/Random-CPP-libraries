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

#define KB_ARROW_UP 296
#define KB_ARROW_DOWN 304
#define KB_ARROW_LEFT 299
#define KB_ARROW_RIGHT 301
#define KB_ENTER 13
#define KB_RETURN 13
#define KB_ESCAPE 27
#include <string>
#include <Windows.h>

class Console
{
	public:
		static void CreateNewConsole();
		static void ChangeColor(int color);
		static void ChangeColorB(int backgroudColor);
		static void ChangeTitle(LPCSTR title);
		static void SetCursorPos(short x, short y);
		static int ReadKey();
		static void AsyncReadKey(int *input);
		static void HideCursor(bool hideCursor);
		static void HideScrollBars(bool hideScrollBars);
	private:
		static HANDLE hConsole;
		static short currentColor;
		static short currentColorB;
};
#endif // CONSOLE_H



