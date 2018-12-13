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

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);			// Stores the console handle
CONSOLE_SCREEN_BUFFER_INFO csbi;							// Stores the console screen buffer information.

// ------------------------------------------------------------------------------
// Clears the entire screen.
// ------------------------------------------------------------------------------
void ClearScreen()
{
	// Call the system function "cls"
	system("cls");
}

// ------------------------------------------------------------------------------
// Prints the Battleship logo.
// ------------------------------------------------------------------------------
void PrintLogo()
{
	// Get current console screen buffer information (used to center the logo)
	GetConsoleScreenBufferInfo(hStdOut, &csbi);

	// Constant variables holding the characters per row and string with a char array of the logo.
	const int charsPerRow = 77;
	const string BattleshipTitle = { (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)187 , (char)32 , (char)32 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)187 , (char)32 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)187 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)187 , (char)219 , (char)219 , (char)187 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)187 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)187 , (char)219 , (char)219 , (char)187 , (char)32 , (char)32 , (char)219 , (char)219 , (char)187 , (char)219 , (char)219 , (char)187 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)187 , (char)32 , '\n' ,
			(char)219 , (char)219 , (char)201 , (char)205 , (char)205 , (char)219 , (char)219 , (char)187 , (char)219 , (char)219 , (char)201 , (char)205 , (char)205 , (char)219 , (char)219 , (char)187 , (char)200 , (char)205 , (char)205 , (char)219 , (char)219 , (char)201 , (char)205 , (char)205 , (char)188 , (char)200 , (char)205 , (char)205 , (char)219 , (char)219 , (char)201 , (char)205 , (char)205 , (char)188 , (char)219 , (char)219 , (char)186 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)201 , (char)205 , (char)205 , (char)205 , (char)205 , (char)188 , (char)219 , (char)219 , (char)201 , (char)205 , (char)205 , (char)205 , (char)205 , (char)188 , (char)219 , (char)219 , (char)186 , (char)32 , (char)32 , (char)219 , (char)219 , (char)186 , (char)219 , (char)219 , (char)186 , (char)219 , (char)219 , (char)201 , (char)205 , (char)205 , (char)219 , (char)219 , (char)187 , '\n' ,
			(char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)201 , (char)188 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)186 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)186 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)186 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)186 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)187 , (char)32 , (char)32 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)187 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)186 , (char)219 , (char)219 , (char)186 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)201 , (char)188 , '\n' ,
			(char)219 , (char)219 , (char)201 , (char)205 , (char)205 , (char)219 , (char)219 , (char)187 , (char)219 , (char)219 , (char)201 , (char)205 , (char)205 , (char)219 , (char)219 , (char)186 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)186 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)186 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)186 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)201 , (char)205 , (char)205 , (char)188 , (char)32 , (char)32 , (char)200 , (char)205 , (char)205 , (char)205 , (char)205 , (char)219 , (char)219 , (char)186 , (char)219 , (char)219 , (char)201 , (char)205 , (char)205 , (char)219 , (char)219 , (char)186 , (char)219 , (char)219 , (char)186 , (char)219 , (char)219 , (char)201 , (char)205 , (char)205 , (char)205 , (char)188 , (char)32 , '\n' ,
			(char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)201 , (char)188 , (char)219 , (char)219 , (char)186 , (char)32 , (char)32 , (char)219 , (char)219 , (char)186 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)186 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)186 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)187 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)187 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)186 , (char)219 , (char)219 , (char)186 , (char)32 , (char)32 , (char)219 , (char)219 , (char)186 , (char)219 , (char)219 , (char)186 , (char)219 , (char)219 , (char)186 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , '\n' ,
			(char)200 , (char)205 , (char)205 , (char)205 , (char)205 , (char)205 , (char)188 , (char)32 , (char)200 , (char)205 , (char)188 , (char)32 , (char)32 , (char)200 , (char)205 , (char)188 , (char)32 , (char)32 , (char)32 , (char)200 , (char)205 , (char)188 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , (char)200 , (char)205 , (char)188 , (char)32 , (char)32 , (char)32 , (char)200 , (char)205 , (char)205 , (char)205 , (char)205 , (char)205 , (char)205 , (char)188 , (char)200 , (char)205 , (char)205 , (char)205 , (char)205 , (char)205 , (char)205 , (char)188 , (char)200 , (char)205 , (char)205 , (char)205 , (char)205 , (char)205 , (char)205 , (char)188 , (char)200 , (char)205 , (char)188 , (char)32 , (char)32 , (char)200 , (char)205 , (char)188 , (char)200 , (char)205 , (char)188 , (char)200 , (char)205 , (char)188 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 };

	// Calculates the middle of the screen based on the console size and the charaters per row.
	int x = (csbi.dwSize.X - charsPerRow) / 2;

	// Call the PrintAtScreenPosition() function to print the logo at the specified postion and color.
	PrintAtScreenPosition(BattleshipTitle, x, 3, DEFAULT);

	// Print two extra lines for padding between player boards and game text.
	cout << endl << endl;
}

// ------------------------------------------------------------------------------
// Prints the a styled string at the specified position.
// ------------------------------------------------------------------------------
void PrintAtScreenPosition(string input, int x, int y, WORD attributes)
{
	// Get current console screen buffer information
	GetConsoleScreenBufferInfo(hStdOut, &csbi);

	// Coordinate position where the string will be printed.
	COORD ScreenPosition;
	ScreenPosition.X = (x < 0) ? csbi.dwSize.X + x : x;		// If the number is negative count from the right side of the screen.
	ScreenPosition.Y = (y < 0) ? csbi.dwSize.Y + y : y;		// If the number is negative count from the right side of the screen.

	// Move the cursor to the position on the screen.
	SetConsoleCursorPosition(hStdOut, ScreenPosition);

	// Loop through each character in the string.
	for (int x = 0; x < input.length(); x++)
	{
		// If a new line character is encountered, reposition the cursor to the one below the original starting location and continue.
		if (input[x] == '\n')
		{
			ScreenPosition.Y += 1;
			SetConsoleCursorPosition(hStdOut, ScreenPosition);
			continue;
		}
		// Set the output font style
		change_font_color(attributes);

		// Print the character to the screen.
		cout << input[x];
	}

	// Print a new line character at the end of output to prevent the next output from continuing on where this ends.
	cout << endl;
}

// ------------------------------------------------------------------------------
// Changes the color of the console background.
// ------------------------------------------------------------------------------
void change_console_color(WORD attributes)
{
	CONSOLE_SCREEN_BUFFER_INFOEX cbi;
	cbi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	GetConsoleScreenBufferInfoEx(hStdOut, &cbi);
	cbi.wAttributes = attributes;
	SetConsoleScreenBufferInfoEx(hStdOut, &cbi);
}

// ------------------------------------------------------------------------------
// Changes the style of the font and it's background.
// ------------------------------------------------------------------------------
void change_font_color(WORD attributes)
{
	SetConsoleTextAttribute(hStdOut, attributes);
}