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

#include "Game.h"
using namespace std;

// ------------------------------------------------------------------------------
// The entry point of the program.
// ------------------------------------------------------------------------------
int main()
{
	// Set the Command Prompt Title Bar, clear screen of any previous text, change background color to blue, and font color to white.
	SetConsoleTitle("Battleship");
	change_console_color(BACKGROUND_BLUE);
	change_font_color(DEFAULT);

	// Constants and menu choices
	const int PLAY_GAME = 1, HOW_TO_PLAY = 2, EXIT_GAME = 3;

	// User selection variable declaration.
	int userselection;

	do
	{
		ClearScreen();
		PrintLogo();

		//Display menu to the user, with instructions to pick one item from the list by hitting the
		//appropriate number on their keyboard.
		cout << "Please select 1, 2 or 3 from the following menu:\n\n";
		cout << "1. Play Game!\n";
		cout << "2. How To Play\n";
		cout << "3. Exit Game\n\n";
		cout << "Your selection: ";

		// Prompt user for selection and store in selection variable
		cin >> userselection;

		// validate user input with while loop
		while (userselection < PLAY_GAME || userselection > EXIT_GAME)
		{
			cout << "\n\nInvalid Input!\n";
			cout << "Enter only a number listed in the above menu.\n";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin >> userselection;
		}

		if (userselection != EXIT_GAME)
		{
			// print out corresponding statement for each item using switch statement 
			switch (userselection)
			{
				case PLAY_GAME:
					SetupGame();
					break;
				case HOW_TO_PLAY:
					ClearScreen();
					PrintLogo();

					cout << "Game Objective: Find and sink all " << NUMBEROFSHIPS << " ships hidden on the board.\n\n";
					cout << "Rules:\n #1 - Fire shots at the board by calling out grid coordinates location. Ex: A1 \n";
					cout << " #2 - A hit indicates that a ship has been hit and the game will display the ship's remaining hits. Hit all of the ship spaces to sink it. A miss indicates that the shot missed and there is no ship at that coordinate.\n";
					cout << " #3 - Input another coordinate and try to find and sink all the ships!\n";
					cout << "\nHAPPY HUNTING!!\n\n";
					cout << "Please press any key to return to the main menu.";
					_getch();
					break;
			}
		}
	} while (userselection != EXIT_GAME);

	return 0;
}