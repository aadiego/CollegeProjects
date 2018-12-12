	// Final Project: Battleship Game
	// Huda Biltagi and Aric A

#include "Program.h"

	BattleshipGameCell GameBoard[rows][cols];							// Create 10x10 array to serve as game board.
	BattleshipGameCell ComputerBoard[rows][cols];						// Create 10x10 array to serve as computer game board.


	/************************
	 *						*
	 *  CLEARS THE BOARD	*
	 *						*
	 ************************/
	void ClearBoard()
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				GameBoard[i][j].isHit = 0;
				ComputerBoard[i][j].isHit = 0;
			}
		}
	}

	/************************
	 *						*
	 * SETS NUMBER OF SHIPS	*
	 *						*
	 ************************/
	int NumberOfShips(BattleshipGameCell Board[rows][cols])
	{
		int c = 0;

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (Board[i][j].isHit == 1)
					c++;
			}
		}

		return c;
	}




	/*************************
	 *						 *
	 *  SETS SHIPS IN RANDOM *
	 *  LOCATIONS ON THE     *
	 *		BOARD			 *
	 ************************/
	void RandShips(BattleshipGameCell Board[rows][cols])
	{
		int s = 0;
		while (s < maxships)
		{
			int x = rand() % rows;
			int y = rand() % cols;
			if (Board[x][y].isHit != 1)
			{
				s++;
				Board[x][y].isHit = 1;
			}
		}
	}

	/********************************************
	*											*
	*TO SHOW THE VALUES CURRENTLY ON THE BOARD	*
	*											*
	********************************************/
	void ShowValue()
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				cout << ComputerBoard[i][j].isHit << " ";
			}
			cout << endl;
		}
	}

	bool CheckTarget(Player PlayerBoard, Coordinates coords)
	{
		switch (PlayerBoard)
		{
			case HUMAN:
				return GameBoard[coords.row][coords.col].isHit == 2;
			case COMPUTER:
				return ComputerBoard[coords.row][coords.col].isHit == 2;
		}
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
			maxGridSize = rows;
			inverseDirection = DOWN;
			break;
		case RIGHT:
			endGridCell = coords.col + steps;
			maxGridSize = cols;
			inverseDirection = LEFT;
			break;
		case DOWN:
			endGridCell = coords.row + steps;
			maxGridSize = rows;
			inverseDirection = UP;
			break;
		case LEFT:
			endGridCell = coords.col - steps;
			maxGridSize = cols;
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


	/************************
	 *						*
	 * ATTACK SEQUENCE		*
	 *						*
	 ************************/
	// ------------------------------------------------------------------------------
	// Checks the player's board at the specified location and returns a result. 
	// ------------------------------------------------------------------------------
	AttackStatus LaunchAttack(Coordinates coords, BattleshipGameCell Board[rows][cols])
	{
		// Check to see if we've already attacked this space.
		if (Board[coords.row][coords.col].isHit != 2)
		{
			// Check to see if there is a ship at the location.
			if (Board[coords.row][coords.col].isHit == 1)
			{
				Board[coords.row][coords.col].isHit = 2;
				// Report the sunk message to the user and return SUNK.
				cout << "Hit! Sunk (" << NumberOfShips(Board) << " ship(s) remaining)." << endl;
				return SUNK;
			}
			else
			{
				Board[coords.row][coords.col].isHit = 2;
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

	static Mode CurrentMode = IDLE;																// Static variable that holds the SimpleAI's current mode.
	static Direction CurrentDirection;															// Static variable that holds the SimpleAI's current direction.
	static Coordinates LastHitCoords;															// Static variable that holds the last higt coordinates.
	static bool CurrentAttackSequenceCheckedDirections[4] = { false,false,false,false };		// Static boolean array that holds the last checked cardinal direction. (For HUNTING mode).
	static int Iterations = 0;																	// Static variable for edge case infinite loop prevention.

	// ------------------------------------------------------------------------------
	// Selects a target based on the CurrentMode.
	// ------------------------------------------------------------------------------
	Coordinates SimpleAI_SelectTarget()
	{
		// Coordinates variable used to hold a copy of the static LastHitCoords for further processing.
		Coordinates coords = LastHitCoords;
		do
		{
			switch (CurrentMode)
			{
			case IDLE:
				// Select a random coordinate pair
				coords.row = rand() % rows;
				coords.col = rand() % cols;
				break;
			case HUNTING:
				// Reset the coords to the LastHitCoords (in case this isn't it's first pass through).
				coords = LastHitCoords;
				// Randomly selection a cardinal attack direction and fall through to ATTACKING.
				SelectDirection(); // Do NOT put a break; after this line as it should fall through the ATTACKING steps.
			case ATTACKING:
				// Move one space in the specified direction.
				switch (CurrentDirection)
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
				break;
			}
		} while (CheckTarget(HUMAN, coords) || IsInGridBoundary(coords, CurrentDirection, CurrentDirection, 0) == false); // Check to see if the space has already been hit and it it's within the boundaries.

		return coords;
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
				Direction temp;
				// Check to see if the random direction is on the player's board. If not, set the direction to checked direction to true and continue on.
				if (IsInGridBoundary(coords, randomDirection, temp, 1) == false)
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

	int main()
	{
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
		while (userselection < MIN_INPUT || userselection > MAX_INPUT)
		{
			cout << "\n\nInvalid Input!\n";
			cout << "Enter only a number listed in the above menu.\n";
			cin >> userselection;
		}

		// print out corresponding statement for each item using switch statement 
		switch (userselection)
		{
		case 1:	////////// RUN GAME ///////////////////;
				srand(time(NULL));
				ClearBoard();
				RandShips(GameBoard);
				RandShips(ComputerBoard);
				int pos1, pos2;
				char prompt;
				while (NumberOfShips(GameBoard) > 0 && NumberOfShips(ComputerBoard) > 0)
				{
					cout << "Please input location: "; cin >> pos1 >> pos2;
					Coordinates coords;
					coords.row = pos1;
					coords.col = pos2;
					LaunchAttack(coords, GameBoard);

					cout << "Computer target location: ";
					Coordinates target = SimpleAI_SelectTarget();
					cout << target.row << " " << target.col << endl;
					LaunchAttack(target, ComputerBoard);
				}
				cout << "Game over!" << endl;
				ShowValue();
				system("pause");
				return 0;
		case 2:	cout << "Game Objective:\n -Find and Sink all 10 ships hidden on the board\n\n";
			cout << "Rules:\n1-Fire shots at the board by calling out grid coordinates location (zero start). Ex: 0 1 \n";
			cout << "\n2-A hit indicates that a ship has been sunk,\nwhile a miss indicates that the shot missed and there is no ship \nat that coordinate.\n";
			cout << "\n3-Input another coordinate and try to find and sink all the ships!\n";
			cout << "\nHAPPY HUNTING!!\n\n";
			_getch();
			/////////select 1 to return to the main menu//////////??????????
			break;
		case 3:	return 0;
			/////////select 1 to return to the main menu//////////??????????
			break;

		}
	}
	