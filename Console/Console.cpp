#include "Console.h"
#include <iostream>
#include <conio.h>

void Console::CreateNewConsole() {
	AllocConsole();
	FILE* out;
	freopen_s(&out, "CONOUT$", "wb", stdout);
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ChangeColor(BRIGHTWHITE);
	std::cout << " ----- Console started -----" << std::endl << std::endl;
}

void Console::ChangeColor(int color) {
	currentColor = color;
	SetConsoleTextAttribute(hConsole, currentColor + currentColorB);
}

void Console::ChangeColorB(int backgroudColor) {
	currentColorB = backgroudColor * 16;
	SetConsoleTextAttribute(hConsole, currentColor + currentColorB);
}

void Console::ChangeTitle(LPCSTR title) {
	SetConsoleTitleA(title);
}

void Console::SetCursorPos(short x, short y) {
	SetConsoleCursorPosition(hConsole, { x, y });
}

int Console::ReadKey() {
	int keyValue = _getch();
	if (keyValue == 224)
		keyValue += _getch();
	return keyValue;
}

void Console::AsyncReadKey(int* output, int* condition, int valueToStop) {
	while (*condition != valueToStop){
		if (_kbhit())
			*output = ReadKey();
		Sleep(10);
	}
}

void Console::HideCursor(bool hideCursor) {
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = !hideCursor;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void Console::HideScrollBars(bool hideScrollBars) {
	if (hideScrollBars)
		ShowScrollBar(GetConsoleWindow(), SB_BOTH, ESB_ENABLE_BOTH);
	else
		ShowScrollBar(GetConsoleWindow(), SB_BOTH, ESB_DISABLE_BOTH);
}

void Console::FixAnsiCodes()
{
	DWORD consoleMode;
	if (GetConsoleMode(hConsole, &consoleMode))
		SetConsoleMode(hConsole, consoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

HANDLE Console::hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
short Console::currentColor = WHITE;
short Console::currentColorB = BLACK;