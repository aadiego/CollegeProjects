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
	ComputerPlayerBoard[GRIDROWS][GRIDCOLUMNS];							// Array for the computer player game board
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

	/* Reset the CurrentPlayer back to COMPUTER (Note: The first turn will actually be the HUMAN player's as the
	   PlayGame() function has a line of code that alternates the players which will run before the game actually starts.) */
	CurrentPlayer = COMPUTER;
	PlayGame();
}

// ------------------------------------------------------------------------------
// Randomly places the ships on the player boards.
// ------------------------------------------------------------------------------
void RandomizeShipLocations(BattleshipGameCell (&PlayerBoard)[GRIDROWS][GRIDCOLUMNS])
{
	// Loop through the total number of ships placing each in a random location.
	for (int shipNumber = 0; shipNumber < NUMBEROFSHIPS; shipNumber++)
	{
		// Get the size of the ship. Since there are 5 ship types use modulus operator in case the game is running with more than 5 ships.
		int shipLength = GetShipLength(static_cast<Name>(shipNumber % 5));

		// Variables to hold the returned coodinates and direction.
		Coordinates coords;
		Direction generatingDirection;
		do
		{
			// Randomly generate the starting coordinate pair between 0 and the lenght/width of the player board (GRIDROWS/GRIDCOLUMS).
			coords.row = rand() % GRIDROWS;
			coords.col = rand() % GRIDCOLUMNS;

			// Randomly select a generatingDirection and check to see if the ship will fit within the boundaries of the player board.
			IsInGridBoundary(coords, static_cast<Direction>(rand() % 4), generatingDirection, shipLength - 1);
		} while (IsValidShipPlacement(PlayerBoard, coords, generatingDirection, shipLength) == false); // Loop until ship has a valid placement.

		// Loop through each space the ship will occupy and set values.
		for (int shipSection = 0; shipSection < shipLength; shipSection++)
		{
			// Dynamiacally create the Ship variable and assign it to the shipInfo pointer variable.
			PlayerBoard[coords.row][coords.col].shipInfo = new Ship;

			// Set the ship name using the modulus operator in case the game is running with more than 5 ships.
			PlayerBoard[coords.row][coords.col].shipInfo->name = static_cast<Name>(shipNumber % 5);

			// Move to the next coordinate pair in the generatingDirection.
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
			return DESTROYERSIZE;
		default: // This should NEVER happen, but it's here just in case.
			return 0;
	}
}

// ------------------------------------------------------------------------------
// Checks to see if the coordinates extend beyond the boundaries of the player
// board for the specified direction and size.
// ------------------------------------------------------------------------------
bool IsInGridBoundary(Coordinates coords, Direction requstedDirection, int steps)
{
	/* Declare a new inverseDirection variable that will be trashed by this overload function as a NULL cannot be
	   passed into a reference variable. */
	Direction inverseDirection;
	return IsInGridBoundary(coords, requstedDirection, inverseDirection, steps);
}

// ------------------------------------------------------------------------------
// Checks to see if the coordinates extend beyond the boundaries of the player
// board for the specified direction and size.
// ------------------------------------------------------------------------------
bool IsInGridBoundary(Coordinates coords, Direction requstedDirection, Direction &actualDirection, int steps)
{
	// Declare variables to hold information for processing.
	int endGridCell, maxGridSize;
	Direction inverseDirection;

	switch (requstedDirection)
	{
		/* For the requstedDirection add or subtract the number of steps, set the maxGridSize to the GRIDROW or GRIDCOLUMN,
		   and specify the inverseDirection in case we need to move opposite direction. */
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

	//Verify that the endGridCell is within the boundary of the row or column.
	if (endGridCell < 0 || endGridCell >= maxGridSize)
	{
		// FALSE: Set the actualDirection reference variable to the inverseDirection and return false.
		actualDirection = inverseDirection;
		return false;
	}
	// TRUE: Set the actualDirection reference variable to the requestedDirection and return true.
	actualDirection = requstedDirection;
	return true;
}

// ------------------------------------------------------------------------------
// Checks to see if the ship position overlaps an existing ship.
// ------------------------------------------------------------------------------
bool IsValidShipPlacement(BattleshipGameCell(&PlayerBoard)[GRIDROWS][GRIDCOLUMNS], Coordinates coords, Direction direction, int shipLength)
{
	// Variable to hold the loop counter.
	int steps = 0;

	// Loop until the number of steps is greater than the shipLength.
	while (steps < shipLength)
	{
		// If the shipInfo variable pointer at the current position has a value, then return false.
		if (PlayerBoard[coords.row][coords.col].shipInfo != nullptr)
		{
			return false;
		}

		// Move to the next coordinate pair in the speficied direction.
		StepDirection(coords, direction);

		// Increment the counter.
		steps++;
	}
	return true;
}

// ------------------------------------------------------------------------------
// Moves the current coordinates one step in the direction specified.
// ------------------------------------------------------------------------------
void StepDirection(Coordinates &coords, Direction direction)
{
	// For coordinate pair reference variable add or subtract 1 to move in the specified direction.
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
// The main Battleship game loop. Prompts player for attack location, processes
// attack locations, and checks the win condition.
// ------------------------------------------------------------------------------
void PlayGame()
{
	do
	{
		// Clear the screen and redraw with the Battleship logo and player boards.
		ClearScreen();
		PrintLogo();
		DrawPlayerBoards(false); // Must be FALSE as it will display the opponent ships on screen. Useful for debugging, but NOT in PRODUCTION code.

		// Set the CurrentPlayer to the inverse of the CurrentPlayer.
		CurrentPlayer = static_cast<Player>((CurrentPlayer + 1) % 2);

		// Declare variables to hold information for processing.
		string attackLocation;
		AttackStatus results;

		do
		{
			switch (CurrentPlayer)
			{
				case HUMAN:
					// Prompt the user for a target location
					cout << "Please input target location: ";
					cin >> attackLocation;

					// Process the target location and store the return value in results.
					results = LaunchAttack(ComputerPlayerBoard, attackLocation);
					break;
				case COMPUTER:
					// Call the SimpleAI to select a target location
					attackLocation = SimpleAI_SelectTarget();

					// Dispaly the target location to the user.
					cout << "The computer targeted: " << attackLocation << endl;
					Coordinates coords;

					// Process the target location and store the return value in results.
					results = LaunchAttack(HumanPlayerBoard, attackLocation, coords);

					// Call the SimpleAi to process the returned results
					ProcessAttackStatus(results, coords.row, coords.col);
					break;
			}
			cout << endl;
		} while (results == UNKNOWN || results == ALREADYATTACKED); // Loop until the player hits a space on the board and that hasn't already been attacked.

		// Sleep for a few moments before checking win condition.
		Sleep(WAITBETWEENTURNS);
	} while (HumanPlayerShipsRemaining > 0 && ComputerPlayerShipsRemaining > 0); // Loop until the win condition (one player has one remaining ships) is met.

	// Clear the screen and redraw with the Battleship logo and player boards.
	ClearScreen();
	PrintLogo();
	DrawPlayerBoards(true); // Display the opponent ships so the human player knows where they were at (in the event they lost).

	// Display the win/lose message
	if (ComputerPlayerShipsRemaining == 0)
	{
		cout << "Congratulations! You defeated the computer!" << endl;
	}
	else
	{
		cout << "Sorry, you have been defeated." << endl;
	}

	// Call dispose to reset the player boards to an empty state (isHit = false and delete pointers).
	Dispose();

	// Prompt the user if they want to play again.
	char userSelection;
	cout << "Would you like to play again? (Y/N) ";
	cin.ignore(INT_MAX, '\n');
	cin.get(userSelection);
	if (tolower(userSelection) == 'y')
	{
		// Re-run SetupGame() to generate new boards to play again.
		SetupGame();
	}
}

// ------------------------------------------------------------------------------
// Draws the player boards on the screen.
// ------------------------------------------------------------------------------
void DrawPlayerBoards(bool ShowOpponentShips)
{
	// Constants holding screen positions.
	const int TopPosition = 11;
	const int LeftPosition = 20;
	const int RightPosition = -55; // Negative number counts from the right instead of left.

	/* MY SHIPS GRID */
	// Print the player board title and header row.
	PrintAtScreenPosition("             My Ships            ", LeftPosition, TopPosition, DEFAULT);
	PrintAtScreenPosition("    A  B  C  D  E  F  G  H  I  J ", LeftPosition, TopPosition + 1, DEFAULT);
	
	// Outer loop through the rows
	for (int row = 0; row < GRIDROWS; row++)
	{
		// Inner loop through the columns.
		for (int col = 0; col < GRIDCOLUMNS; col++)
		{
			// Print the row number
			PrintAtScreenPosition(to_string(row + 1), LeftPosition, (TopPosition + 2) + row, DEFAULT);

			// Set the cell value to " X " if hit, or "   " if un-hit.
			string value = HumanPlayerBoard[row][col].isHit ? " X " : "   ";

			// Print the cell onto the screen at the specified position with the specified coloring.
			PrintAtScreenPosition(value, (LeftPosition + 3) + (col * 3), (TopPosition + 2) + row, (HumanPlayerBoard[row][col].shipInfo != nullptr) ? HIT_SHOWSHIP : DEFAULT);
		}
	}

	/* MY ATTACKS GRID */
	// Print the player board title and header row.
	PrintAtScreenPosition("            My Attacks           ", RightPosition, TopPosition, DEFAULT);
	PrintAtScreenPosition("    A  B  C  D  E  F  G  H  I  J ", RightPosition, TopPosition + 1, DEFAULT);

	// Outer loop through the rows
	for (int row = 0; row < GRIDROWS; row++)
	{
		// Inner loop through the columns.
		for (int col = 0; col < GRIDCOLUMNS; col++)
		{
			// Print the row number
			PrintAtScreenPosition(to_string(row + 1), RightPosition, (TopPosition + 2) + row, DEFAULT);

			// Set the cell value to " X " if hit, or "   " if un-hit.
			string value = ComputerPlayerBoard[row][col].isHit ? " X " : "   ";

			// If the ShowOpponentShips parameter is true set the font_color to make the ships visible.
			WORD font_color = ShowOpponentShips ? HIT_SHOWSHIP : HIT_HIDESHIP;

			// Print the cell onto the screen at the specified position with the specified coloring.
			PrintAtScreenPosition(value, (RightPosition + 3) + (col * 3), (TopPosition + 2) + row, (ComputerPlayerBoard[row][col].shipInfo != nullptr) ? font_color : DEFAULT);
		}
	}

	// Reset the font color back to default.
	change_font_color(DEFAULT);

	// Print two extra lines for padding between player boards and game text.
	cout << endl << endl;
}

// ------------------------------------------------------------------------------
// Checks the player's board at the specified location and returns a result. 
// ------------------------------------------------------------------------------
AttackStatus LaunchAttack(BattleshipGameCell(&OpponentPlayerBoard)[GRIDROWS][GRIDCOLUMNS], string location)
{
	/* Declare a new coords variable that will be trashed by this overload function as a NULL cannot be
	   passed into a reference variable. */
	Coordinates coords;
	return LaunchAttack(OpponentPlayerBoard, location, coords);
}

// ------------------------------------------------------------------------------
// Checks the player's board at the specified location and returns a result. 
// ------------------------------------------------------------------------------
AttackStatus LaunchAttack(BattleshipGameCell(&OpponentPlayerBoard)[GRIDROWS][GRIDCOLUMNS], string location, Coordinates &coordinates)
{
	// Coordinates variable to hold the converted location string to coordinate pair.
	Coordinates coords;

	/* SetTarget() converts the location string and stores the value in the coords reference variable. Additionally, it returns true or false
	   if the target location is valid. */
	if (SetTarget(location, coords))
	{
		// Set the coordinates reference variable to the converted coords. (Used by the SimpleAI to track last hit coordinates).
		coordinates = coords;

		// Check to see if we've already attacked this space.
		if (OpponentPlayerBoard[coords.row][coords.col].isHit == false)
		{
			// Set the isHit boolean to true to show that this spot has been attacked.
			OpponentPlayerBoard[coords.row][coords.col].isHit = true;

			// Check to see if there is a ship at the location.
			if (OpponentPlayerBoard[coords.row][coords.col].shipInfo != nullptr)
			{
				Name shipName = OpponentPlayerBoard[coords.row][coords.col].shipInfo->name;			// Set the ship name local variable for reporting back to the user
				int hitsRemaining;																	// Variable to hold the number of hits remaining for the ship.
				int* shipsRemaining = &NumberOfShipsRemaining();									// Pointer variable to the HumanPlayerShipsRemaining or ComputerPlayerShipsRemaining

				// Check to see if the ship is sunk.
				if (WasShipSunk(OpponentPlayerBoard, shipName, hitsRemaining))
				{
					// Dereference and decrement the number of ships remaining
					*shipsRemaining -= 1;

					// Report the sunk message to the user and return SUNK.
					cout << "Hit! Sunk " << ShipNameEnumToString(shipName) << " (" << *shipsRemaining << " ship(s) remaining)." << endl;
					return SUNK;
				}
				else
				{
					// Report the hit message to the user and return HIT.
					cout << "Hit! " << ShipNameEnumToString(shipName) << " (" << hitsRemaining << " hit(s) remaining)." << endl;
					return HIT;
				}
			}
			else
			{
				// Report the missed message to the user and return MISS.
				cout << "Miss." << endl;
				return MISS;
			}
		}
		else
		{
			// Report the location already attacked message to the user and return ALREADYATTACKED.
			cout << "The attack location coordinates has already been attacked. Please try again." << endl;
			return ALREADYATTACKED;
		}
	}
	else
	{
		// Report the invalid target message to the user and return UNKNOWN.
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
	// Get the lenght of the ship for an inverse accumulator
	int shipLength = GetShipLength(shipName);

	// Outer loop through the rows
	for (int row = 0; row < GRIDROWS; row++)
	{
		// Inner loop through the columns
		for (int col = 0; col < GRIDCOLUMNS; col++)
		{
			// Check to see if a ship exists at the current location.
			if (PlayerBoard[row][col].shipInfo != nullptr)
			{
				/* Decrement from the shipLength inverse accumulator if its name matches the shipName paramater
				   and if the space has been hit. */
				if (PlayerBoard[row][col].shipInfo->name == shipName && PlayerBoard[row][col].isHit)
				{
					shipLength -= 1;
				}

				// If the shipLenght is zero set sectionsRemaining reference variable to zero and return true.
				if (shipLength == 0)
				{
					sectionsRemaining = 0;
					return true;
				}
			}
		}
	}
	// Set the sectionsRemaining reference variable and return false.
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
	// Outer loop through the rows
	for (int row = 0; row < GRIDROWS; row++)
	{
		// Inner loop through the columns
		for (int col = 0; col < GRIDCOLUMNS; col++)
		{
			// Reset the current position .isHit to faluse.
			PlayerBoard[row][col].isHit = false;

			// If a ship exists at the current location, delete it and set the pointer variable back to nullptr.
			if (PlayerBoard[row][col].shipInfo != nullptr)
			{
				delete PlayerBoard[row][col].shipInfo;
				PlayerBoard[row][col].shipInfo = nullptr;
			}
		}
	}
}