	// Final Project: Battleship Game
	// Huda Biltagi and Aric A

#include "Program.h"

	BattleshipGameCell GameBoard[rows][cols];							// Create 10x10 array to serve as game board.
	BattleshipGameCell ComputerBoard[rows][cols];						// Create 10x10 array to serve as computer game board.

	int main()
	{
		// Display menu to the user, with instructions to pick one item from the list by hitting the appropriate number on their keyboard.
		const char MAX_INPUT = 3, MIN_INPUT = 1;
		int userselection;

		do
		{
			cout << "Please select 1, 2 or 3 from the following menu:\n\n";
			cout << "1. Play Game!\n";
			cout << "2. How To Play\n";
			cout << "3. Exit Game\n\n";
			cout << "Your selection: ";
			cin >> userselection;

			// Validate user input with while loop
			while (userselection < MIN_INPUT || userselection > MAX_INPUT)
			{
				cout << "\n\nInvalid Input!\n";
				cout << "Enter only a number listed in the above menu.\n";
				cin >> userselection;
			}

			// print out corresponding statement for each item using switch statement 
			switch (userselection)
			{
				case 1:	////////// RUN GAME //////////
					srand(time(NULL));
					ClearBoard();
					RandShips(GameBoard);
					RandShips(ComputerBoard);
					int pos1, pos2;
					char prompt;
					while (NumberOfShips(GameBoard) > 0 && NumberOfShips(ComputerBoard) > 0)
					{
						cout << "Please input location: ";
						cin >> pos1 >> pos2;
						Coordinates coords;
						coords.row = pos1;
						coords.col = pos2;
						LaunchAttack(coords, GameBoard);
						cout << endl;

						cout << "Computer target location: ";
						Coordinates target = SimpleAI_SelectTarget();
						cout << target.row << " " << target.col << endl;
						LaunchAttack(target, ComputerBoard);
						cout << endl;
					}
					cout << "Game over!" << endl;
					ShowValue();
					system("pause");
				case 2: ////////// DISPLAY INSTRUCTIONS //////////
					cout << "Game Objective:\n -Find and Sink all " << maxships << " ships hidden on the board\n\n";
					cout << "Rules:\n1-Fire shots at the board by calling out grid coordinates location (zero start). Ex: 0 1 \n";
					cout << "\n2-A hit indicates that a ship has been sunk,\nwhile a miss indicates that the shot missed and there is no ship \nat that coordinate.\n";
					cout << "\n3-Input another coordinate and try to find and sink all the ships!\n";
					cout << "\nHAPPY HUNTING!!\n";
					cout << "Please press any key to return to the main menu.\n\n";
					_getch();
					break;
			}
		} while (userselection != MAX_INPUT);
	}

	// CLEARS THE BOARD
	void ClearBoard()
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				GameBoard[i][j].isHit = false;
				GameBoard[i][j].containsShip = false;
				ComputerBoard[i][j].isHit = false;
				ComputerBoard[i][j].containsShip = false;
			}
		}
	}

	// SETS NUMBER OF SHIPS
	int NumberOfShips(BattleshipGameCell Board[rows][cols])
	{
		int c = 0;

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (Board[i][j].isHit == false && Board[i][j].containsShip == true)
					c++;
			}
		}

		return c;
	}

	// SETS SHIPS IN RANDOM LOCATIONS ON THE BOARD
	void RandShips(BattleshipGameCell Board[rows][cols])
	{
		int s = 0;
		while (s < maxships)
		{
			int x = rand() % rows;
			int y = rand() % cols;
			if (Board[x][y].containsShip == false)
			{
				s++;
				Board[x][y].containsShip = true;
			}
		}
	}

	// TO SHOW THE VALUES CURRENTLY ON THE BOARD
	void ShowValue()
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				cout << (ComputerBoard[i][j].containsShip ? "X" : "~") << " ";
			}
			cout << endl;
		}
	}

	// ------------------------------------------------------------------------------
	// Checks the specified player board to see it has already been attacked.
	// ------------------------------------------------------------------------------
	bool CheckTarget(Player PlayerBoard, Coordinates coords)
	{
		switch (PlayerBoard)
		{
		case HUMAN:
			return GameBoard[coords.row][coords.col].isHit == true;
		case COMPUTER:
			return ComputerBoard[coords.row][coords.col].isHit == true;
		}
	}

	 // ------------------------------------------------------------------------------
	 // Checks the player's board at the specified location and returns a result. 
	 // ------------------------------------------------------------------------------
	AttackStatus LaunchAttack(Coordinates coords, BattleshipGameCell Board[rows][cols])
	{
		// Check to see if we've already attacked this space.
		if (Board[coords.row][coords.col].isHit != true)
		{
			Board[coords.row][coords.col].isHit = true;

			// Check to see if there is a ship at the location.
			if (Board[coords.row][coords.col].containsShip == true)
			{
				// Report the sunk message to the user and return SUNK.
				cout << "Hit! Sunk (" << NumberOfShips(Board) << " ship(s) remaining)." << endl;
				return SUNK;
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

	// ------------------------------------------------------------------------------
	// Selects a target based on the CurrentMode.
	// ------------------------------------------------------------------------------
	Coordinates SimpleAI_SelectTarget()
	{
		// Coordinates variable used to hold a copy of the static LastHitCoords for further processing.
		Coordinates coords;
		do
		{
			// Select a random coordinate pair
			coords.row = rand() % rows;
			coords.col = rand() % cols;
			break;
		} while (CheckTarget(HUMAN, coords)); // Check to see if the space has already been hit.

		return coords;
	}