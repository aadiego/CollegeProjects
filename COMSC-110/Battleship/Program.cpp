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

int main()
{
	SetConsoleTitle("Battleship");

	//Display menu to the user, with instructions to pick one item from the list by hitting the
	//appropriate number on their keyboard.
	const int  MAX_INPUT = 3, MIN_INPUT = 1;
	int userselection;

	cout << "Please select 1, 2 or 3 from the following menu:\n\n";
	cout << "1. Play Game!\n";
	cout << "2. How To Play\n";
	cout << "3. Exit Game\n\n";
	cout << "Your selection: ";
	cin >> userselection;

	// validate user input with while loop
	while (userselection < 1 || userselection > 3)
	{
		cout << "\n\nInvalid Input!\n";
		cout << "Enter only a number listed in the above menu.\n";
		cin >> userselection;
	}

	// print out corresponding statement for each item using switch statement 
	switch (userselection)
	{
	case 1:
		SetupGame();

		break;
	case 2:
		cout << "Game Objective:\n -Find and Sink all" << NUMBEROFSHIPS << " ships hidden on the board\n\n";
		cout << "Rules:\n1-Fire shots at the board by calling out grid coordinates location. Ex: A 1 \n";
		cout << "\n2-A hit indicates that a ship has been sunk,\nwhile a miss indicates that the shot missed and there is no ship \nat that coordinate.\n";
		cout << "\n3-Input another coordinate and try to find and sink all the ships!\n";
		cout << "\nHAPPY HUNTING!!\n\n";
		/////////select 1 to return to the main menu//////////??????????
		break;
	case 3:
		cout << "You have exited the game!";
		/////////select 1 to return to the main menu//////////??????????
		break;

	}

	return 0;
}