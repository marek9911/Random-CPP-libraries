#pragma once
#ifndef CONSOLE_H
#define CONSOLE_H
#if __has_include("Ascii.h")
#include "Ascii.h"
#endif

#define BLACK 0x0
#define BLUE 0x1
#define GREEN 0x2
#define AQUA 0x3
#define RED 0x4
#define PURPLE 0x5
#define YELLOW 0x6
#define WHITE 0x7
#define GRAY 0x8
#define LIGHTBLUE 0x9
#define LIGHTGREEN 0xA
#define LIGHTAQUA 0xB
#define LIGHTRED 0xC
#define LIGHTPURPLE 0xD
#define LIGHTYELLOW 0xE
#define BRIGHTWHITE 0xF

#define KB_ARROW_UP 296
#define KB_ARROW_DOWN 304
#define KB_ARROW_LEFT 299
#define KB_ARROW_RIGHT 301
#define KB_ESCAPE 27
#define KB_ENTER 13
#define KB_RETURN 13
#define KB_SPACE 32
#define KB_BACKSPACE 8
#define KB_TAB 9

#include <string>
#ifdef _WIN32
#include <tchar.h>
#include <Windows.h>
#else

#endif

class Console
{
	#ifdef _WIN32
	public:
		// Creates a new CMD window if its not created and redirects output to it (mostly for DLL injecting)
		static void CreateNewConsole();

		// Changes an CMD foreground color
		static void ChangeColor(int color);

		// Changes an CMD background color
		static void ChangeColorB(int backgroudColor);

		// Changes a name of window
		static void ChangeTitle(LPCTSTR title);

		// Sets a position where text will be outputted in CMD
		static void SetCursorPos(short x, short y);

		// Reads a single key press from user and returns int to ascii character
		static int ReadKey();

		// Reads keys asynchronously
		static void AsyncReadKey(int* output, int* condition, int valueToStop);

		// Breaks read key (or getch) function
		static void BreakReadKey();

		// Hides blinking cursor in CMD
		static void HideCursor(bool hideCursor = true);

		// Hides a scroll bars on down and right side in CMD
		static void HideScrollBars(bool hideScrollBars);

		// Enables ANSI escape sequences in CMD on Windows 10 1511 and higher
		static void EnableAnsiEscapeCodes();

		// Enables UTF-8 I/O in CMD
		static void EnableUTF8Output();
		static void EnableUTF8Input();

		// Enables WCHAR I/O in CMD
		static void EnableWCHAROutput();
		static void EnableWCHARInput();

	private:
		static HANDLE hConsole;
		static short currentColor;
		static short currentColorB;
	#else
	
	#endif
};
#endif // CONSOLE_H



