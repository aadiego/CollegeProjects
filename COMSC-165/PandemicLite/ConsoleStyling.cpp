#include "ConsoleStyling.h"

// Global variables and constants
HWND console = GetConsoleWindow();							// Stores the console
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);			// Stores the console handle
CONSOLE_SCREEN_BUFFER_INFO csbi;							// Stores the console screen buffer information.

// *******************************************************************************************
// **     Function: SetupConsole															**
// **   Parameters: N/A																		**
// **       Return: void																	**
// **  Description: Sets the Windows Command Line console's title, size, disables the		**
// **				maximize button, and sets the default font color.						**
// *******************************************************************************************
void SetupConsole()
{
	// Set the console title and clear the screen output for initial draw.
	SetConsoleTitle("Pandemic (Lite)");
	ClearScreen();

	// Get the current console dimensions and position then modify the dimensions to be the game size (1024x768)
	RECT dimensions;
	GetWindowRect(console, &dimensions);
	MoveWindow(console, dimensions.left, dimensions.top, 1024, 768, true);

	// Get the console window to disable the maximize option
	DWORD style = GetWindowLong(console, GWL_STYLE);
	style &= ~WS_MAXIMIZEBOX;
	SetWindowLong(console, GWL_STYLE, style);
	SetWindowPos(console, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_FRAMECHANGED);

	// Set the default font color.
	ChangeFontColor(DEFAULT);
}

// *******************************************************************************************
// **     Function: ClearScreen																**
// **   Parameters: N/A																		**
// **       Return: void																	**
// **  Description: Clears the console output.												**
// *******************************************************************************************
void ClearScreen()
{
	system("cls");
}

// *******************************************************************************************
// **     Function: PrintLogo																**
// **   Parameters: bool IncludeSubText	(optional) [Default = true]							**
// **       Return: void																	**
// **  Description: Prints the logo center on the screen.									**
// *******************************************************************************************
void PrintLogo(bool IncludeSubText)
{
	// Get current console screen buffer information (used to center the logo)
	GetConsoleScreenBufferInfo(hStdOut, &csbi);

	// Constant variables holding the characters per row and string with a char array of the logo.
	const int charsPerRow = 63;
	string PandemicTitle = { (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)32 , (char)32 , (char)219 , (char)219 , (char)219 , (char)32 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)32 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)32 , (char)32 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)32 , (char)219 , (char)219 , (char)219 , (char)32 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)219 , (char)32 , (char)219 , (char)219 , (char)32 , (char)32 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , '\n' ,
		(char)219 , (char)219 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)32 , (char)219 , (char)219 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)32 , (char)219 , (char)219 , (char)219 , (char)219 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)32 , (char)219 , (char)219 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)32 , (char)219 , (char)219 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)219 , (char)219 , (char)32 , (char)32 , (char)219 , (char)219 , (char)219 , (char)219 , (char)32 , (char)219 , (char)219 , (char)32 , (char)219 , (char)219 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , '\n' ,
		(char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)32 , (char)32 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)32 , (char)219 , (char)219 , (char)32 , (char)219 , (char)219 , (char)32 , (char)32 , (char)219 , (char)219 , (char)32 , (char)219 , (char)219 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)32 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)32 , (char)219 , (char)219 , (char)219 , (char)219 , (char)32 , (char)219 , (char)219 , (char)32 , (char)219 , (char)219 , (char)32 , (char)219 , (char)219 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , '\n' ,
		(char)219 , (char)219 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)32 , (char)219 , (char)219 , (char)32 , (char)32 , (char)219 , (char)219 , (char)32 , (char)219 , (char)219 , (char)32 , (char)219 , (char)219 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)32 , (char)219 , (char)219 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)32 , (char)32 , (char)219 , (char)219 , (char)32 , (char)32 , (char)219 , (char)219 , (char)32 , (char)219 , (char)219 , (char)32 , (char)219 , (char)219 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , '\n' ,
		(char)219 , (char)219 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)32 , (char)219 , (char)219 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)219 , (char)219 , (char)32 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)32 , (char)32 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)32 , (char)219 , (char)219 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , (char)32 , (char)219 , (char)219 , (char)32 , (char)219 , (char)219 , (char)32 , (char)32 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 , (char)219 };

	// Check if the subtext should be included. If so, append it to the title.
	if (IncludeSubText)
	{
		PandemicTitle += "\n\n     A lite version of the cooperative board game designed\n           Matt Leacock and published by Z-Man Games";
	}

	// Calculates the middle of the screen based on the console size and the characters per row.
	int x = (csbi.dwSize.X - charsPerRow) / 2;

	// Call the PrintAtScreenPosition() function to print the logo at the specified position and color.
	PrintAtScreenPosition(PandemicTitle, x, 3, DEFAULT);

	// Print two extra lines for padding between title and game text.
	cout << endl << endl;
}

// *******************************************************************************************
// **     Function: PrintAtScreenPosition													**
// **   Parameters: string input															**
// **				int x																	**
// **				int y																	**
// **				WORD attributes															**
// **				bool SkipEndingNewLine (optional) [Default = true]						**
// **       Return: void																	**
// **  Description: Prints the input string at the specific position on the screen with		**
// **				the specific coloring attributes.										**
// *******************************************************************************************
void PrintAtScreenPosition(string input, int x, int y, WORD attributes, bool SkipEndingNewLine)
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
		ChangeFontColor(attributes);

		// Print the character to the screen.
		cout << input[x];
	}

	if (SkipEndingNewLine)
	{
		// Print a new line character at the end of output to prevent the next output from continuing on where this ends.
		cout << endl;
	}
}

// *******************************************************************************************
// **     Function: PrintCenterScreenAtPosition												**
// **   Parameters: string input															**
// **				int y																	**
// **				int charsPerRow															**
// **				WORD attributes															**
// **				bool SkipEndingNewLine (optional) [Default = true]						**
// **       Return: void																	**
// **  Description: Prints the input string center on the screen at the specific y			**
// **				coordinate and with the specific coloring attributes.					**
// *******************************************************************************************
void PrintCenterScreenAtPosition(string input, int y, int charsPerRow, WORD attributes, bool SkipEndingNewLine)
{
	// Calculates the middle of the screen based on the console size and the characters per row.
	int x = (csbi.dwSize.X - charsPerRow) / 2;

	PrintAtScreenPosition(input, x, y, attributes, SkipEndingNewLine);
}

// *******************************************************************************************
// **     Function: ChangeConsoleColor														**
// **   Parameters: WORD attributes															**
// **       Return: void																	**
// **  Description: Changes the console's background color.									**
// *******************************************************************************************
void ChangeConsoleColor(WORD attributes)
{
	CONSOLE_SCREEN_BUFFER_INFOEX cbi;
	cbi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	GetConsoleScreenBufferInfoEx(hStdOut, &cbi);
	cbi.wAttributes = attributes;
	SetConsoleScreenBufferInfoEx(hStdOut, &cbi);
}

// *******************************************************************************************
// **     Function: ChangeFontColor															**
// **   Parameters: WORD attributes															**
// **       Return: void																	**
// **  Description: Changes the console's font color.										**
// *******************************************************************************************
void ChangeFontColor(WORD attributes)
{
	SetConsoleTextAttribute(hStdOut, attributes);
}
