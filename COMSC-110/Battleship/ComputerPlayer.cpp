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

static Mode CurrentMode = IDLE;																// Static variable that holds the SimpleAI's current mode.
static Direction CurrentDirection;															// Static variable that holds the SimpleAI's current direction.
static Coordinates LastHitCoords;															// Static variable that holds the last higt coordinates.
static bool CurrentAttackSequenceCheckedDirections[4] = { false,false,false,false };		// Static boolean array that holds the last checked cardinal direction. (For HUNTING mode).
static int Iterations = 0;																	// Static variable for edge case infinite loop prevention.

// ------------------------------------------------------------------------------
// Selects a target based on the CurrentMode.
// ------------------------------------------------------------------------------
string SimpleAI_SelectTarget()
{
	// Coordinates variable used to hold a copy of the static LastHitCoords for further processing.
	Coordinates coords;
	do
	{
		// Store a copy of the LastHitCoords in the variable.
		coords = LastHitCoords;
		switch (CurrentMode)
		{
			case IDLE:
				// Select a random coordinate pair
				coords.row = rand() % GRIDROWS;
				coords.col = rand() % GRIDCOLUMNS;
				break;
			case HUNTING:
				// Randomly selection a cardinal attack direction and fall through to ATTACKING.
				SelectDirection(); // Do NOT put a break; after this line as it should fall through the ATTACKING steps.
			case ATTACKING:
				// Call StepDirection() to move one space in the specified direction. NOTE: coords is a reference variable, so this WILL modify the original variable.
				StepDirection(coords, CurrentDirection);
				break;
		}
	} while (CheckTarget(HUMAN, coords) || IsInGridBoundary(coords, CurrentDirection, CurrentDirection, 0) == false); // Check to see if the space has already been hit and it it's within the boundaries.

	// Convert the coordinate value into a string and return for reporting to the UI and for use in LaunchAttack().
	string rtn;
	rtn += static_cast<char>(coords.col + 65);
	rtn += to_string(coords.row + 1);
	return rtn;
}

// ------------------------------------------------------------------------------
// Randomly selects a direction to head.
// ------------------------------------------------------------------------------
void SelectDirection()
{	
	bool isValidDirection = false;
	do
	{
		// THIS IS PURELY FOR INFINITE LOOP PROTECTION. If somehow the SimpleAI get stuck in an infinte loop while HUNTING this will
		// set the CurrentAttackSequenceCheckedDirections to false for all elements and set the mode back to IDLE.
		if (CurrentAttackSequenceCheckedDirections[UP] == true
			&& CurrentAttackSequenceCheckedDirections[LEFT] == true
			&& CurrentAttackSequenceCheckedDirections[DOWN] == true
			&& CurrentAttackSequenceCheckedDirections[RIGHT] == true)
		{
			CurrentMode = IDLE;
			CurrentAttackSequenceCheckedDirections[UP] = false;
			CurrentAttackSequenceCheckedDirections[LEFT] = false;
			CurrentAttackSequenceCheckedDirections[DOWN] = false;
			CurrentAttackSequenceCheckedDirections[RIGHT] = false;
			return;
		}

		// Coordinates variable used to hold a copy of the static LastHitCoords for further processing.
		Coordinates coords = LastHitCoords;

		// Randomly select a direction
		Direction randomDirection = static_cast<Direction>(rand() % 4);

		// Check to see if we've attempted to go this direction before.
		if (CurrentAttackSequenceCheckedDirections[randomDirection] == false)
		{
			// Check to see if the random direction is on the player's board. If not, set the direction to checked direction to true and continue on.
			if (IsInGridBoundary(coords, randomDirection) == false)
			{
				CurrentAttackSequenceCheckedDirections[randomDirection] = true;
			}
			else
			{
				// Set that we have checked this direction, set the CurrentDirection to the randomly selected direciton, and set isValidDirection to true to exit the loop.
				CurrentAttackSequenceCheckedDirections[randomDirection] = true;
				CurrentDirection = randomDirection;
				isValidDirection = true;
			}
		}
	} while (isValidDirection == false); // Loop until a valid direction is found.
}

// ------------------------------------------------------------------------------
// Processes the results from LaunchAttack() which determines how the SimpleAI
// will proceed on its next move.
// ------------------------------------------------------------------------------
void ProcessAttackStatus(int attackStatus, int RowCoord, int ColCoord)
{
	switch (attackStatus)
	{
		case MISS:
			// If the current mode is attacking and we MISS, then inverse the direction for next attack.
			if (CurrentMode == ATTACKING)
			{
				switch (CurrentDirection)
				{
					case UP:
						CurrentDirection = DOWN;
						CurrentAttackSequenceCheckedDirections[DOWN] = true;
						break;
					case RIGHT:
						CurrentDirection = LEFT;
						CurrentAttackSequenceCheckedDirections[LEFT] = true;
						break;
					case DOWN:
						CurrentDirection = UP;
						CurrentAttackSequenceCheckedDirections[UP] = true;
						break;
					case LEFT:
						CurrentDirection = RIGHT;
						CurrentAttackSequenceCheckedDirections[RIGHT] = true;
						break;
				}

				// TLDR; This preevents an edge case where two ships could be next to each other and it misses on both sides.
				/* Aric: While testing I found that it's possilbe for the game to place two ships next to each other and the SimpleAI to hit
				         the first ship (GOES INTO HUNTING MODE) and then the second ship (GOES INTO ATTACKING MODE) and then miss. The above
						 code will cause the direction to inverse for the next attack. However, if it misses again it will attempt to invert again
						 and cause the SimpleAI to never select a valid location leading to an inifite loop. Instead this keeps track of how many
						 times this happens and if it happens twice, it will return to HUNTING mode. This could probably get fixed if the SimpleAI
						 were a bit more advanced and knew that it hit different ship than the first one, but that is too advanced for this
						 concept. */
				Iterations += 1;
				if (Iterations == 2)
				{
					CurrentMode = HUNTING;
					Iterations = 0;
				}
			}
			break;
		case HIT:
			// If the current mode is HUNTING switch to ATTACKING.
			if (CurrentMode == HUNTING)
			{
				CurrentMode = ATTACKING;
			}
			// If the current mode is IDLE switch to HUNTING.
			else if (CurrentMode == IDLE)
			{
				CurrentMode = HUNTING;
			}
			// Store the last hit coordinates.
			LastHitCoords.row = RowCoord;
			LastHitCoords.col = ColCoord;
			break;
		case SUNK:
			// Reset the check variables to their defaults and switch the mode back to IDLE.
			Iterations = 0;
			CurrentMode = IDLE;
			CurrentAttackSequenceCheckedDirections[UP] = false;
			CurrentAttackSequenceCheckedDirections[LEFT] = false;
			CurrentAttackSequenceCheckedDirections[DOWN] = false;
			CurrentAttackSequenceCheckedDirections[RIGHT] = false;
			break;
	}
}