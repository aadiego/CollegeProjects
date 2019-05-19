#include "Game.h"
using namespace std;

// Function Prototypes
bool parseCmdLineArgs(int, char*[]);
void displayHelpMessage(string);
void displayHowToPlayMessage();

// Variables and Constants
GameOptions options;									// Holds the game options used by the SetupGame function to build the game objects.

// *******************************************************************************************
// **     Function: main (Program entry point)												**
// **   Parameters: int argc																**
// **				char *argv[]															**
// **       Return: int																		**
// **  Description: Entry point for the program. Parses command line arguments and displays	**
// **				the main menu.															**
// *******************************************************************************************
int main(int argc, char *argv[])
{
	// Set the default return value to EXIT_SUCCESS.
	int ret = EXIT_SUCCESS;

	// Wrapping the entire application in one try...catch block. While there shouldn't be any exceptions thrown, I'd rather have them be caught, reported out, and exit gracefully than crash.
	try
	{
		// Check and parse the command line arguments. If they are well-formed then proceed to display the title screen and main menu. If not, a usage/help message is displayed.
		if (parseCmdLineArgs(argc, argv))
		{
			// Call the SetupConsole function to set the console defaults for the game.
			SetupConsole();

			menu:
				ClearScreen();
				PrintLogo();

				const int charsPerRow = 19;
				const string PlayGame = "     PLAY GAME     ";
				const string HowToPlay = "    HOW TO PLAY    ";
				const string ExitGame = "     EXIT GAME     ";

				int selectionIndex = 0;
				int userSelection = INT_MIN;
				do
				{
					PrintCenterScreenAtPosition(PlayGame, 30, charsPerRow, selectionIndex == 0 ? SELECTED_TEXT : DEFAULT);
					PrintCenterScreenAtPosition(HowToPlay, 32, charsPerRow, selectionIndex == 1 ? SELECTED_TEXT : DEFAULT);
					PrintCenterScreenAtPosition(ExitGame, 34, charsPerRow, selectionIndex == 2 ? SELECTED_TEXT : DEFAULT);

					switch (_getch())
					{
						case KEY_UP:
							selectionIndex = selectionIndex == 0 ? 2 : --selectionIndex;
							break;
						case KEY_DOWN:
							selectionIndex = ++selectionIndex % 3;
							break;
						case KEY_ENTER:
							userSelection = selectionIndex;
							break;
						case KEY_ESCAPE:
							userSelection = 2;
					}
				} while (userSelection == INT_MIN);

				switch(userSelection)
				{
					case 0:
						goto playgame;
						break;
					case 1:
						goto howtoplay;
						break;
					case 2:
						goto exit;
						break;
				}

			playgame:
				if (SetupGame(options))
				{
					options.seed = 0;
					goto playgame;
				}
				options.seed = 0;
				goto menu;

			howtoplay:
				displayHowToPlayMessage();
				goto menu;

			exit:
				return EXIT_SUCCESS;
		}
	}
	catch (exception &ex)
	{
		cout << ex.what();
		ret = EXIT_FAILURE;
	}
	return ret;
}

// *******************************************************************************************
// **     Function: parseCmdLineArgs														**
// **   Parameters: int argc																**
// **				char *argv[]															**
// **       Return: bool																	**
// **  Description: Command line parser that stores the command line arguments into the		**
// **				options variable used by game.											**	
// *******************************************************************************************
bool parseCmdLineArgs(int argc, char* argv[])
{
	// Set the default return value to true.
	bool ret = true;

	// Loop through each of the command line arguments, skipping 0 as it's the executable path and name.
	for (int count = 1; count < argc; ++count)
	{
		// Declare two variables to hold the argument key and it's value
		string key = ToLower(string(argv[count]));
		string value = "";

		// Check if there is an argument value for this argument key by checking if the cout + 1 is less than the total argument count.
		if (count + 1 < argc)
		{
			value = string(argv[count + 1]);
		}

		// Giant if...else if...else statement that compares the key vs the expected values. If an entered argument key doesn't match what is expected, the usage/help message is displayed.
		if (key == "-seed")
		{
			// Check if the first character of the value is a '-' (dash). If so, then that signifies the start of the next argument key thus there was no argument value for this key so throw an exception.
			if (value[0] == '-')
			{
				throw InvalidArgumentException("Found argument key 'seed'; however, the argument value is empty.");
			}

			// Convert the string seed value to an unsigned long and set the seed in the game options and increment the count as we used two argument values for the one loop iteration.
			options.seed = stoul(value, nullptr, 0);
			++count;
		}
		else if(key == "-bluediseasename")
		{
			// Check if the first character of the value is a '-' (dash). If so, then that signifies the start of the next argument key thus there was no argument value for this key so throw an exception.
			if (value[0] == '-')
			{
				throw InvalidArgumentException("Found argument key 'bluediseasename'; however, the argument value is empty.");
			}

			// Set the BlueDiseaseName in the game options and increment the count as we used two argument values for the one loop iteration.
			options.BlueDiseaseName = value;
			++count;
		}
		else if (key == "-yellowdiseasename")
		{
			// Check if the first character of the value is a '-' (dash). If so, then that signifies the start of the next argument key thus there was no argument value for this key so throw an exception.
			if (value[0] == '-')
			{
				throw InvalidArgumentException("Found argument key 'yellowdiseasename'; however, the argument value is empty.");
			}

			// Set the YellowDiseaseName in the game options and increment the count as we used two argument values for the one loop iteration.
			options.YellowDiseaseName = value;
			++count;
		}
		else if (key == "-purplediseasename")
		{
			// Check if the first character of the value is a '-' (dash). If so, then that signifies the start of the next argument key thus there was no argument value for this key so throw an exception.
			if (value[0] == '-')
			{
				throw InvalidArgumentException("Found argument key 'purplediseasename'; however, the argument value is empty.");
			}

			// Set the PurpleDiseaseName in the game options and increment the count as we used two argument values for the one loop iteration.
			options.PurpleDiseaseName = value;
			++count;
		}
		else if (key == "-reddiseasename")
		{
			// Check if the first character of the value is a '-' (dash). If so, then that signifies the start of the next argument key thus there was no argument value for this key so throw an exception.
			if (value[0] == '-')
			{
				throw InvalidArgumentException("Found argument key 'reddiseasename'; however, the argument value is empty.");
			}

			// Set the RedDiseaseName in the game options and increment the count as we used two argument values for the one loop iteration.
			options.RedDiseaseName = value;
			++count;
		}
		else if (key == "-numberofepidemics")
		{
			// Check if the first character of the value is a '-' (dash). If so, then that signifies the start of the next argument key thus there was no argument value for this key so throw an exception.
			if (value[0] == '-')
			{
				throw InvalidArgumentException("Found argument key 'numberofepidemics'; however, the argument value is empty.");
			}

			// Convert the string epidemics value to an unsigned long and check if the value is within range (4 <= numberofepidemics <= 6). If not, throw an exception.
			const unsigned int epidemics = stoul(value, nullptr, 0);
			if (epidemics < 4 || epidemics > 6)
			{
				throw InvalidArgumentException("The number of Epidemics must be between 4 and 6.");
			}

			// Set the NumberOfEpidemics in the game options and increment the count as we used two argument values for the one loop iteration.
			options.NumberOfEpidemics = epidemics;
			++count;
		}
		// If we made it here then the user typed in something other than an expected argument key so display the usage message.
		else
		{
			// Get the executable path and name stored in argument value 0 and split it off to just the executable name.
			string ExecutablePathAndName = string(argv[0]);
			size_t pos = ExecutablePathAndName.rfind('\\', ExecutablePathAndName.length());
			if (pos != string::npos)
			{
				ExecutablePathAndName = ExecutablePathAndName.substr(pos + 1, ExecutablePathAndName.length() - 1);
			}

			// Display the usage/help message with the correct executable name filled in.
			displayHelpMessage(ExecutablePathAndName);

			// Set the return value to false to prevent the application from running any further.
			ret = false;
		}
	}
	return ret;
}

// *******************************************************************************************
// **     Function: displayHelpMessage														**
// **   Parameters: string ExecutableName													**
// **       Return: void																	**
// **  Description: Displays the usage/help message in the command line.					**
// *******************************************************************************************
void displayHelpMessage(string ExecutableName)
{
	cout << "Usage: " << ExecutableName << " [-help | -?] [-seed <unsigned_int>] [-bluediseasename <string>] [-yellowdiseasename <string>] [-purplediseasename <string>] [-reddiseasename <string>] [-numberofepidemics [4 | 5 | 6]]" << endl << endl;
	cout << "-help | -?" << "\t\t" << "Displays this help message" << endl;
	cout << "-seed" << "\t\t\t" << "Sets the seed used by the random number generator. (optional)" << endl;
	cout << "-bluediseasename" << "\t" << "Sets the name for the Blue disease. (optional)" << endl;
	cout << "-yellowdiseasename" << "\t" << "Sets the name for the Yellow disease. (optional)" << endl;
	cout << "-purplediseasename" << "\t" << "Sets the name for the Purple disease. (optional)" << endl;
	cout << "-reddiseasename" << "\t\t" << "Sets the name for the Red disease. (optional)" << endl;
	cout << "-numberofepidemics" << "\t" << "Sets the number of epidemics in the Player deck. [4 =  Introductory (default) | 5 = Standard | 6 = Heroic] (optional)" << endl;
}

// *******************************************************************************************
// **     Function: displayHowToPlayMessage													**
// **   Parameters: N/A																		**
// **       Return: void																	**
// **  Description: Displays the 'How To Play' message.										**
// *******************************************************************************************
void displayHowToPlayMessage()
{
	// Clear the screen and reprint the logo (without the subtext)
	ClearScreen();
	PrintLogo(false);

	// Page 1 of 3 text
	cout << "Do you have what it takes to save humanity? As a skilled member of a disease-fighting team, you must keep four deadly" << endl
		<< "diseases at bay while discovering their cures." << endl
		<< endl
		<< "You will travel across the globe, treating infections while finding resources for cures. The clock is ticking as" << endl
		<< "outbreaks and epidemics fuel the spreading plagues." << endl
		<< endl
		<< "Can you find all four cures in time? The fate of humanity is in your hands!" << endl
		<< endl
		<< endl
		<< "Overview" << endl
		<< "-------------" << endl
		<< "In this lite version of Pandemic, you are the solo member of a disease control team. You must work to develop cures and" << endl
		<< "prevent disease outbreaks, before 4 deadly diseases (Blue, Yellow, Black, and Red) contaminate humanity." << endl
		<< endl
		<< "The goal is to discover cures for all 4 diseases. You lose if:" << endl
		<< " " << (char)175 << " 8 outbreaks occur (a worldwide panic happens)," << endl
		<< " " << (char)175 << " not enough disease cubes are left when needed (a disease spreads too much), or," << endl
		<< " " << (char)175 << " not enough player cards are left when needed (your team runs out of time)." << endl
		<< endl
		<< endl
		<< "Player Turn" << endl
		<< "----------------" << endl
		<< "You may do up to 4 actions each turn; however, some of these actions may not be available at your specific location." << endl
		<< endl
		<< "Select any combination of the actions listed below. You may do the same action several times, each time counting as 1" << endl
		<< "action. Your role’s special abilities may change how an action is done." << endl
		<< endl
		<< "Movement Actions" << endl
		<< " " << (char)175 << " Drive/Ferry: Move from your current location to a neighboring city." << endl
		<< " " << (char)175 << " Direct Flight: Discard a City card to move to the city named on the card." << endl
		<< " " << (char)175 << " Charter Flight: Discard the City card that matches the city you are in to move to any city." << endl
		<< " " << (char)175 << " Shuttle Flight: Move from a city with a research station to any other city that has a research station." << endl
		<< endl
		<< "Page 1 of 3" << endl
		<< "Press ENTER to continue or ESCAPE to return to the main menu...";

	// Do...while loop that waits for the correct keypress before continuing
	bool nextPage = false;
	do
	{
		switch (_getch())
		{
			case KEY_ENTER:
				nextPage = true;
				break;
			case KEY_ESCAPE:
				return;
		}
	} while (!nextPage);

	// Clear the screen and reprint the logo (without the subtext)
	ClearScreen();
	PrintLogo(false);

	// Page 2 of 3 text
	cout << "Player Turn (continued)" << endl
		<< "----------------------------" << endl
		<< "Other Actions" << endl
		<< " " << (char)175 << " Build a Research Station: Discard the City card that matches the city you are in to place a research station there." << endl
		<< " " << (char)175 << " Treat Disease: Remove 1 infection marker from the city you are in. Returning it back to the disease supply." << endl
		<< " " << (char)175 << " Discover a Cure: At any research station, discard 5 City cards of the same disease from your hand to cure the disease." << endl
		<< endl
		<< "After doing 4 actions, the game will automatically draw the top 2 cards from the Player Deck." << endl
		<< endl
		<< endl
		<< "Epidemic Cards" << endl
		<< "-------------------" << endl
		<< "If your draws include any Epidemic cards, the following will immediately happen:" << endl
		<< " " << (char)175 << " Increase: The Infection Rate will increase 1 space on the infection track." << endl
		<< " " << (char)175 << " Infect: The bottom card from the Infection Deck will be drawn and infected with 3 infection markers of it's disease." << endl
		<< " " << (char)175 << " Intensify: The Infection Deck discard pile is shuffled and placed back on top of the Infection Deck draw pile." << endl
		<< endl
		<< endl
		<< "Hand Limit" << endl
		<< "---------------" << endl
		<< "If you ever have more than 9 cards in hand (after first resolving any Epidemic cards you may have drawn), discard cards" << endl
		<< "until you have 9 cards in hand." << endl
		<< endl
		<< endl
		<< "Infections" << endl
		<< "---------------" << endl
		<< "The game will draw as many Infection cards from the top of the Infection Deck as the current infection rate infecting" << endl
		<< "the city named on each card with 1 infection marker of the city's disease." << endl
		<< endl
		<< "If the city already has 3 infection markers of the disease, a 4th infection marker will not be added. Instead, an outbreak" << endl
		<< "of this disease occurs in the city (see Outbreaks on the next page)." << endl
		<< endl
		<< endl
		<< "Page 2 of 3" << endl
		<< "Press ENTER to continue or ESCAPE to return to the main menu...";

	// Do...while loop that waits for the correct keypress before continuing
	nextPage = false;
	do
	{
		switch (_getch())
		{
		case KEY_ENTER:
			nextPage = true;
			break;
		case KEY_ESCAPE:
			return;
		}
	} while (!nextPage);

	// Clear the screen and reprint the logo (without the subtext)
	ClearScreen();
	PrintLogo(false);

	// Page 3 of 3 text
	cout << "Outbreaks" << endl
		<< "--------------" << endl
		<< "When a disease outbreak occurs, the outbreaks marker forward 1 space on the Outbreaks Track. Then, 1 infection marker of" << endl
		<< "the disease will be place neighboring cities. If any of them already has 3 infection markers of the disease, a chain" << endl
		<< "reaction outbreak occurs." << endl
		<< endl
		<< "When a chain reaction outbreak occurs, the outbreaks marker forward 1 space on the Outbreaks Track per outbreak. Cities" << endl
		<< "that have already had an outbreak this round will not outbreak again." << endl
		<< endl
		<< "As a result of outbreaks, a city may have disease cubes of multiple colors on it; up to 3 cubes of each color." << endl
		<< endl
		<< endl
		<< "Turn End" << endl
		<< "-------------" << endl
		<< "After infecting cities, the round is over and you will perform 4 player actions again." << endl
		<< endl
		<< endl
		<< "Game End" << endl
		<< "-------------" << endl
		<< "The players win as soon as cures to all 4 diseases are discovered." << endl
		<< endl
		<< "There are 3 ways for the game to end and the player to lose:" << endl
		<< " " << (char)175 << " if the outbreaks marker reaches the last space of the Outbreaks Track," << endl
		<< " " << (char)175 << " if the game is unable to place the number of infection markers actually needed on the board, or " << endl
		<< " " << (char)175 << " if a player cannot draw 2 Player cards after doing his/her actions." << endl
		<< endl
		<< endl
		<< endl
		<< endl
		<< endl
		<< endl
		<< endl
		<< endl
		<< "Page 3 of 3" << endl
		<< "Press any key to return to the main menu...";

	// Switch statement that waits until a key is pressed before returning out of the function.
	switch (_getch())
	{
		default:
			return;
	}
}
