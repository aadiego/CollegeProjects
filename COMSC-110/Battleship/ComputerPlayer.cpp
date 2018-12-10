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

#include "ComputerPlayer.h"
#include "Game.h"

static Mode CurrentMode = IDLE;
static Direction CurrentDirection;
static Coordinates LastHitCoords;
static bool CurrentAttackSequenceCheckedDirections[4];
static int Iterations = 0;

// ------------------------------------------------------------------------------
// 
// ------------------------------------------------------------------------------
string SimpleAI_SelectTarget()
{
	Coordinates coords = LastHitCoords;
	do
	{
		switch (CurrentMode)
		{
			case IDLE:
				coords.row = rand() % GRIDROWS;
				coords.col = rand() % GRIDCOLUMNS;
				break;
			case HUNTING:
				SelectDirection();
			case ATTACKING:
				StepDirection(coords, CurrentDirection);
				break;
		}
	} while (CheckTarget(HUMAN, coords) || IsInGridBoundary(coords, CurrentDirection, CurrentDirection) == false);

	string rtn;
	rtn += static_cast<char>(coords.col + 65);
	rtn += to_string(coords.row + 1);
	return rtn;
}

// ------------------------------------------------------------------------------
// 
// ------------------------------------------------------------------------------
void SelectDirection()
{	
	bool isValidDirection = false;
	do
	{
		Direction randomDirection = static_cast<Direction>(rand() % 4);
		if (CurrentAttackSequenceCheckedDirections[randomDirection] == false)
		{
			if (IsInGridBoundary(LastHitCoords, randomDirection) == false)
			{
				CurrentAttackSequenceCheckedDirections[randomDirection] = true;
			}
			else
			{
				CurrentAttackSequenceCheckedDirections[randomDirection] = true;
				CurrentDirection = randomDirection;
				isValidDirection = true;
			}
		}
	} while (isValidDirection == false);
}

// ------------------------------------------------------------------------------
// 
// ------------------------------------------------------------------------------
void ProcessAttackStatus(int attackStatus, int RowCoord, int ColCoord)
{
	switch (attackStatus)
	{
		case MISS:
			if (CurrentMode == ATTACKING)
			{
				switch (CurrentDirection)
				{
					case UP:
						CurrentDirection = DOWN;
						break;
					case RIGHT:
						CurrentDirection = LEFT;
						break;
					case DOWN:
						CurrentDirection = UP;
						break;
					case LEFT:
						CurrentDirection = RIGHT;
						break;
				}
				Iterations += 1;
				if (Iterations == 2)
				{
					CurrentMode = HUNTING;
					Iterations = 0;
				}
			}
			break;
		case HIT:
			if (CurrentMode == HUNTING)
			{
				CurrentMode = ATTACKING;
			}
			else if (CurrentMode == IDLE)
			{
				CurrentMode = HUNTING;
			}
			LastHitCoords.row = RowCoord;
			LastHitCoords.col = ColCoord;
			break;
		case SUNK:
			CurrentMode = IDLE;
			for (int x = 0; x < 4; x++)
			{
				CurrentAttackSequenceCheckedDirections[x] = false;
			}
			break;
	}
}