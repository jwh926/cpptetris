#ifndef __TETRIS_HELPER_H__
#define __TETRIS_HELPER_H__

#include <Windows.h>
#include <cstdio>

KEY_EVENT_RECORD krec;
void putStringOnPosition(int x, int y, const char* content) {
	// Move Cursor
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	// Print string
	printf("%s", content);
}

void showConsoleCursor(bool showFlag) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void drawPosition(int x, int y, bool filled) {
	putStringOnPosition(x * 2, y, filled ? "бс" : "бр");
}

bool keyState(char c) {
	short ret;
	switch (c) {
	case 'a': ret = GetKeyState(0x41); break;
	case 'd': ret = GetKeyState(0x44); break;
	case 's': ret = GetKeyState(0x53); break;
	case 'w': ret = GetKeyState(0x57); break;
	default: return false;
	}
	return ret != 0 && ret != 1;
}

#endif // !__TETRIS_HELPER_H__