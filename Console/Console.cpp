#include "Console.h"
#include <iostream>

using namespace std;
void Console::CreateNewConsole() {
	AllocConsole();
	FILE* out;
	freopen_s(&out, "CONOUT$", "wb", stdout);
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ChangeColor(brightWhite);
	cout << " ----- Console started -----" << endl << endl;
}

void Console::ChangeColor(int color) {
	SetConsoleTextAttribute(hConsole, color);
}

void Console::ChangeTitle(LPCSTR title) {
	SetConsoleTitleA(title);
}

HANDLE Console::hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
