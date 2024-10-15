#pragma once
#include <string>

namespace console
{
	// Creates a new CMD window if its not created and redirects output to it (mostly for DLL injecting)
	void CreateNewConsole();

	// Changes an CMD foreground color
	void ChangeColor(int color);

	// Changes an CMD background color
	void ChangeColorB(int backgroudColor);

	// Changes a name of window
	void ChangeTitle(const std::string& title);
	void ChangeTitle(const std::wstring& title);

	// Sets a position where text will be outputted in CMD
	void SetCursorPos(short x, short y);

	// Reads a single key press from user and returns int to ascii character
	int ReadKey();

	// Non blockingly reads a key (for inifinte loops)
	void AsyncReadKey(int* output, int* condition, int valueToStop);

	// Breaks read key (or getch) function
	void BreakReadKey();

	// Hides blinking cursor in CMD
	void HideCursor(bool hideCursor = true);

	// Hides a scroll bars on down and right side in CMD
	void HideScrollBars(bool hideScrollBars = true);

	// Enables ANSI escape sequences in CMD on Windows 10 1511 and higher
	void EnableAnsiEscapeCodes();

	// Enables UTF-8 I/O in CMD
	void EnableUTF8Output();
	void EnableUTF8Input();

	// Enables WCHAR I/O in CMD
	void EnableWCHAROutput();
	void EnableWCHARInput();

	namespace colors
	{
		static constexpr short black = 0x0;
		static constexpr short blue = 0x1;
		static constexpr short green = 0x2;
		static constexpr short aqua = 0x3;
		static constexpr short red = 0x4;
		static constexpr short purple = 0x5;
		static constexpr short yellow = 0x6;
		static constexpr short white = 0x7;
		static constexpr short gray = 0x8;
		static constexpr short lightBlue = 0x9;
		static constexpr short lightGreen = 0xA;
		static constexpr short lightAqua = 0xB;
		static constexpr short lightRed = 0xC;
		static constexpr short lightPurple = 0xD;
		static constexpr short lightYellow = 0xE;
		static constexpr short brightWhite = 0xF;
	}
	namespace keyboard
	{
		static constexpr int arrowUp = 296;
		static constexpr int arrowDown = 304;
		static constexpr int arrowLeft = 299;
		static constexpr int arrowRight = 301;
		static constexpr int escape = 27;
		static constexpr int enter = 13;
		static constexpr int space = 32;
		static constexpr int backspace = 8;
		static constexpr int tab = 9;
	}
}
