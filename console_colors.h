#ifndef CONSOLECOLORS_H_
#define CONSOLECOLORS_H_

#define FG_BLACK 0x0
#define FG_BLUE 0x1
#define FG_GREEN 0x2
#define FG_AQUA 0x3
#define FG_RED 0x4
#define FG_PURPLE 0x5
#define FG_YELLOW 0x6
#define FG_WHITE 0x7
#define FG_GREY 0x8
#define FG_LIGHT_BLUE 0x9
#define FG_LIGHT_GREEN 0xa
#define FG_LIGHT_AQUA 0xb
#define FG_LIGHT_RED 0xc
#define FG_LIGHT_PURPLE 0xd
#define FG_LIGHT_YELLOW 0xe
#define FG_BRIGHT_WHITE 0xf

#define BG_BLACK (0x0 * 16)
#define BG_BLUE (0x1 * 16)
#define BG_GREEN (0x2 * 16)
#define BG_AQUA (0x3 * 16)
#define BG_RED (0x4 * 16)
#define BG_PURPLE (0x5 * 16)
#define BG_YELLOW (0x6 * 16)
#define BG_WHITE (0x7 * 16)
#define BG_GREY (0x8 * 16)
#define BG_LIGHT_BLUE (0x9 * 16)
#define BG_LIGHT_GREEN (0xa * 16)
#define BG_LIGHT_AQUA (0xb * 16)
#define BG_LIGHT_RED (0xc * 16)
#define BG_LIGHT_PURPLE (0xd * 16)
#define BG_LIGHT_YELLOW (0xe * 16)
#define BG_BRIGHT_WHITE (0xf * 16)

#define FG_DEFAULT FG_WHITE
#define BG_DEFAULT BG_BLACK

#define CONSOLE_DEFAULT (FG_DEFAULT|BG_DEFAULT)

#if defined(_WIN32)

#include <windows.h>

void ccset(unsigned char color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

#else //unknown platform

#pragma message("This module has not been implemented for this platform/compiler")

void ccset(unsigned char) {}; //dummy

#endif //platform

#endif //CONSOLECOLORS_H_
