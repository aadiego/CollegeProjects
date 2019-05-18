#include "ConsoleStyling.h"

HWND console = GetConsoleWindow();							// Stores the console
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);			// Stores the console handle
CONSOLE_SCREEN_BUFFER_INFO csbi;							// Stores the console screen buffer information.

void SetupConsole()
{
	SetConsoleTitle("Pandemic (Lite)");

	RECT dimensions;
	GetWindowRect(console, &dimensions);
	MoveWindow(console, dimensions.left, dimensions.top, 1024, 768, true);

	change_font_color(DEFAULT);
}

void ClearScreen()
{
	system("cls");
}

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