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

#ifndef Game_H
#define Game_H
#include <conio.h>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include "BattleshipGameCell.h"
#include "ComputerPlayer.h"
#include "Screen.h"
using namespace std;

const int GRIDROWS = 10,											// Number of ROWS in the BattleshipGameGrid array
		  GRIDCOLUMNS = 10,											// Number of COLUMNS in the BattleshipGameGrid array
		  NUMBEROFSHIPS = 5,										// Number game pieces (ships)
		  CARRIERSIZE = 5,											// Size of the CARRIER game piece
		  BATTLESHIPSIZE = 4,										// Size of the BATTLESHIP game piece
		  CRUISERSIZE = 3,											// Size of the CRUISER game piece
		  SUBMARINESIZE = 3,										// Size of the SUBMARINE game piece
		  DESTROYERSIZE = 2;										// Size of the DESTROYER game piece

enum AttackStatus { UNKNOWN, ALREADYATTACKED, MISS, HIT, SUNK };	// Enum for reporting the status of the attack				
enum Player { HUMAN, COMPUTER };									// Enum for the player type

struct Coordinates													// Stores the X,Y position of the attack (zero start)
{
	int row;														// Stores the X (horizontal) coordinate value
	int col;														// Stores the Y (vertical) coordinate value
};

void SetupGame();
void RandomizeShipLocations(BattleshipGameCell (&)[GRIDROWS][GRIDCOLUMNS]);
int GetShipLength(Name);
bool IsInGridBoundary(Coordinates, Direction, int = 1);
bool IsInGridBoundary(Coordinates, Direction, Direction &, int = 1);
bool IsValidShipPlacement(BattleshipGameCell(&)[GRIDROWS][GRIDCOLUMNS], Coordinates, Direction, int);
void StepDirection(Coordinates &, Direction);
void PlayGame();
void DrawPlayerBoards(bool);
AttackStatus LaunchAttack(BattleshipGameCell(&)[GRIDROWS][GRIDCOLUMNS], string);
AttackStatus LaunchAttack(BattleshipGameCell(&)[GRIDROWS][GRIDCOLUMNS], string, Coordinates &);
bool SetTarget(string, Coordinates &);
bool CheckTarget(Player, Coordinates);
bool WasShipSunk(BattleshipGameCell(&)[GRIDROWS][GRIDCOLUMNS], Name, int &);
int& NumberOfShipsRemaining();
void Logger(string);
void Dispose();
void Dispose(BattleshipGameCell(&)[GRIDROWS][GRIDCOLUMNS]);

#endif