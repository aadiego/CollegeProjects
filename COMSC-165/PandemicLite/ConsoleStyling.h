#pragma once
#ifndef CONSOLESTYLING_H
#define CONSOLESTYLING_H

#include <conio.h>
#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_BACKSPACE 8
#define KEY_ESCAPE 27

#define BLUE_DISEASE (BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY)
#define YELLOW_DISEASE (BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY)
#define PURPLE_DISEASE (BACKGROUND_BLUE | BACKGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY)
#define RED_DISEASE (BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY)

#define DEFAULT (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY)
#define BLUE_TEXT (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define YELLOW_TEXT (FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY)
#define PURPLE_TEXT (FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY)
#define RED_TEXT (FOREGROUND_RED | FOREGROUND_INTENSITY)

#define SELECTED_TEXT (BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY)

void SetupConsole();
void ClearScreen();
void PrintLogo(bool = true);
void PrintAtScreenPosition(string, int, int, WORD);
void PrintCenterScreenAtPosition(string, int, int, WORD);
void ChangeConsoleColor(WORD);
void ChangFontColor(WORD);

#endif