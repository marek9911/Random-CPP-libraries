#pragma once
#ifndef CONSOLE_H
#define CONSOLE_H

/*#ifdef UNICODE
	#define BOX_DN_R u8"╔"	// ╔
	#define BOX_UP_R u8"╚"	// ╚
	#define BOX_DN_L u8"╗"	// ╗
	#define BOX_UP_L u8"╝"	// ╝
	#define BOX_VT u8"║"	// ║
	#define BOX_HT u8"═"	// ═
	#define LINE_DN_R u8"┌"	// ┌
	#define LINE_UP_R u8"└"	// └
	#define LINE_DN_L u8"┐"	// ┐
	#define LINE_UP_L u8"┘"	// ┘
	#define LINE_VT u8"│"	// │
	#define LINE_HT u8"─"	// ─
#else*/
	#define BOX_DN_R char(201)	// ╔
	#define BOX_UP_R char(200)	// ╚
	#define BOX_DN_L char(187)	// ╗
	#define BOX_UP_L char(188)	// ╝
	#define BOX_VT char(186)	// ║
	#define BOX_HT char(205)	// ═
	#define BOX_3W_R char(204)	// ╠
	#define BOX_3W_L char(185)	// ╣
	#define BOX_3W_U char(202)	// ╩
	#define BOX_3W_D char(203)	// ╦
	#define BOX_4W char(206)	// ╬

	#define LINE_DN_R char(218)	// ┌
	#define LINE_UP_R char(192)	// └
	#define LINE_DN_L char(191)	// ┐
	#define LINE_UP_L char(217)	// ┘
	#define LINE_VT char(179)	// │
	#define LINE_HT char(196)	// ─
	#define LINE_3W_R char(195)	// ├
	#define LINE_3W_L char(180)	// ┤
	#define LINE_3W_U char(193)	// ┴
	#define LINE_3W_D char(194)	// ┬
	#define LINE_4W char(197)	// ┼
//#endif

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

#define ANSI_RESET "\033[0m"
#define ANSI_BOLD "\033[1m"
#define ANSI_UNDERLINE "\033[4m"
#define ANSI_INVERSE "\033[7m"

#define ANSI_BLACK "\033[30m"
#define ANSI_RED "\033[31m"
#define ANSI_GREEN "\033[32m"
#define ANSI_YELLOW "\033[33m"
#define ANSI_BLUE "\033[34m"
#define ANSI_PURPLE "\033[35m"
#define ANSI_CYAN "\033[36m"
#define ANSI_WHITE "\033[37m"

#define ANSI_LIGHTBLACK "\033[90m"
#define ANSI_LIGHTRED "\033[91m"
#define ANSI_LIGHTGREEN "\033[92m"
#define ANSI_LIGHTYELLOW "\033[93m"
#define ANSI_LIGHTBLUE "\033[94m"
#define ANSI_LIGHTPURPLE "\033[95m"
#define ANSI_LIGHTCYAN "\033[96m"
#define ANSI_LIGHTWHITE "\033[97m"

#define ANSI_BLACK_B "\033[40m"
#define ANSI_RED_B "\033[41m"
#define ANSI_GREEN_B "\033[42m"
#define ANSI_YELLOW_B "\033[43m"
#define ANSI_BLUE_B "\033[44m"
#define ANSI_PURPLE_B "\033[45m"
#define ANSI_CYAN_B "\033[46m"
#define ANSI_WHITE_B "\033[47m"

#define ANSI_LIGHTBLACK_B "\033[100m"
#define ANSI_LIGHTRED_B "\033[101m"
#define ANSI_LIGHTGREEN_B "\033[102m"
#define ANSI_LIGHTYELLOW_B "\033[103m"
#define ANSI_LIGHTBLUE_B "\033[104m"
#define ANSI_LIGHTPURPLE_B "\033[105m"
#define ANSI_LIGHTCYAN_B "\033[106m"
#define ANSI_LIGHTWHITE_B "\033[107m"

#define KB_ARROW_UP 296
#define KB_ARROW_DOWN 304
#define KB_ARROW_LEFT 299
#define KB_ARROW_RIGHT 301
#define KB_ESCAPE 27
#define KB_ENTER 13
#define KB_RETURN 13

#include <tchar.h>
#include <string>
#include <Windows.h>

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

		// Hides blinking cursor in CMD
		static void HideCursor(bool hideCursor);

		// Hides a scroll bars on down and right side in CMD
		static void HideScrollBars(bool hideScrollBars);

		// Enables ANSI escape sequences in CMD on Windows 10 1511 and higher
		static void FixAnsiCodes();

	private:
		static HANDLE hConsole;
		static short currentColor;
		static short currentColorB;
	#endif
};
#endif // CONSOLE_H



