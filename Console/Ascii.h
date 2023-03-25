﻿#pragma once

#define ANSI_PREFIX "\033["
#define ANSI_SUFFIX "m"

#define MACRO_TO_VALUE(value, macro) macro(value)
#define MAKE_STRING(string) #string
#define MAKE_WIDE(string) L##string
#define MAKE_U8(string) u8##string
#define MAKE_ESCAPE(color) ANSI_PREFIX MACRO_TO_VALUE(color, MAKE_STRING) ANSI_SUFFIX

// Ansi escape sequence codes
#define __ASC_RESET				0
#define __ASC_BOLD				1
#define __ASC_UNDERLINE			4
#define __ASC_INVERSE			7
#define __ASC_RESET_BOLD		22
#define __ASC_RESET_UNDERLINE	24
#define __ASC_RESET_INVERSE		27

#define __ASC_BLACK		30
#define __ASC_RED		31
#define __ASC_GREEN		32
#define __ASC_YELLOW	33
#define __ASC_BLUE		34
#define __ASC_PURPLE	35
#define __ASC_CYAN		36
#define __ASC_WHITE		37

#define __ASC_LBLACK	90
#define __ASC_LRED		91
#define __ASC_LGREEN	92
#define __ASC_LYELLOW	93
#define __ASC_LBLUE		94
#define __ASC_LPURPLE	95
#define __ASC_LCYAN		96
#define __ASC_LWHITE	97

#define __ASC_BLACK_B	40
#define __ASC_RED_B		41
#define __ASC_GREEN_B	42
#define __ASC_YELLOW_B	43
#define __ASC_BLUE_B	44
#define __ASC_PURPLE_B	45
#define __ASC_CYAN_B	46
#define __ASC_WHITE_B	47

#define __ASC_LBLACK_B	100
#define __ASC_LRED_B	101
#define __ASC_LGREEN_B	102
#define __ASC_LYELLOW_B	103
#define __ASC_LBLUE_B	104
#define __ASC_LPURPLE_B	105
#define __ASC_LCYAN_B	106
#define __ASC_LWHITE_B	107

// Box and line drawing characters
#define __ASC_LINE_DN_R	"┌"
#define __ASC_LINE_UP_R	"└"
#define __ASC_LINE_DN_L	"┐"
#define __ASC_LINE_UP_L	"┘"
#define __ASC_LINE_VT	"│"
#define __ASC_LINE_HT	"─"
#define __ASC_LINE_3W_R	"├"
#define __ASC_LINE_3W_L	"┤"
#define __ASC_LINE_3W_U	"┴"
#define __ASC_LINE_3W_D	"┬"
#define __ASC_LINE_4W	"┼"

#define __ASC_BOX_DN_R	"╔"
#define __ASC_BOX_UP_R	"╚"
#define __ASC_BOX_DN_L	"╗"
#define __ASC_BOX_UP_L	"╝"
#define __ASC_BOX_VT	"║"
#define __ASC_BOX_HT	"═"
#define __ASC_BOX_3W_R	"╠"
#define __ASC_BOX_3W_L	"╣"
#define __ASC_BOX_3W_U	"╩"
#define __ASC_BOX_3W_D	"╦"
#define __ASC_BOX_4W	"╬"

#define __ASC_VBOX_DN_R	"╓"
#define __ASC_VBOX_UP_R	"╙"
#define __ASC_VBOX_DN_L	"╖"
#define __ASC_VBOX_UP_L	"╜"
#define __ASC_VBOX_VT	"║"
#define __ASC_VBOX_HT	"─"
#define __ASC_VBOX_3W_R	"╟"
#define __ASC_VBOX_3W_L	"╢"
#define __ASC_VBOX_3W_U	"╨"
#define __ASC_VBOX_3W_D	"╥"
#define __ASC_VBOX_4W	"╫"

#define __ASC_HBOX_DN_R	"╒"
#define __ASC_HBOX_UP_R	"╘"
#define __ASC_HBOX_DN_L	"╕"
#define __ASC_HBOX_UP_L	"╛"
#define __ASC_HBOX_VT	"│"
#define __ASC_HBOX_HT	"═"
#define __ASC_HBOX_3W_R	"╞"
#define __ASC_HBOX_3W_L	"╡"
#define __ASC_HBOX_3W_U	"╧"
#define __ASC_HBOX_3W_D	"╤"
#define __ASC_HBOX_4W	"╪"

#define __ASC_BLOCK		"█"
#define __ASC_BLOCK_R	"▐"
#define __ASC_BLOCK_L	"▌"
#define __ASC_BLOCK_U	"▀"
#define __ASC_BLOCK_D	"▄"
#define __ASC_BLOCK_25	"░"
#define __ASC_BLOCK_50	"▒"
#define __ASC_BLOCK_75	"▓"



// ASCII ANSI COLORS
#define ANSI_RESET MAKE_ESCAPE(__ASC_RESET)
#define ANSI_BOLD MAKE_ESCAPE(__ASC_BOLD)
#define ANSI_UNDERLINE MAKE_ESCAPE(__ASC_UNDERLINE)
#define ANSI_INVERSE MAKE_ESCAPE(__ASC_INVERSE)
#define ANSI_RESET_BOLD MAKE_ESCAPE(__ASC_RESET_BOLD)
#define ANSI_RESET_UNDERLINE MAKE_ESCAPE(__ASC_RESET_UNDERLINE)
#define ANSI_RESET_INVERSE MAKE_ESCAPE(__ASC_RESET_INVERSE)

#define ANSI_BLACK MAKE_ESCAPE(__ASC_BLACK)
#define ANSI_RED MAKE_ESCAPE(__ASC_RED)
#define ANSI_GREEN MAKE_ESCAPE(__ASC_GREEN)
#define ANSI_YELLOW MAKE_ESCAPE(__ASC_YELLOW)
#define ANSI_BLUE MAKE_ESCAPE(__ASC_BLUE)
#define ANSI_PURPLE MAKE_ESCAPE(__ASC_PURPLE)
#define ANSI_CYAN MAKE_ESCAPE(__ASC_CYAN)
#define ANSI_WHITE MAKE_ESCAPE(__ASC_WHITE)

#define ANSI_LIGHTBLACK MAKE_ESCAPE(__ASC_LBLACK)
#define ANSI_LIGHTRED MAKE_ESCAPE(__ASC_LRED)
#define ANSI_LIGHTGREEN MAKE_ESCAPE(__ASC_LGREEN)
#define ANSI_LIGHTYELLOW MAKE_ESCAPE(__ASC_LYELLOW)
#define ANSI_LIGHTBLUE MAKE_ESCAPE(__ASC_LBLUE)
#define ANSI_LIGHTPURPLE MAKE_ESCAPE(__ASC_LPURPLE)
#define ANSI_LIGHTCYAN MAKE_ESCAPE(__ASC_LCYAN)
#define ANSI_LIGHTWHITE MAKE_ESCAPE(__ASC_LWHITE)

#define ANSI_BLACK_B MAKE_ESCAPE(__ASC_BLACK_B)
#define ANSI_RED_B MAKE_ESCAPE(__ASC_RED_B)
#define ANSI_GREEN_B MAKE_ESCAPE(__ASC_GREEN_B)
#define ANSI_YELLOW_B MAKE_ESCAPE(__ASC_YELLOW_B)
#define ANSI_BLUE_B MAKE_ESCAPE(__ASC_BLUE_B)
#define ANSI_PURPLE_B MAKE_ESCAPE(__ASC_PURPLE_B)
#define ANSI_CYAN_B MAKE_ESCAPE(__ASC_CYAN_B)
#define ANSI_WHITE_B MAKE_ESCAPE(__ASC_WHITE_B)

#define ANSI_LIGHTBLACK_B MAKE_ESCAPE(__ASC_LBLACK_B)
#define ANSI_LIGHTRED_B MAKE_ESCAPE(__ASC_LRED_B)
#define ANSI_LIGHTGREEN_B MAKE_ESCAPE(__ASC_LGREEN_B)
#define ANSI_LIGHTYELLOW_B MAKE_ESCAPE(__ASC_LYELLOW_B)
#define ANSI_LIGHTBLUE_B MAKE_ESCAPE(__ASC_LBLUE_B)
#define ANSI_LIGHTPURPLE_B MAKE_ESCAPE(__ASC_LPURPLE_B)
#define ANSI_LIGHTCYAN_B MAKE_ESCAPE(__ASC_LCYAN_B)
#define ANSI_LIGHTWHITE_B MAKE_ESCAPE(__ASC_LWHITE_B)


// WIDE ANSI COLORS
#define W_ANSI_RESET MACRO_TO_VALUE(ANSI_RESET, MAKE_WIDE)
#define W_ANSI_BOLD MACRO_TO_VALUE(ANSI_BOLD, MAKE_WIDE)
#define W_ANSI_UNDERLINE MACRO_TO_VALUE(ANSI_UNDERLINE, MAKE_WIDE)
#define W_ANSI_INVERSE MACRO_TO_VALUE(ANSI_INVERSE, MAKE_WIDE)
#define W_ANSI_RESET_BOLD MACRO_TO_VALUE(ANSI_RESET_BOLD, MAKE_WIDE)
#define W_ANSI_RESET_UNDERLINE MACRO_TO_VALUE(ANSI_RESET_UNDERLINE, MAKE_WIDE)
#define W_ANSI_RESET_INVERSE MACRO_TO_VALUE(ANSI_RESET_INVERSE, MAKE_WIDE)

#define W_ANSI_BLACK MACRO_TO_VALUE(ANSI_BLACK, MAKE_WIDE)
#define W_ANSI_RED MACRO_TO_VALUE(ANSI_RED, MAKE_WIDE)
#define W_ANSI_GREEN MACRO_TO_VALUE(ANSI_GREEN, MAKE_WIDE)
#define W_ANSI_YELLOW MACRO_TO_VALUE(ANSI_YELLOW, MAKE_WIDE)
#define W_ANSI_BLUE MACRO_TO_VALUE(ANSI_BLUE, MAKE_WIDE)
#define W_ANSI_PURPLE MACRO_TO_VALUE(ANSI_PURPLE, MAKE_WIDE)
#define W_ANSI_CYAN MACRO_TO_VALUE(ANSI_CYAN, MAKE_WIDE)
#define W_ANSI_WHITE MACRO_TO_VALUE(ANSI_WHITE, MAKE_WIDE)

#define W_ANSI_LIGHTBLACK MACRO_TO_VALUE(ANSI_LIGHTBLACK, MAKE_WIDE)
#define W_ANSI_LIGHTRED MACRO_TO_VALUE(ANSI_LIGHTRED, MAKE_WIDE)
#define W_ANSI_LIGHTGREEN MACRO_TO_VALUE(ANSI_LIGHTGREEN, MAKE_WIDE)
#define W_ANSI_LIGHTYELLOW MACRO_TO_VALUE(ANSI_LIGHTYELLOW, MAKE_WIDE)
#define W_ANSI_LIGHTBLUE MACRO_TO_VALUE(ANSI_LIGHTBLUE, MAKE_WIDE)
#define W_ANSI_LIGHTPURPLE MACRO_TO_VALUE(ANSI_LIGHTPURPLE, MAKE_WIDE)
#define W_ANSI_LIGHTCYAN MACRO_TO_VALUE(ANSI_LIGHTCYAN, MAKE_WIDE)
#define W_ANSI_LIGHTWHITE MACRO_TO_VALUE(ANSI_LIGHTWHITE, MAKE_WIDE)

#define W_ANSI_BLACK_B MACRO_TO_VALUE(ANSI_BLACK_B, MAKE_WIDE)
#define W_ANSI_RED_B MACRO_TO_VALUE(ANSI_RED_B, MAKE_WIDE)
#define W_ANSI_GREEN_B MACRO_TO_VALUE(ANSI_GREEN_B, MAKE_WIDE)
#define W_ANSI_YELLOW_B MACRO_TO_VALUE(ANSI_YELLOW_B, MAKE_WIDE)
#define W_ANSI_BLUE_B MACRO_TO_VALUE(ANSI_BLUE_B, MAKE_WIDE)
#define W_ANSI_PURPLE_B MACRO_TO_VALUE(ANSI_PURPLE_B, MAKE_WIDE)
#define W_ANSI_CYAN_B MACRO_TO_VALUE(ANSI_CYAN_B, MAKE_WIDE)
#define W_ANSI_WHITE_B MACRO_TO_VALUE(ANSI_WHITE_B, MAKE_WIDE)

#define W_ANSI_LIGHTBLACK_B MACRO_TO_VALUE(ANSI_LIGHTBLACK_B, MAKE_WIDE)
#define W_ANSI_LIGHTRED_B MACRO_TO_VALUE(ANSI_LIGHTRED_B, MAKE_WIDE)
#define W_ANSI_LIGHTGREEN_B MACRO_TO_VALUE(ANSI_LIGHTGREEN_B, MAKE_WIDE)
#define W_ANSI_LIGHTYELLOW_B MACRO_TO_VALUE(ANSI_LIGHTYELLOW_B, MAKE_WIDE)
#define W_ANSI_LIGHTBLUE_B MACRO_TO_VALUE(ANSI_LIGHTBLUE_B, MAKE_WIDE)
#define W_ANSI_LIGHTPURPLE_B MACRO_TO_VALUE(ANSI_LIGHTPURPLE_B, MAKE_WIDE)
#define W_ANSI_LIGHTCYAN_B MACRO_TO_VALUE(ANSI_LIGHTCYAN_B, MAKE_WIDE)
#define W_ANSI_LIGHTWHITE_B MACRO_TO_VALUE(ANSI_LIGHTWHITE_B, MAKE_WIDE)


// UTF-8 ANSI COLORS
#define U8_ANSI_RESET MACRO_TO_VALUE(ANSI_RESET, MAKE_U8)
#define U8_ANSI_BOLD MACRO_TO_VALUE(ANSI_BOLD, MAKE_U8)
#define U8_ANSI_UNDERLINE MACRO_TO_VALUE(ANSI_UNDERLINE, MAKE_U8)
#define U8_ANSI_INVERSE MACRO_TO_VALUE(ANSI_INVERSE, MAKE_U8)
#define U8_ANSI_RESET_BOLD MACRO_TO_VALUE(ANSI_RESET_BOLD, MAKE_U8)
#define U8_ANSI_RESET_UNDERLINE MACRO_TO_VALUE(ANSI_RESET_UNDERLINE, MAKE_U8)
#define U8_ANSI_RESET_INVERSE MACRO_TO_VALUE(ANSI_RESET_INVERSE, MAKE_U8)

#define U8_ANSI_BLACK MACRO_TO_VALUE(ANSI_BLACK, MAKE_U8)
#define U8_ANSI_RED MACRO_TO_VALUE(ANSI_RED, MAKE_U8)
#define U8_ANSI_GREEN MACRO_TO_VALUE(ANSI_GREEN, MAKE_U8)
#define U8_ANSI_YELLOW MACRO_TO_VALUE(ANSI_YELLOW, MAKE_U8)
#define U8_ANSI_BLUE MACRO_TO_VALUE(ANSI_BLUE, MAKE_U8)
#define U8_ANSI_PURPLE MACRO_TO_VALUE(ANSI_PURPLE, MAKE_U8)
#define U8_ANSI_CYAN MACRO_TO_VALUE(ANSI_CYAN, MAKE_U8)
#define U8_ANSI_WHITE MACRO_TO_VALUE(ANSI_WHITE, MAKE_U8)

#define U8_ANSI_LIGHTBLACK MACRO_TO_VALUE(ANSI_LIGHTBLACK, MAKE_U8)
#define U8_ANSI_LIGHTRED MACRO_TO_VALUE(ANSI_LIGHTRED, MAKE_U8)
#define U8_ANSI_LIGHTGREEN MACRO_TO_VALUE(ANSI_LIGHTGREEN, MAKE_U8)
#define U8_ANSI_LIGHTYELLOW MACRO_TO_VALUE(ANSI_LIGHTYELLOW, MAKE_U8)
#define U8_ANSI_LIGHTBLUE MACRO_TO_VALUE(ANSI_LIGHTBLUE, MAKE_U8)
#define U8_ANSI_LIGHTPURPLE MACRO_TO_VALUE(ANSI_LIGHTPURPLE, MAKE_U8)
#define U8_ANSI_LIGHTCYAN MACRO_TO_VALUE(ANSI_LIGHTCYAN, MAKE_U8)
#define U8_ANSI_LIGHTWHITE MACRO_TO_VALUE(ANSI_LIGHTWHITE, MAKE_U8)

#define U8_ANSI_BLACK_B MACRO_TO_VALUE(ANSI_BLACK_B, MAKE_U8)
#define U8_ANSI_RED_B MACRO_TO_VALUE(ANSI_RED_B, MAKE_U8)
#define U8_ANSI_GREEN_B MACRO_TO_VALUE(ANSI_GREEN_B, MAKE_U8)
#define U8_ANSI_YELLOW_B MACRO_TO_VALUE(ANSI_YELLOW_B, MAKE_U8)
#define U8_ANSI_BLUE_B MACRO_TO_VALUE(ANSI_BLUE_B, MAKE_U8)
#define U8_ANSI_PURPLE_B MACRO_TO_VALUE(ANSI_PURPLE_B, MAKE_U8)
#define U8_ANSI_CYAN_B MACRO_TO_VALUE(ANSI_CYAN_B, MAKE_U8)
#define U8_ANSI_WHITE_B MACRO_TO_VALUE(ANSI_WHITE_B, MAKE_U8)

#define U8_ANSI_LIGHTBLACK_B MACRO_TO_VALUE(ANSI_LIGHTBLACK_B, MAKE_U8)
#define U8_ANSI_LIGHTRED_B MACRO_TO_VALUE(ANSI_LIGHTRED_B, MAKE_U8)
#define U8_ANSI_LIGHTGREEN_B MACRO_TO_VALUE(ANSI_LIGHTGREEN_B, MAKE_U8)
#define U8_ANSI_LIGHTYELLOW_B MACRO_TO_VALUE(ANSI_LIGHTYELLOW_B, MAKE_U8)
#define U8_ANSI_LIGHTBLUE_B MACRO_TO_VALUE(ANSI_LIGHTBLUE_B, MAKE_U8)
#define U8_ANSI_LIGHTPURPLE_B MACRO_TO_VALUE(ANSI_LIGHTPURPLE_B, MAKE_U8)
#define U8_ANSI_LIGHTCYAN_B MACRO_TO_VALUE(ANSI_LIGHTCYAN_B, MAKE_U8)
#define U8_ANSI_LIGHTWHITE_B MACRO_TO_VALUE(ANSI_LIGHTWHITE_B, MAKE_U8)



// ASCII BOX DRAWINGS (THIS DOESN'T SUPPORT SOME CHARACTERS)
#define ASCII_BOX_DN_R	((char)201)	// ╔
#define ASCII_BOX_UP_R	((char)200)	// ╚
#define ASCII_BOX_DN_L	((char)187)	// ╗
#define ASCII_BOX_UP_L	((char)188)	// ╝
#define ASCII_BOX_VT	((char)186)	// ║
#define ASCII_BOX_HT	((char)205)	// ═
#define ASCII_BOX_3W_R	((char)204)	// ╠
#define ASCII_BOX_3W_L	((char)185)	// ╣
#define ASCII_BOX_3W_U	((char)202)	// ╩
#define ASCII_BOX_3W_D	((char)203)	// ╦
#define ASCII_BOX_4W	((char)206)	// ╬

#define ASCII_LINE_DN_R	((char)218)	// ┌
#define ASCII_LINE_UP_R	((char)192)	// └
#define ASCII_LINE_DN_L	((char)191)	// ┐
#define ASCII_LINE_UP_L	((char)217)	// ┘
#define ASCII_LINE_VT	((char)179)	// │
#define ASCII_LINE_HT	((char)196)	// ─
#define ASCII_LINE_3W_R	((char)195)	// ├
#define ASCII_LINE_3W_L	((char)180)	// ┤
#define ASCII_LINE_3W_U	((char)193)	// ┴
#define ASCII_LINE_3W_D	((char)194)	// ┬
#define ASCII_LINE_4W	((char)197)	// ┼

#define ASCII_BLOCK		((char)219)	// █
#define ASCII_BLOCK_U	((char)223)	// ▀
#define ASCII_BLOCK_D	((char)220)	// ▄
#define ASCII_BLOCK_25	((char)176)	// ░
#define ASCII_BLOCK_50	((char)177)	// ▒
#define ASCII_BLOCK_75	((char)178)	// ▓


// WIDE BOX DRAWINGS
#define W_LINE_DN_R MACRO_TO_VALUE(__ASC_LINE_DN_R, MAKE_WIDE)
#define W_LINE_UP_R MACRO_TO_VALUE(__ASC_LINE_UP_R, MAKE_WIDE)
#define W_LINE_DN_L MACRO_TO_VALUE(__ASC_LINE_DN_L, MAKE_WIDE)
#define W_LINE_UP_L MACRO_TO_VALUE(__ASC_LINE_UP_L, MAKE_WIDE)
#define W_LINE_VT MACRO_TO_VALUE(__ASC_LINE_VT, MAKE_WIDE)
#define W_LINE_HT MACRO_TO_VALUE(__ASC_LINE_HT, MAKE_WIDE)
#define W_LINE_3W_R MACRO_TO_VALUE(__ASC_LINE_3W_R, MAKE_WIDE)
#define W_LINE_3W_L MACRO_TO_VALUE(__ASC_LINE_3W_L, MAKE_WIDE)
#define W_LINE_3W_U MACRO_TO_VALUE(__ASC_LINE_3W_U, MAKE_WIDE)
#define W_LINE_3W_D MACRO_TO_VALUE(__ASC_LINE_3W_D, MAKE_WIDE)
#define W_LINE_4W MACRO_TO_VALUE(__ASC_LINE_4W, MAKE_WIDE)

#define W_BOX_DN_R MACRO_TO_VALUE(__ASC_BOX_DN_R, MAKE_WIDE)
#define W_BOX_UP_R MACRO_TO_VALUE(__ASC_BOX_UP_R, MAKE_WIDE)
#define W_BOX_DN_L MACRO_TO_VALUE(__ASC_BOX_DN_L, MAKE_WIDE)
#define W_BOX_UP_L MACRO_TO_VALUE(__ASC_BOX_UP_L, MAKE_WIDE)
#define W_BOX_VT MACRO_TO_VALUE(__ASC_BOX_VT, MAKE_WIDE)
#define W_BOX_HT MACRO_TO_VALUE(__ASC_BOX_HT, MAKE_WIDE)
#define W_BOX_3W_R MACRO_TO_VALUE(__ASC_BOX_3W_R, MAKE_WIDE)
#define W_BOX_3W_L MACRO_TO_VALUE(__ASC_BOX_3W_L, MAKE_WIDE)
#define W_BOX_3W_U MACRO_TO_VALUE(__ASC_BOX_3W_U, MAKE_WIDE)
#define W_BOX_3W_D MACRO_TO_VALUE(__ASC_BOX_3W_D, MAKE_WIDE)
#define W_BOX_4W MACRO_TO_VALUE(__ASC_BOX_4W, MAKE_WIDE)

#define W_VBOX_DN_R MACRO_TO_VALUE(__ASC_VBOX_DN_R, MAKE_WIDE)
#define W_VBOX_UP_R MACRO_TO_VALUE(__ASC_VBOX_UP_R, MAKE_WIDE)
#define W_VBOX_DN_L MACRO_TO_VALUE(__ASC_VBOX_DN_L, MAKE_WIDE)
#define W_VBOX_UP_L MACRO_TO_VALUE(__ASC_VBOX_UP_L, MAKE_WIDE)
#define W_VBOX_VT MACRO_TO_VALUE(__ASC_VBOX_VT, MAKE_WIDE)
#define W_VBOX_HT MACRO_TO_VALUE(__ASC_VBOX_HT, MAKE_WIDE)
#define W_VBOX_3W_R MACRO_TO_VALUE(__ASC_VBOX_3W_R, MAKE_WIDE)
#define W_VBOX_3W_L MACRO_TO_VALUE(__ASC_VBOX_3W_L, MAKE_WIDE)
#define W_VBOX_3W_U MACRO_TO_VALUE(__ASC_VBOX_3W_U, MAKE_WIDE)
#define W_VBOX_3W_D MACRO_TO_VALUE(__ASC_VBOX_3W_D, MAKE_WIDE)
#define W_VBOX_4W MACRO_TO_VALUE(__ASC_VBOX_4W, MAKE_WIDE)

#define W_HBOX_DN_R MACRO_TO_VALUE(__ASC_HBOX_DN_R, MAKE_WIDE)
#define W_HBOX_UP_R MACRO_TO_VALUE(__ASC_HBOX_UP_R, MAKE_WIDE)
#define W_HBOX_DN_L MACRO_TO_VALUE(__ASC_HBOX_DN_L, MAKE_WIDE)
#define W_HBOX_UP_L MACRO_TO_VALUE(__ASC_HBOX_UP_L, MAKE_WIDE)
#define W_HBOX_VT MACRO_TO_VALUE(__ASC_HBOX_VT, MAKE_WIDE)
#define W_HBOX_HT MACRO_TO_VALUE(__ASC_HBOX_HT, MAKE_WIDE)
#define W_HBOX_3W_R MACRO_TO_VALUE(__ASC_HBOX_3W_R, MAKE_WIDE)
#define W_HBOX_3W_L MACRO_TO_VALUE(__ASC_HBOX_3W_L, MAKE_WIDE)
#define W_HBOX_3W_U MACRO_TO_VALUE(__ASC_HBOX_3W_U, MAKE_WIDE)
#define W_HBOX_3W_D MACRO_TO_VALUE(__ASC_HBOX_3W_D, MAKE_WIDE)
#define W_HBOX_4W MACRO_TO_VALUE(__ASC_HBOX_4W, MAKE_WIDE)
#define W_BLOCK MACRO_TO_VALUE(__ASC_BLOCK, MAKE_WIDE)

#define W_BLOCK_R MACRO_TO_VALUE(__ASC_BLOCK_R, MAKE_WIDE)
#define W_BLOCK_L MACRO_TO_VALUE(__ASC_BLOCK_L, MAKE_WIDE)
#define W_BLOCK_U MACRO_TO_VALUE(__ASC_BLOCK_U, MAKE_WIDE)
#define W_BLOCK_D MACRO_TO_VALUE(__ASC_BLOCK_D, MAKE_WIDE)
#define W_BLOCK_25 MACRO_TO_VALUE(__ASC_BLOCK_25, MAKE_WIDE)
#define W_BLOCK_50 MACRO_TO_VALUE(__ASC_BLOCK_50, MAKE_WIDE)
#define W_BLOCK_75 MACRO_TO_VALUE(__ASC_BLOCK_75, MAKE_WIDE)


// UTF-8 BOX DRAWINGS
#define U8_LINE_DN_R MACRO_TO_VALUE(__ASC_LINE_DN_R, MAKE_U8)
#define U8_LINE_UP_R MACRO_TO_VALUE(__ASC_LINE_UP_R, MAKE_U8)
#define U8_LINE_DN_L MACRO_TO_VALUE(__ASC_LINE_DN_L, MAKE_U8)
#define U8_LINE_UP_L MACRO_TO_VALUE(__ASC_LINE_UP_L, MAKE_U8)
#define U8_LINE_VT MACRO_TO_VALUE(__ASC_LINE_VT, MAKE_U8)
#define U8_LINE_HT MACRO_TO_VALUE(__ASC_LINE_HT, MAKE_U8)
#define U8_LINE_3W_R MACRO_TO_VALUE(__ASC_LINE_3W_R, MAKE_U8)
#define U8_LINE_3W_L MACRO_TO_VALUE(__ASC_LINE_3W_L, MAKE_U8)
#define U8_LINE_3W_U MACRO_TO_VALUE(__ASC_LINE_3W_U, MAKE_U8)
#define U8_LINE_3W_D MACRO_TO_VALUE(__ASC_LINE_3W_D, MAKE_U8)
#define U8_LINE_4W MACRO_TO_VALUE(__ASC_LINE_4W, MAKE_U8)

#define U8_BOX_DN_R MACRO_TO_VALUE(__ASC_BOX_DN_R, MAKE_U8)
#define U8_BOX_UP_R MACRO_TO_VALUE(__ASC_BOX_UP_R, MAKE_U8)
#define U8_BOX_DN_L MACRO_TO_VALUE(__ASC_BOX_DN_L, MAKE_U8)
#define U8_BOX_UP_L MACRO_TO_VALUE(__ASC_BOX_UP_L, MAKE_U8)
#define U8_BOX_VT MACRO_TO_VALUE(__ASC_BOX_VT, MAKE_U8)
#define U8_BOX_HT MACRO_TO_VALUE(__ASC_BOX_HT, MAKE_U8)
#define U8_BOX_3W_R MACRO_TO_VALUE(__ASC_BOX_3W_R, MAKE_U8)
#define U8_BOX_3W_L MACRO_TO_VALUE(__ASC_BOX_3W_L, MAKE_U8)
#define U8_BOX_3W_U MACRO_TO_VALUE(__ASC_BOX_3W_U, MAKE_U8)
#define U8_BOX_3W_D MACRO_TO_VALUE(__ASC_BOX_3W_D, MAKE_U8)
#define U8_BOX_4W MACRO_TO_VALUE(__ASC_BOX_4W, MAKE_U8)

#define U8_VBOX_DN_R MACRO_TO_VALUE(__ASC_VBOX_DN_R, MAKE_U8)
#define U8_VBOX_UP_R MACRO_TO_VALUE(__ASC_VBOX_UP_R, MAKE_U8)
#define U8_VBOX_DN_L MACRO_TO_VALUE(__ASC_VBOX_DN_L, MAKE_U8)
#define U8_VBOX_UP_L MACRO_TO_VALUE(__ASC_VBOX_UP_L, MAKE_U8)
#define U8_VBOX_VT MACRO_TO_VALUE(__ASC_VBOX_VT, MAKE_U8)
#define U8_VBOX_HT MACRO_TO_VALUE(__ASC_VBOX_HT, MAKE_U8)
#define U8_VBOX_3W_R MACRO_TO_VALUE(__ASC_VBOX_3W_R, MAKE_U8)
#define U8_VBOX_3W_L MACRO_TO_VALUE(__ASC_VBOX_3W_L, MAKE_U8)
#define U8_VBOX_3W_U MACRO_TO_VALUE(__ASC_VBOX_3W_U, MAKE_U8)
#define U8_VBOX_3W_D MACRO_TO_VALUE(__ASC_VBOX_3W_D, MAKE_U8)
#define U8_VBOX_4W MACRO_TO_VALUE(__ASC_VBOX_4W, MAKE_U8)

#define U8_HBOX_DN_R MACRO_TO_VALUE(__ASC_HBOX_DN_R, MAKE_U8)
#define U8_HBOX_UP_R MACRO_TO_VALUE(__ASC_HBOX_UP_R, MAKE_U8)
#define U8_HBOX_DN_L MACRO_TO_VALUE(__ASC_HBOX_DN_L, MAKE_U8)
#define U8_HBOX_UP_L MACRO_TO_VALUE(__ASC_HBOX_UP_L, MAKE_U8)
#define U8_HBOX_VT MACRO_TO_VALUE(__ASC_HBOX_VT, MAKE_U8)
#define U8_HBOX_HT MACRO_TO_VALUE(__ASC_HBOX_HT, MAKE_U8)
#define U8_HBOX_3W_R MACRO_TO_VALUE(__ASC_HBOX_3W_R, MAKE_U8)
#define U8_HBOX_3W_L MACRO_TO_VALUE(__ASC_HBOX_3W_L, MAKE_U8)
#define U8_HBOX_3W_U MACRO_TO_VALUE(__ASC_HBOX_3W_U, MAKE_U8)
#define U8_HBOX_3W_D MACRO_TO_VALUE(__ASC_HBOX_3W_D, MAKE_U8)
#define U8_HBOX_4W MACRO_TO_VALUE(__ASC_HBOX_4W, MAKE_U8)

#define U8_BLOCK MACRO_TO_VALUE(__ASC_BLOCK, MAKE_U8)
#define U8_BLOCK_R MACRO_TO_VALUE(__ASC_BLOCK_R, MAKE_U8)
#define U8_BLOCK_L MACRO_TO_VALUE(__ASC_BLOCK_L, MAKE_U8)
#define U8_BLOCK_U MACRO_TO_VALUE(__ASC_BLOCK_U, MAKE_U8)
#define U8_BLOCK_D MACRO_TO_VALUE(__ASC_BLOCK_D, MAKE_U8)
#define U8_BLOCK_25 MACRO_TO_VALUE(__ASC_BLOCK_25, MAKE_U8)
#define U8_BLOCK_50 MACRO_TO_VALUE(__ASC_BLOCK_50, MAKE_U8)
#define U8_BLOCK_75 MACRO_TO_VALUE(__ASC_BLOCK_75, MAKE_U8)