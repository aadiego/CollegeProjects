	// Final Project: Battleship Game
	// Huda Biltagi and Aric A

#include <iostream>
#include <ctime>
	using namespace std;

	void ClearBoard();
	void ShowValue();
	int NumberOfShips();
	void RandShips();
	bool Attack(int, int);


	const int rows = 10;					// Create 10x10 array to serve as game board.
	const int cols = 10;
	int GameBoard[rows][cols];

	int maxships = 10;						// Maximum number of ships on the board.


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
				GameBoard[i][j] = 0;
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
				cout << GameBoard[i][j] << " ";
			}
			cout << endl;
		}
	}





	/************************
	 *						*
	 * SETS NUMBER OF SHIPS	*
	 *						*
	 ************************/
	int NumberOfShips()
	{
		int c = 0;

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (GameBoard[i][j] == 1)
					c++;
			}
		}

		return 0;
	}




	/*************************
	 *						 *
	 *  SETS SHIPS IN RANDOM *
	 *  LOCATIONS ON THE     *
	 *		BOARD			 *
	 ************************/
	void RandShips()
	{
		int s = 0;
		while (s < maxships)
		{
			int x = rand() % rows;
			int y = rand() % cols;
			if (GameBoard[x][y] != 1)
			{
				s++;
				GameBoard[x][y] = 1;
			}
		}
	}




	/************************
	 *						*
	 * ATTACK SEQUENCE		*
	 *						*
	 ************************/
	bool Attack(int x, int y)
	{
		if (GameBoard[x][y] == 1)
		{
			GameBoard[x][y] = 2;
			return true;
		}
		return false;
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
				RandShips();
				int pos1, pos2;
				char prompt;
				while (1)
				{
					cout << "Please input location: "; cin >> pos1 >> pos2;
					if (Attack(pos1, pos2))
						cout << "DIRECT HIT! You sunk a ship!" << endl;
					else
						cout << "Shot Missed! No ship at this location." << endl;
					cout << "Number of ships left: " << NumberOfShips() << endl;
					/////////cout << "Do you want to surrender (y/n)? "; cin >> prompt;
					/////if (prompt == 'y')
						//break;
				}
				cout << "Game over!" << endl;
				ShowValue();
				system("pause");
				return 0;
		case 2:	cout << "Game Objective:\n -Find and Sink all 10 ships hidden on the board\n\n";
			cout << "Rules:\n1-Fire shots at the board by calling out grid coordinates location. Ex: A 1 \n";
			cout << "\n2-A hit indicates that a ship has been sunk,\nwhile a miss indicates that the shot missed and there is no ship \nat that coordinate.\n";
			cout << "\n3-Input another coordinate and try to find and sink all the ships!\n";
			cout << "\nHAPPY HUNTING!!\n\n";
			/////////select 1 to return to the main menu//////////??????????
			break;
		case 3:	cout << "You have exited the game!";
			/////////select 1 to return to the main menu//////////??????????
			break;

		}
	}
	