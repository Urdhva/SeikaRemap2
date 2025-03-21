#pragma once
#include <windows.h>

//header file for forward declerations

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lparam);
void AddMenus(HWND hwnd);
