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

static BattleshipGameCell HumanPlayerBoard[GRIDROWS][GRIDCOLUMNS],		// Array for the human player game board
				   ComputerPlayerBoard[GRIDROWS][GRIDCOLUMNS];			// Array for the computer player game board
static int HumanPlayerShipsRemaining,									// Holds the number of ships remaining for the human player
	  ComputerPlayerShipsRemaining;										// Holds the number of ships remaining for the computer player
static Player CurrentPlayer = COMPUTER;									// Holds the current attacking player
const int WAITBETWEENTURNS = 3000;										// Milliseconds between turns.

// ------------------------------------------------------------------------------
// Sets up the player boards and starts the game.
// ------------------------------------------------------------------------------
void SetupGame()
{
	// Seed rand() with the current time.
	srand(time(0));
	
	// Randomly place the ships for both players.
	RandomizeShipLocations(HumanPlayerBoard);
	RandomizeShipLocations(ComputerPlayerBoard);

	// Set the number of player ships to the NUMBEROFSHIPS constant.
	HumanPlayerShipsRemaining = ComputerPlayerShipsRemaining = NUMBEROFSHIPS;
	CurrentPlayer = COMPUTER;
	PlayGame();
}

// ------------------------------------------------------------------------------
// Randomly places the ships on the player boards.
// ------------------------------------------------------------------------------
void RandomizeShipLocations(BattleshipGameCell (&PlayerBoard)[GRIDROWS][GRIDCOLUMNS])
{
	for (int shipNumber = 0; shipNumber < NUMBEROFSHIPS; shipNumber++)
	{
		int shipLength = GetShipLength(static_cast<Name>(shipNumber));

		Coordinates coords;
		Direction generatingDirection;
		do
		{
			coords.row = rand() % GRIDROWS;
			coords.col = rand() % GRIDCOLUMNS;
			IsInGridBoundary(coords, static_cast<Direction>(rand() % 4), generatingDirection, shipLength - 1);
		} while (IsValidShipPlacement(PlayerBoard, coords, generatingDirection, shipLength) == false);

		for (int shipSection = 0; shipSection < shipLength; shipSection++)
		{
			PlayerBoard[coords.row][coords.col].shipInfo = new Ship;
			PlayerBoard[coords.row][coords.col].shipInfo->name = static_cast<Name>(shipNumber);
			StepDirection(coords, generatingDirection);
		}
	}
}

// ------------------------------------------------------------------------------
// Get the length of the ship
// ------------------------------------------------------------------------------
int GetShipLength(Name shipName)
{
	switch (shipName)
	{
		case CARRIER:
			return CARRIERSIZE;
		case BATTLESHIP:
			return BATTLESHIPSIZE;
		case CRUISER:
			return CRUISERSIZE;
		case SUBMARINE:
			return SUBMARINESIZE;
		case DESTROYER:
		default:
			return DESTROYERSIZE;
	}
}

// ------------------------------------------------------------------------------
// Checks to see if the ship will extend beyond the boundaries of the player
// board for the direction and size.
// ------------------------------------------------------------------------------
bool IsInGridBoundary(Coordinates coords, Direction requstedDirection, int steps)
{
	Direction inverseDirection;
	return IsInGridBoundary(coords, requstedDirection, inverseDirection, steps);
}

// ------------------------------------------------------------------------------
// Checks to see if the ship will extend beyond the boundaries of the player
// board for the direction and size.
// ------------------------------------------------------------------------------
bool IsInGridBoundary(Coordinates coords, Direction requstedDirection, Direction &actualDirection, int steps)
{
	int endGridCell, maxGridSize;
	Direction inverseDirection;
	switch (requstedDirection)
	{
		case UP:
			endGridCell = coords.row - steps;
			maxGridSize = GRIDROWS;
			inverseDirection = DOWN;
			break;
		case RIGHT:
			endGridCell = coords.col + steps;
			maxGridSize = GRIDCOLUMNS;
			inverseDirection = LEFT;
			break;
		case DOWN:
			endGridCell = coords.row + steps;
			maxGridSize = GRIDROWS;
			inverseDirection = UP;
			break;
		case LEFT:
			endGridCell = coords.col - steps;
			maxGridSize = GRIDCOLUMNS;
			inverseDirection = RIGHT;
			break;
	}

	if (endGridCell < 0 || endGridCell >= maxGridSize)
	{
		actualDirection = inverseDirection;
		return false;
	}
	actualDirection = requstedDirection;
	return true;
}

// ------------------------------------------------------------------------------
// Checks to see if the ship position overlaps an existing ship.
// ------------------------------------------------------------------------------
bool IsValidShipPlacement(BattleshipGameCell(&PlayerBoard)[GRIDROWS][GRIDCOLUMNS], Coordinates coords, Direction direction, int shipLength)
{
	int steps = 0;
	while (steps < shipLength)
	{
		if (PlayerBoard[coords.row][coords.col].shipInfo != nullptr)
		{
			return false;
		}
		StepDirection(coords, direction);
		steps++;
	}
	return true;
}

// ------------------------------------------------------------------------------
// Moves the current coordinates one step in the direction specified.
// ------------------------------------------------------------------------------
void StepDirection(Coordinates &coords, Direction direction)
{
	switch (direction)
	{
		case UP:
			coords.row -= 1;
			break;
		case RIGHT:
			coords.col += 1;
			break;
		case DOWN:
			coords.row += 1;
			break;
		case LEFT:
			coords.col -= 1;
			break;
	}
}

// ------------------------------------------------------------------------------
// 
// ------------------------------------------------------------------------------
void PlayGame()
{
	do
	{
		ClearScreen();
		PrintLogo();
		DrawPlayerBoards(false);

		CurrentPlayer = static_cast<Player>((CurrentPlayer + 1) % 2);
		string attackLocation;
		AttackStatus results;
		do
		{
			switch (CurrentPlayer)
			{
				case HUMAN:
					cout << "Please input target location: ";
					cin >> attackLocation;
					results = LaunchAttack(ComputerPlayerBoard, attackLocation);
					break;
				case COMPUTER:
					attackLocation = SimpleAI_SelectTarget();
					cout << "The computer targeted: " << attackLocation << endl;
					Coordinates coords;
					results = LaunchAttack(HumanPlayerBoard, attackLocation, coords);
					ProcessAttackStatus(results, coords.row, coords.col);
					break;
			}
			cout << endl;
		} while (results == UNKNOWN || results == ALREADYATTACKED);
		Sleep(WAITBETWEENTURNS);
	} while (HumanPlayerShipsRemaining > 0 && ComputerPlayerShipsRemaining > 0);

	ClearScreen();
	PrintLogo();
	DrawPlayerBoards(true);
	if (ComputerPlayerShipsRemaining == 0)
	{
		cout << "Congratulations! You defeated the computer!" << endl;
	}
	else
	{
		cout << "Sorry, you have been defeated." << endl;
	}

	Dispose();

	char userSelection;
	cout << "Would you like to play again? (Y/N) ";
	cin.ignore(INT_MAX, '\n');
	cin.get(userSelection);
	if (tolower(userSelection) == 'y')
	{
		SetupGame();
	}
}

// ------------------------------------------------------------------------------
// 
// ------------------------------------------------------------------------------
void DrawPlayerBoards(bool ShowOpponentShips)
{
	int LeftPosition = 20;
	PrintAtScreenPosition("             My Ships            ", LeftPosition, 11, DEFAULT);
	PrintAtScreenPosition("    A  B  C  D  E  F  G  H  I  J ", LeftPosition, 12, DEFAULT);
	for (int row = 0; row < GRIDROWS; row++)
	{
		for (int col = 0; col < GRIDCOLUMNS; col++)
		{
			PrintAtScreenPosition(to_string(row + 1), LeftPosition, 13 + row, DEFAULT);
			string value = HumanPlayerBoard[row][col].isHit ? " X " : "   ";
			PrintAtScreenPosition(value, (LeftPosition + 3) + (col * 3), 13 + row, (HumanPlayerBoard[row][col].shipInfo != nullptr) ? HIT_SHOWSHIP : DEFAULT);
		}
	}

	int RightPosition = -55;
	PrintAtScreenPosition("            My Attacks           ", RightPosition, 11, DEFAULT);
	PrintAtScreenPosition("    A  B  C  D  E  F  G  H  I  J ", RightPosition, 12, DEFAULT);
	for (int row = 0; row < GRIDROWS; row++)
	{
		for (int col = 0; col < GRIDCOLUMNS; col++)
		{
			PrintAtScreenPosition(to_string(row + 1), RightPosition, 13 + row, DEFAULT);
			string value = ComputerPlayerBoard[row][col].isHit ? " X " : "   ";
			WORD font_color = ShowOpponentShips ? HIT_SHOWSHIP : HIT_HIDESHIP;
			PrintAtScreenPosition(value, (RightPosition + 3) + (col * 3), 13 + row, (ComputerPlayerBoard[row][col].shipInfo != nullptr) ? font_color : DEFAULT);
		}
	}

	change_font_color(DEFAULT);
	cout << endl << endl;
}

// ------------------------------------------------------------------------------
// 
// ------------------------------------------------------------------------------
AttackStatus LaunchAttack(BattleshipGameCell(&OpponentPlayerBoard)[GRIDROWS][GRIDCOLUMNS], string location)
{
	Coordinates coords;
	return LaunchAttack(OpponentPlayerBoard, location, coords);
}

// ------------------------------------------------------------------------------
// 
// ------------------------------------------------------------------------------
AttackStatus LaunchAttack(BattleshipGameCell(&OpponentPlayerBoard)[GRIDROWS][GRIDCOLUMNS], string location, Coordinates &coordinates)
{
	Coordinates coords;
	if (SetTarget(location, coords))
	{
		coordinates = coords;
		if (OpponentPlayerBoard[coords.row][coords.col].isHit == false)
		{
			OpponentPlayerBoard[coords.row][coords.col].isHit = true;
			if (OpponentPlayerBoard[coords.row][coords.col].shipInfo != nullptr)
			{
				Name shipName = OpponentPlayerBoard[coords.row][coords.col].shipInfo->name;
				int hitsRemaining;
				int* shipsRemaining = &NumberOfShipsRemaining();
				if (WasShipSunk(OpponentPlayerBoard, shipName, hitsRemaining))
				{
					*shipsRemaining -= 1;
					cout << "Hit! Sunk " << ShipNameEnumToString(shipName) << " (" << *shipsRemaining << " ship(s) remaining)." << endl;
					return SUNK;
				}
				else
				{
					cout << "Hit! " << ShipNameEnumToString(shipName) << " (" << hitsRemaining << " hit(s) remaining)." << endl;
					return HIT;
				}
			}
			else
			{
				cout << "Miss." << endl;
				return MISS;
			}
		}
		else
		{
			cout << "The attack location coordinates has already been attacked. Please try again." << endl;
			return ALREADYATTACKED;
		}
	}
	else
	{
		cout << "Invalid target. Please enter a valid target location." << endl;
		return UNKNOWN;
	}
}

// ------------------------------------------------------------------------------
// Checks the player's input location and converts it to Coordinates.
// ------------------------------------------------------------------------------
bool SetTarget(string location, Coordinates &coords)
{
	// Validate and convert first character (A thru J) into it's int value.
	char letter = location[0];
	switch (tolower(letter))
	{
		case 'a':
			coords.col = 0;
			break;
		case 'b':
			coords.col = 1;
			break;
		case 'c':
			coords.col = 2;
			break;
		case 'd':
			coords.col = 3;
			break;
		case 'e':
			coords.col = 4;
			break;
		case 'f':
			coords.col = 5;
			break;
		case 'g':
			coords.col = 6;
			break;
		case 'h':
			coords.col = 7;
			break;
		case 'i':
			coords.col = 8;
			break;
		case 'j':
			coords.col = 9;
			break;
		default:
			return false;
	}

	// Temporary string variable to hold the reconstructed Y coordinate
	string tempNumeric;

	// Reconstruct the Y coordinate for processing
	// Skip sub-zero as it will be the X coordinate handled above.
	for (int counter = 1; counter < location.length(); counter++)
	{
		// Verify that the character between 0 (ASCII 48) and 9 (ASCII 57)
		if (location[counter] >= 48 && location[counter] <= 57)
		{
			// Concatenate on the temp string for processing later
			tempNumeric += location[counter];
		}
		else
		{
			// If anything other than what is expected is found return false
			return false;
		}
	}

	// If a second coordinate position is not specified, return false.
	if (tempNumeric.empty())
	{
		return false;
	}
	
	// Convert the temp string into an integer
	int numeric = stoi(tempNumeric);

	// Validate the Y coordinate is between 1 and GRIDROWS.
	if (numeric >= 1 && numeric <= GRIDROWS)
	{
		coords.row = --numeric;
		return true;
	}
	return false;
}

// ------------------------------------------------------------------------------
// Checks the specified player board to see it has already been attacked.
// ------------------------------------------------------------------------------
bool CheckTarget(Player PlayerBoard, Coordinates coords)
{
	switch (PlayerBoard)
	{
		case HUMAN:
			return HumanPlayerBoard[coords.row][coords.col].isHit;
		case COMPUTER:
			return ComputerPlayerBoard[coords.row][coords.col].isHit;
	}
}

// ------------------------------------------------------------------------------
// Checks the specified player board to see if the ship has been sunk.
// ------------------------------------------------------------------------------
bool WasShipSunk(BattleshipGameCell(&PlayerBoard)[GRIDROWS][GRIDCOLUMNS], Name shipName, int &sectionsRemaining)
{
	int shipLength = GetShipLength(shipName);
	for (int row = 0; row < GRIDROWS; row++)
	{
		for (int col = 0; col < GRIDCOLUMNS; col++)
		{
			if (PlayerBoard[row][col].shipInfo != nullptr)
			{
				if (PlayerBoard[row][col].shipInfo->name == shipName && PlayerBoard[row][col].isHit)
				{
					shipLength -= 1;
				}

				if (shipLength == 0)
				{
					sectionsRemaining = 0;
					return true;
				}
			}
		}
	}
	sectionsRemaining = shipLength;
	return false;
}

// ------------------------------------------------------------------------------
// Returns the number of ships remaining for the opponent.
// ------------------------------------------------------------------------------
int& NumberOfShipsRemaining()
{
	switch (CurrentPlayer)
	{
		case HUMAN:
			return ComputerPlayerShipsRemaining;
		case COMPUTER:
			return HumanPlayerShipsRemaining;
	}
}

// ------------------------------------------------------------------------------
// Disposes all of the player board information for both players.
// ------------------------------------------------------------------------------
void Dispose()
{
	Dispose(HumanPlayerBoard);
	Dispose(ComputerPlayerBoard);
}

// ------------------------------------------------------------------------------
// Disposes all of the player board information on the specified board.
// ------------------------------------------------------------------------------
void Dispose(BattleshipGameCell(&PlayerBoard)[GRIDROWS][GRIDCOLUMNS])
{
	for (int row = 0; row < GRIDROWS; row++)
	{
		for (int col = 0; col < GRIDCOLUMNS; col++)
		{
			PlayerBoard[row][col].isHit = false;
			if (PlayerBoard[row][col].shipInfo != nullptr)
			{
				delete PlayerBoard[row][col].shipInfo;
				PlayerBoard[row][col].shipInfo = nullptr;
			}
		}
	}
}