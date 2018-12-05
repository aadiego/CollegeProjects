#include <iostream>
#include "Prototype.h"
using namespace std;


int main()


{
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

}