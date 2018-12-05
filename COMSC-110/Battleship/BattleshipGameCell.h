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

#ifndef BattleshipGameCell_H
#define BattleshipGameCell_H
#include <string>
using namespace std;

enum Name { CARRIER, BATTLESHIP, CRUISER, SUBMARINE, DESTROYER };	// Enum of the names of the ships
enum Orientation { VERTICAL, HORIZONTAL };							// Enum of the orientation of the ship on the game board
enum Section { TOPLEFTCAP, MIDDLE, BOTTOMRIGHTCAP };				// Enum of the section of the ship for UI drawing

struct Ship															// Store information about the ship
{
	Name name;														// Stores the name of the ship
	Orientation orientation;										// Stores the ship orientation on the game board
	Section section;												// Stores the section of the ship for UI drawing
};

struct BattleshipGameCell
{
	bool isHit;														// Was the space hit by the opponent?
	Ship *shipInfo;													// Store information about the ship
};

string ShipNameEnumToString(Name);									// Converts the Name enumerator to string for reporting to the game UI.

#endif