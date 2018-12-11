/* Aric Adiego
   Huda Biltagi
   COMSC-110, Section 8001 (Introduction to Programming) Final Project
   Instructor: Michael Wallace
   2018-12-13

   ------------------------------------------------------------------------------
   MIT License
   ------------------------------------------------------------------------------
   Copyright (c) 2018 Aric Adiego and Huda Biltagi

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/

#include "Screen.h"
using namespace std;

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbi;

void ClearScreen()
{
	system("cls");
}

void PrintLogo()
{
	GetConsoleScreenBufferInfo(hStdOut, &csbi);

	const int charsPerRow = 77;
	const string BattleshipTitle = { (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)187 , (char)32 , (char)32 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)187 , (char)32 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)187 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)187 , (char)219 , (char)219 , (char)187 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)187 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)187 , (char)219 , (char)219 , (char)187 , (char)32 , (char)32 , (char)219 , (char)219 , (char)187 , (char)219 , (char)219 , (char)187 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)187 , (char)32 , '\n' ,
			(char)219 , (char)219 , (char)201 , (char)205 , (char)205 , (char)219 , (char)219 , (char)187 , (char)219 , (char)219 , (char)201 , (char)205 , (char)205 , (char)219 , (char)219 , (char)187 , (char)200 , (char)205 , (char)205 , (char)219 , (char)219 , (char)201 , (char)205 , (char)205 , (char)188 , (char)200 , (char)205 , (char)205 , (char)219 , (char)219 , (char)201 , (char)205 , (char)205 , (char)188 , (char)219 , (char)219 , (char)186 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)201 , (char)205 , (char)205 , (char)205 , (char)205 , (char)188 , (char)219 , (char)219 , (char)201 , (char)205 , (char)205 , (char)205 , (char)205 , (char)188 , (char)219 , (char)219 , (char)186 , (char)32 , (char)32 , (char)219 , (char)219 , (char)186 , (char)219 , (char)219 , (char)186 , (char)219 , (char)219 , (char)201 , (char)205 , (char)205 , (char)219 , (char)219 , (char)187 , '\n' ,
			(char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)201 , (char)188 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)186 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)186 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)186 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)186 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)187 , (char)32 , (char)32 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)187 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)186 , (char)219 , (char)219 , (char)186 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)201 , (char)188 , '\n' ,
			(char)219 , (char)219 , (char)201 , (char)205 , (char)205 , (char)219 , (char)219 , (char)187 , (char)219 , (char)219 , (char)201 , (char)205 , (char)205 , (char)219 , (char)219 , (char)186 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)186 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)186 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)186 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)201 , (char)205 , (char)205 , (char)188 , (char)32 , (char)32 , (char)200 , (char)205 , (char)205 , (char)205 , (char)205 , (char)219 , (char)219 , (char)186 , (char)219 , (char)219 , (char)201 , (char)205 , (char)205 , (char)219 , (char)219 , (char)186 , (char)219 , (char)219 , (char)186 , (char)219 , (char)219 , (char)201 , (char)205 , (char)205 , (char)205 , (char)188 , (char)32 , '\n' ,
			(char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)201 , (char)188 , (char)219 , (char)219 , (char)186 , (char)32 , (char)32 , (char)219 , (char)219 , (char)186 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)186 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)186 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)187 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)187 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)186 , (char)219 , (char)219 , (char)186 , (char)32 , (char)32 , (char)219 , (char)219 , (char)186 , (char)219 , (char)219 , (char)186 , (char)219 , (char)219 , (char)186 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , '\n' ,
			(char)200 , (char)205 , (char)205 , (char)205 , (char)205 , (char)205 , (char)188 , (char)32 , (char)200 , (char)205 , (char)188 , (char)32 , (char)32 , (char)200 , (char)205 , (char)188 , (char)32 , (char)32 , (char)32 , (char)200 , (char)205 , (char)188 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , (char)200 , (char)205 , (char)188 , (char)32 , (char)32 , (char)32 , (char)200 , (char)205 , (char)205 , (char)205 , (char)205 , (char)205 , (char)205 , (char)188 , (char)200 , (char)205 , (char)205 , (char)205 , (char)205 , (char)205 , (char)205 , (char)188 , (char)200 , (char)205 , (char)205 , (char)205 , (char)205 , (char)205 , (char)205 , (char)188 , (char)200 , (char)205 , (char)188 , (char)32 , (char)32 , (char)200 , (char)205 , (char)188 , (char)200 , (char)205 , (char)188 , (char)200 , (char)205 , (char)188 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 };

	int x = (csbi.dwSize.X - charsPerRow) / 2;
	PrintAtScreenPosition(BattleshipTitle, x, 3, DEFAULT);
	cout << endl << endl;
}

void PrintAtScreenPosition(string input, int x, int y, WORD attributes)
{
	COORD ScreenPosition;
	ScreenPosition.X = (x < 0) ? csbi.dwSize.X + x : x;
	ScreenPosition.Y = (y < 0) ? csbi.dwSize.Y + y : y;
	SetConsoleCursorPosition(hStdOut, ScreenPosition);
	for (int x = 0; x < input.length(); x++)
	{
		if (input[x] == '\n')
		{
			ScreenPosition.Y += 1;
			SetConsoleCursorPosition(hStdOut, ScreenPosition);
			continue;
		}
		change_font_color(attributes);
		cout << input[x];
	}
	cout << endl;
}

void change_console_color(WORD attributes)
{
	CONSOLE_SCREEN_BUFFER_INFOEX cbi;
	cbi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	GetConsoleScreenBufferInfoEx(hStdOut, &cbi);
	cbi.wAttributes = attributes;
	SetConsoleScreenBufferInfoEx(hStdOut, &cbi);
}

void change_font_color(WORD attributes)
{
	SetConsoleTextAttribute(hStdOut, attributes);
}