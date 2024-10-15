#include "Console.h"
#include <Windows.h>
#include <conio.h>
#include <io.h>
#include <fcntl.h>

static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
static short currentColor = console::colors::white;
static short currentColorB = console::colors::black;

namespace console
{
	void CreateNewConsole() {
		AllocConsole();
		FILE* out;
		freopen_s(&out, "CONIN$", "r", stdin);
		freopen_s(&out, "CONOUT$", "w", stdout);
		freopen_s(&out, "CONOUT$", "w", stderr);
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	void ChangeColor(int color) {
		currentColor = color;
		SetConsoleTextAttribute(hConsole, currentColor + currentColorB);
	}

	void ChangeColorB(int backgroudColor) {
		currentColorB = backgroudColor * 16;
		SetConsoleTextAttribute(hConsole, currentColor + currentColorB);
	}

	void ChangeTitle(const std::string& title) {
		SetConsoleTitleA(title.c_str());
	}

	void ChangeTitle(const std::wstring& title) {
		SetConsoleTitleW(title.c_str());
	}

	void SetCursorPos(short x, short y) {
		SetConsoleCursorPosition(hConsole, { x, y });
	}

	int ReadKey() {
		int keyValue = _getch();
		if (keyValue == 224) {
			keyValue += _getch();
		}
		return keyValue;
	}

	void AsyncReadKey(int* output, int* condition, int valueToStop) {
		while (*condition != valueToStop){
			if (_kbhit()) {
				*output = ReadKey();
			}
			Sleep(10);
		}
	}

	void BreakReadKey() {
		_ungetch(0);
	}

	void HideCursor(bool hideCursor) {
		CONSOLE_CURSOR_INFO cursorInfo;
		GetConsoleCursorInfo(hConsole, &cursorInfo);
		cursorInfo.bVisible = !hideCursor;
		SetConsoleCursorInfo(hConsole, &cursorInfo);
	}

	void HideScrollBars(bool hideScrollBars) {
		if (hideScrollBars) {
			ShowScrollBar(GetConsoleWindow(), SB_BOTH, ESB_ENABLE_BOTH);
		}
		else {
			ShowScrollBar(GetConsoleWindow(), SB_BOTH, ESB_DISABLE_BOTH);
		}
	}

	void EnableAnsiEscapeCodes() {
		DWORD consoleMode;
		if (GetConsoleMode(hConsole, &consoleMode)) {
			SetConsoleMode(hConsole, consoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
		}
	}

	void EnableUTF8Output() {
		SetConsoleOutputCP(65001);
	}

	void EnableUTF8Input() {
		SetConsoleCP(65001);
	}

	void EnableWCHAROutput() {
		int nul = _setmode(_fileno(stdout), _O_U16TEXT);
	}

	void EnableWCHARInput() {
		int nul = _setmode(_fileno(stdin), _O_U16TEXT);
	}
}
