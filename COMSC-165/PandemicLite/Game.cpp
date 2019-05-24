#include <algorithm>
#include "Program.h"
#include "City.h"
#include "Disease.h"
#include "Card.h"
#include "Deck.h"
#include "BasePlayer.h"
#include "MedicRole.h"

// *******************************************************************************************
// **     Function: Game (constructor)														**
// **   Parameters: N/A																		**
// **       Return: N/A																		**
// **  Description: Initializes a Game instance.											**
// *******************************************************************************************
Game::Game()
{
	// Set the current game pointer to this game instance
	CurrentGame = this;
}

// *******************************************************************************************
// **     Function: Game (destructor)														**
// **   Parameters: N/A																		**
// **       Return: N/A																		**
// **  Description: Deletes the disease linked list nodes, city linked list nodes, player	**
// **				object, player deck object, and infect deck object.						**
// *******************************************************************************************
Game::~Game()
{
	// Disease node traversal and next node pointers
	Disease* diseaseNodePtr = diseaseLinkedList;
	Disease* diseaseNextNode = nullptr;

	// Loop through the linked list deleting each node until no more nodes exist
	while (diseaseNodePtr != nullptr)
	{
		diseaseNextNode = diseaseNodePtr->nextNode;
		delete diseaseNodePtr;
		diseaseNodePtr = diseaseNextNode;
	}

	// City node traversal and next node pointers
	City* cityNodePtr = cityLinkedList;
	City* cityNextNode = nullptr;

	// Loop through the linked list deleting each node until no more nodes exist
	while (cityNodePtr != nullptr)
	{
		cityNextNode = cityNodePtr->nextNode;
		delete cityNodePtr;
		cityNodePtr = cityNextNode;
	}

	// Delete the player, playerCardDeck, and infectionCardDeck objects
	if (player != nullptr)
	{
		delete player;
	}

	if (playerCardDeck != nullptr)
	{
		delete playerCardDeck;
	}

	if (infectionCardDeck != nullptr)
	{
		delete infectionCardDeck;
	}
}

// *******************************************************************************************
// **     Function: SetupGame																**
// **   Parameters: Options options															**
// **       Return: void																	**
// **  Description: Builds all the game objects and sets up the game instance.				**
// *******************************************************************************************
void Game::SetupGame(Options options)
{
	// Store the options parameter to a private variable.
	this->options = options;

	// Initialize random with the provided seed value or from the system time.
	srand(options.seed == 0 ? time(nullptr) : options.seed);
	
	// Set the game variables
	infectionRateIndex = 0;
	totalOutbreaks = 0;
	gameOver = false;
	reason = NA;

	// Create the Disease objects
	Disease* Blue = new Disease(options.BlueDiseaseName, BLUE_TEXT, BLUE_DISEASE, nullptr);
	Disease* Yellow = new Disease(options.YellowDiseaseName, YELLOW_TEXT, YELLOW_DISEASE, Blue);
	Disease* Purple = new Disease(options.PurpleDiseaseName, PURPLE_TEXT, PURPLE_DISEASE, Yellow);
	Disease* Red = new Disease(options.RedDiseaseName, RED_TEXT, RED_DISEASE, Purple);
	diseaseLinkedList = Blue;

	// Create the City objects
	// Blue Disease Cities
	City* SanFrancisco = new City("San Francisco", BLUE_TEXT, Blue, nullptr);
	City* Chicago = new City("Chicago", BLUE_TEXT, Blue, SanFrancisco);
	City* Atlanta = new City("Atlanta", BLUE_TEXT, Blue, Chicago);
	City* Montreal = new City("Montreal", BLUE_TEXT, Blue, Atlanta);
	City* Washington = new City("Washington", BLUE_TEXT, Blue, Montreal);
	City* NewYork = new City("New York", BLUE_TEXT, Blue, Washington);
	City* London = new City("London", BLUE_TEXT, Blue, NewYork);
	City* Madrid = new City("Madrid", BLUE_TEXT, Blue, London);
	City* Paris = new City("Paris", BLUE_TEXT, Blue, Madrid);
	City* Essen = new City("Essen", BLUE_TEXT, Blue, Paris);
	City* Milan = new City("Milan", BLUE_TEXT, Blue, Essen);
	City* StPetersburg = new City("St. Petersburg", BLUE_TEXT, Blue, Milan);

	// Yellow Disease Cities
	City* LosAngeles = new City("Los Angeles", YELLOW_TEXT, Yellow, StPetersburg);
	City* MexicoCity = new City("Mexico City", YELLOW_TEXT, Yellow, LosAngeles);
	City* Miami = new City("Miami", YELLOW_TEXT, Yellow, MexicoCity);
	City* Bogota = new City("Bogota", YELLOW_TEXT, Yellow, Miami);
	City* Lima = new City("Lima", YELLOW_TEXT, Yellow, Bogota);
	City* Santiago = new City("Santiago", YELLOW_TEXT, Yellow, Lima);
	City* SaoPaulo = new City("Sao Paulo", YELLOW_TEXT, Yellow, Santiago);
	City* BuenosAires = new City("Buenos Aires", YELLOW_TEXT, Yellow, SaoPaulo);
	City* Lagos = new City("Lagos", YELLOW_TEXT, Yellow, BuenosAires);
	City* Kinshasa = new City("Kinshasa", YELLOW_TEXT, Yellow, Lagos);
	City* Johannesburg = new City("Johannesburg", YELLOW_TEXT, Yellow, Kinshasa);
	City* Khartoum = new City("Khartoum", YELLOW_TEXT, Yellow, Johannesburg);

	// Purple Disease Cities
	City* Algiers = new City("Algiers", PURPLE_TEXT, Purple, Khartoum);
	City* Cairo = new City("Cairo", PURPLE_TEXT, Purple, Algiers);
	City* Istanbul = new City("Istanbul", PURPLE_TEXT, Purple, Cairo);
	City* Moscow = new City("Moscow", PURPLE_TEXT, Purple, Istanbul);
	City* Tehran = new City("Tehran", PURPLE_TEXT, Purple, Moscow);
	City* Baghdad = new City("Baghdad", PURPLE_TEXT, Purple, Tehran);
	City* Riyadh = new City("Riyadh", PURPLE_TEXT, Purple, Baghdad);
	City* Karachi = new City("Karachi", PURPLE_TEXT, Purple, Riyadh);
	City* Mumbai = new City("Mumbai", PURPLE_TEXT, Purple, Karachi);
	City* Delhi = new City("Delhi", PURPLE_TEXT, Purple, Mumbai);
	City* Chennai = new City("Chennai", PURPLE_TEXT, Purple, Delhi);
	City* Kolkata = new City("Kolkata", PURPLE_TEXT, Purple, Chennai);

	// Red Disease Cities
	City* Beijing = new City("Beijing", RED_TEXT, Red, Kolkata);
	City* Seoul = new City("Seoul", RED_TEXT, Red, Beijing);
	City* Shanghai = new City("Shanghai", RED_TEXT, Red, Seoul);
	City* Tokyo = new City("Tokyo", RED_TEXT, Red, Shanghai);
	City* HongKong = new City("Hong Kong", RED_TEXT, Red, Tokyo);
	City* Taipei = new City("Taipei", RED_TEXT, Red, HongKong);
	City* Osaka = new City("Osaka", RED_TEXT, Red, Taipei);
	City* Bangkok = new City("Bangkok", RED_TEXT, Red, Osaka);
	City* Jakarta = new City("Jakarta", RED_TEXT, Red, Bangkok);
	City* HoChiMinhCity = new City("Ho Chi Minh City", RED_TEXT, Red, Jakarta);
	City* Manila = new City("Manila", RED_TEXT, Red, HoChiMinhCity);
	City* Sydney = new City("Sydney", RED_TEXT, Red, Manila);
	cityLinkedList = SanFrancisco;

	// Set Neighbors
	// Blue Disease Cities
	SanFrancisco->setNeighbors({ Chicago, LosAngeles, Manila, Tokyo });
	Chicago->setNeighbors({ SanFrancisco, Montreal, Atlanta, MexicoCity, LosAngeles });
	Atlanta->setNeighbors({ Chicago, Washington, Miami });
	Montreal->setNeighbors({ Chicago, NewYork, Washington });
	Washington->setNeighbors({ Atlanta, Montreal, NewYork, Miami });
	NewYork->setNeighbors({ Washington, Montreal, London, Madrid });
	London->setNeighbors({ NewYork, Essen, Paris, Madrid });
	Madrid->setNeighbors({ NewYork, London, Paris, Algiers, SaoPaulo });
	Paris->setNeighbors({ Madrid, London, Essen, Milan, Algiers });
	Essen->setNeighbors({ London, Paris, StPetersburg, Milan });
	Milan->setNeighbors({ Paris, Essen, Istanbul });
	StPetersburg->setNeighbors({ Essen, Moscow, Istanbul });

	// Yellow Disease Cities
	LosAngeles->setNeighbors({ MexicoCity, SanFrancisco, Chicago, Sydney });
	MexicoCity->setNeighbors({ LosAngeles, Miami, Bogota, Lima, Chicago });
	Miami->setNeighbors({ Bogota, MexicoCity, Atlanta, Washington });
	Bogota->setNeighbors({ MexicoCity, Miami, SaoPaulo, BuenosAires, Lima });
	Lima->setNeighbors({ MexicoCity, Bogota, Santiago });
	Santiago->setNeighbors({ Lima });
	SaoPaulo->setNeighbors({ BuenosAires, Bogota, Lagos, Madrid });
	BuenosAires->setNeighbors({ Bogota, SaoPaulo });
	Lagos->setNeighbors({ SaoPaulo, Kinshasa, Khartoum });
	Kinshasa->setNeighbors({ Lagos, Khartoum, Johannesburg });
	Johannesburg->setNeighbors({ Kinshasa, Khartoum });
	Khartoum->setNeighbors({ Johannesburg, Kinshasa, Lagos, Cairo });

	// Purple Disease Cities
	Algiers->setNeighbors({ Istanbul, Cairo, Madrid, Paris });
	Cairo->setNeighbors({ Algiers, Istanbul, Baghdad, Riyadh, Khartoum });
	Istanbul->setNeighbors({ Moscow, Baghdad, Cairo, Algiers, Milan, StPetersburg });
	Moscow->setNeighbors({ Tehran, Istanbul, StPetersburg });
	Tehran->setNeighbors({ Delhi, Karachi, Baghdad, Moscow });
	Baghdad->setNeighbors({ Tehran, Karachi, Riyadh, Cairo, Istanbul });
	Riyadh->setNeighbors({ Cairo, Baghdad, Karachi });
	Karachi->setNeighbors({ Riyadh, Baghdad, Tehran, Delhi, Mumbai });
	Mumbai->setNeighbors({ Karachi, Delhi, Chennai });
	Delhi->setNeighbors({ Kolkata, Chennai, Mumbai, Karachi, Tehran });
	Chennai->setNeighbors({ Mumbai, Delhi, Kolkata, Bangkok, Jakarta });
	Kolkata->setNeighbors({ Delhi, Chennai, Bangkok, HongKong });

	// Red Disease Cities
	Beijing->setNeighbors({ Seoul, Shanghai });
	Seoul->setNeighbors({ Beijing, Shanghai, Tokyo });
	Shanghai->setNeighbors({ Beijing, Seoul, Tokyo, Taipei, HongKong });
	Tokyo->setNeighbors({ Seoul, Shanghai, Osaka, SanFrancisco });
	HongKong->setNeighbors({ Shanghai, Taipei, Manila, HoChiMinhCity, Bangkok, Kolkata });
	Taipei->setNeighbors({ Manila, HongKong, Shanghai, Osaka });
	Osaka->setNeighbors({ Taipei, Tokyo });
	Bangkok->setNeighbors({ HongKong, HoChiMinhCity, Jakarta, Chennai, Kolkata });
	Jakarta->setNeighbors({ Bangkok, HoChiMinhCity, Sydney, Chennai });
	HoChiMinhCity->setNeighbors({ Jakarta, Bangkok, HongKong, Manila });
	Manila->setNeighbors({ Sydney, HoChiMinhCity, HongKong, Taipei, SanFrancisco });
	Sydney->setNeighbors({ Jakarta, Manila, LosAngeles });

	// Clear the screen and display the introduction
	ClearScreen();
	cout << "The world is falling apart. Four diseases are sweeping the planet and you are on the front lines. We've identified the" << endl;
	cout << "following nine cities as the origin of the infections. Travel the world helping to treat the diseases and gather samples" << endl;
	cout << "to help discover cures. Can you save humanity before it becomes a world wide pandemic?" << endl << endl;

	// Initialize the infection card deck from the city linked list
	infectionCardDeck = new Deck<InfectionCard>(cityLinkedList, getInfectionRate());

	// Infect the first nine cities to start the game.
	for(int initialInfection = 0; initialInfection < 9; ++initialInfection)
	{
		// The infection rate is 3 for the first 3 cities, 2 for the second 3 cities, and 1 for the final three cities.
		int infectionRate = 1;
		if (initialInfection < 3)
		{
			infectionRate = 3;
		}
		else if (initialInfection < 6)
		{
			infectionRate = 2;
		}

		// Draw the card from the infection deck, perform the action of infecting the city with the correct number of infection markers, and discard the card.
		InfectionCard Card = infectionCardDeck->draw(true);
		Card.DrawAction(infectionRate);
		infectionCardDeck->discard(Card);
	}

	// Pause the screen to allow the player to read the intro message and initial infection.
	GamePauseUntilKeyPress("Enter", KEY_ENTER);

	// Create the player instance from the MedicRole derived class (currently the only role available)
	player = new MedicRole("Medic", Atlanta);

	// Initialize the player card deck from the city linked list.
	playerCardDeck = new Deck<PlayerCard>(cityLinkedList, 2);

	// Draw five cards into the player's hand
	for (int initialHand = 0; initialHand < 5; ++initialHand)
	{
		player->AddPlayerCardToHand(playerCardDeck->draw(true));
	}

	// Prepare the rest of the player deck (adding epidemics) and shuffle
	PlayerCard::PreparePlayerDeck(playerCardDeck);

	// Draw the game screen
	DrawGameScreen();
}

// *******************************************************************************************
// **     Function: Play																	**
// **   Parameters: N/A																		**
// **       Return: bool																	**
// **  Description: The game play loop. Runs as long as the player hasn't won/lost the		**
// **				game. Returns true to play again or false to return to the main menu.	**
// *******************************************************************************************
bool Game::Play()
{
	// Do... while loop that will cause the game loop to run as long as the win/loss condition hasn't been triggered.
	do
	{
		// Loop once per action for the player.
		for (int ActionNumber = 0; ActionNumber < player->getMaxActions() && !gameOver; ++ActionNumber)
		{
			// Set the default return value to false.
			// NOTE: Returning false from any Action will make the Action not count against the players available actions this turn.
			bool ret = false;

			do
			{
				// Call the getAvailableActions and print out a list of the actions available to the player at the moment.
				vector<string> AvailableActions = player->getAvailableActions();
				cout << "Action " << ActionNumber + 1 << " of " << player->getMaxActions() << endl;
				cout << "------------------" << endl;

				// Variable that stores the corresponding (zero-based) menu option number.
				int selectionIndex = -1;

				// Loop through each of the available actions listing each one out with a number.
				for (string Action : AvailableActions)
				{
					++selectionIndex;
					cout << (selectionIndex + 1) << ": " << Action << endl;
				}

				// Prompt the user for input using the GetNumericInput.
				int userSelection = GetNumericInput(1, selectionIndex + 1, true, true);

				// The last option is always "Pass", so if the value entered by the user is the last option on the list we are skipping the rest of the actions this turn.
				if (userSelection == selectionIndex)
				{
					// Set the ActionNumber variable from the For loop to the max value, redraw the scren, and break.
					ActionNumber = player->getMaxActions();
					DrawGameScreen();
					break;
				}

				// Redraw the screen and call the DoPlayerAction function.
				DrawGameScreen();
				cout << "Action " << ActionNumber + 1 << " of " << player->getMaxActions() << endl;
				cout << "------------------" << endl;
				ret = DoPlayerAction(player, AvailableActions[userSelection]);

				// Check the win condition of all diseases being cured by iterating through the linked list and storing the isCured value in an array.
				int iteration = 0;
				bool allDiseasesCured[4] = { false, false, false, false };
				Disease* disease = diseaseLinkedList;
				while(disease != nullptr)
				{
					allDiseasesCured[iteration] = disease->getIsCured();
					disease = disease->nextNode;
					++iteration;
				}

				// Check the array and if all values are turn the call EndGame with the WIN argument.
				if (allDiseasesCured[0] && allDiseasesCured[1] && allDiseasesCured[2] && allDiseasesCured[3])
				{
					EndGame(GameOverReason::WIN);
				}

				// Redraw the screen.
				DrawGameScreen();
			} while (!gameOver && !ret);			// Loop here in case the action returns a false (meaning it doesn't count against the max actions this turn) or GameOver is triggered.
		}

		// Loop through the drawing cards from the player deck until it reaches the draw count or game over occurs.
		for (int PlayerDeckDraw = 0; PlayerDeckDraw < playerCardDeck->getDrawCount() && !gameOver; ++PlayerDeckDraw)
		{
			cout << "Player Deck draw " << PlayerDeckDraw + 1 << " of " << playerCardDeck->getDrawCount() << endl;
			cout << "----------------------------" << endl;

			// Check if the player card deck is empty. If not, then draw cards from the player deck.
			if (!playerCardDeck->isEmpty())
			{
				PlayerCard card = playerCardDeck->draw();

				// If the cards is not an epidemic add it to the player hand.
				if (!card.getIsEpidemic())
				{
					player->AddPlayerCardToHand(card);
				}

				// Pause the screen to allow the player to read the card information and then redraw the screen.
				GamePauseUntilKeyPress("Enter", KEY_ENTER);
				DrawGameScreen();

				// While loop for discarding cards if the player hand is at or above the maximum allowable quantity
				while (player->isPlayerHandAtMax())
				{
					cout << "You have too many cards in your player hand (maximum " + to_string(player->getMaxCardsInHand()) + ")." << endl;
					cout << "Please select the card below that you would like to discard:" << endl;

					// Variable that stores the corresponding (zero-based) menu option number.
					int selectionIndex = -1;
					vector<PlayerCard*> cards = player->getPlayerHandCards();

					// Loop through each of the player's cards listing each one out with a number.
					for(PlayerCard* card : cards)
					{
						++selectionIndex;
						cout << (selectionIndex + 1) << ": " << card->getName() << endl;
					}

					// Prompt the user for input using the GetNumericInput.
					int userSelection = GetNumericInput(1, selectionIndex + 1, true, true);

					// Discard the selected card from the hand and redraw the screen.
					player->DiscardCardFromHand(cards[userSelection]);
					DrawGameScreen();
				}
			}
			else
			{
				// If the player deck has run out of cards then the player has lost the game. Call the EndGame function with the appropriate argument.
				EndGame(GameOverReason::LOSS_PLAYERDECKEMPTY);
			}
		}

		// Loop through the drawing cards from the infection deck
		for (int InfectionDeckDraw = 0; InfectionDeckDraw < getInfectionRate() && !gameOver; ++InfectionDeckDraw)
		{
			cout << "Infection Deck draw " << InfectionDeckDraw + 1 << " of " << getInfectionRate() << endl;
			cout << "-------------------------------" << endl;

			// Draw the infection card (this will trigger the DrawAction) and then discard the card.
			InfectionCard card = infectionCardDeck->draw();
			infectionCardDeck->discard(card);

			// Pause the screen to allow the player to read the card information and then redraw the screen.
			GamePauseUntilKeyPress("Enter", KEY_ENTER);
			DrawGameScreen();
		}
	} while (!gameOver);			// Loop until the game is marked as over.

	// Pointer variable to the disease linked list node.
	Disease* diseaseNodePtr = diseaseLinkedList;

	// Switch statement to output the corresponding game win/loss stament.
	switch(reason)
	{
		case WIN:
			cout << "Congratulations! You have saved humanity this time... But can you do it again?" << endl;
			break;
		case LOSS_INFECTIONMARKERS:
			while (diseaseNodePtr->nextNode != nullptr)
			{
				if (diseaseNodePtr->getRemainingInfectionCount() == 0)
				{
					break;
				}
				diseaseNodePtr = diseaseNodePtr->nextNode;
			}
			cout << "The " << *diseaseNodePtr << " disease has started to overrun the populate. You have failed to save humanity...\nWant to play again?" << endl;
			break;
		case LOSS_OUTBREAKS:
			cout << "Due to the large number of outbreaks the four diseases have overrun the populate. You have failed to save humanity...\nWant to play again?" << endl;
			break;
		case LOSS_PLAYERDECKEMPTY:
			cout << "You have ran out of time. The four diseases have spread too far to contain. You have failed to save humanity...\nWant to play again?" << endl;
			break;
	}

	// Prompt the player if he/she wants to play again.
	cout << endl << "Please press the ENTER key to play again or ESCAPE to return to the Main Menu...";
	do
	{
		switch(_getch())
		{
			case KEY_ENTER:
				return true;
			case KEY_ESCAPE:
				return false;
		}
	} while (true);
}

// *******************************************************************************************
// **     Function: DoPlayerAction															**
// **   Parameters: BasePlayer* player														**
// **				string &action															**
// **       Return: bool																	**
// **  Description: Calls the player's action based off of the input action string.			**
// *******************************************************************************************
bool Game::DoPlayerAction(BasePlayer* player, string &action)
{
	// Set the default return value to false.
	// NOTE: Returning false from any Action will make the Action not count against the players available actions this turn.
	bool ret = false;

	// Check the input string vs the known menu option string and call the appropriate player action.
	// NOTE: This has to be an if...else if...else statement because switch needs a constant input value to work.
	if (action == "Drive/Ferry")
	{
		ret = player->DriveFerry();
	}
	else if (action == "Direct Flight")
	{
		ret = player->DirectFlight();
	}
	else if (action == "Charter Flight")
	{
		ret = player->CharterFlight();
	}
	else if (action == "Shuttle Flight")
	{
		ret = player->ShuttleFlight();
	}
	else if (action == "Build a Research Station")
	{
		ret = player->BuildResearchStation();
	}
	else if (action == "Treat Disease")
	{
		ret = player->TreatDisease();
	}
	else if (action == "Discover a Cure")
	{
		ret = player->DiscoverCure();
	}
	return ret;
}

// *******************************************************************************************
// **     Function: getGameOptions															**
// **   Parameters: N/A																		**
// **       Return: Game::Options															**
// **  Description: Returns the 'options' private variable value.							**
// *******************************************************************************************
Game::Options Game::getGameOptions() const
{
	return options;
}

// *******************************************************************************************
// **     Function: getCityLinkedList														**
// **   Parameters: N/A																		**
// **       Return: City*																	**
// **  Description: Returns the 'cityLinkedList' private variable value.					**
// *******************************************************************************************
City* Game::getCityLinkedList() const
{
	return cityLinkedList;
}

// *******************************************************************************************
// **     Function: getDiseaseLinkedList													**
// **   Parameters: N/A																		**
// **       Return: Disease*																**
// **  Description: Returns the 'diseaseLinkedList' private variable value.					**
// *******************************************************************************************
Disease* Game::getDiseaseLinkedList() const
{
	return diseaseLinkedList;
}

// *******************************************************************************************
// **     Function: getInfectionRate														**
// **   Parameters: N/A																		**
// **       Return: int																		**
// **  Description: Returns the infection rate value.										**
// *******************************************************************************************
int Game::getInfectionRate() const
{
	return INFECTIONRATE[infectionRateIndex];
}

// *******************************************************************************************
// **     Function: getInfectionRateIndex													**
// **   Parameters: N/A																		**
// **       Return: int																		**
// **  Description: Returns the 'infectionRateIndex' private variable value.				**
// *******************************************************************************************
int Game::getInfectionRateIndex() const
{
	return infectionRateIndex;
}

// *******************************************************************************************
// **     Function: getPlayer																**
// **   Parameters: N/A																		**
// **       Return: BasePlayer*																**
// **  Description: Returns the 'player' private variable value.							**
// *******************************************************************************************
BasePlayer* Game::getPlayer() const
{
	return player;
}

// *******************************************************************************************
// **     Function: getMaxOutbreaks															**
// **   Parameters: N/A																		**
// **       Return: int																		**
// **  Description: Returns the 'MAXOUTBREAKS' private constant value.						**
// *******************************************************************************************
int Game::getMaxOutbreaks() const
{
	return MAXOUTBREAKS;
}

// *******************************************************************************************
// **     Function: getMaxResearchStations													**
// **   Parameters: N/A																		**
// **       Return: int																		**
// **  Description: Returns the 'MAXRESEARCHSTATIONS' private constant value.				**
// *******************************************************************************************
int Game::getMaxResearchStations() const
{
	return MAXRESEARCHSTATIONS;
}

// *******************************************************************************************
// **     Function: getResearchStationCount													**
// **   Parameters: N/A																		**
// **       Return: int																		**
// **  Description: Returns the count of research stations build in cities.					**
// *******************************************************************************************
int Game::getResearchStationCount() const
{
	int ret = 0;
	City* nodePtr = cityLinkedList;
	while (nodePtr != nullptr)
	{
		if (nodePtr->hasResearchStation())
		{
			++ret;
		}
		nodePtr = nodePtr->nextNode;
	}
	return ret;
}

// *******************************************************************************************
// **     Function: getTotalOutbreaks														**
// **   Parameters: N/A																		**
// **       Return: int																		**
// **  Description: Returns the 'totalOutbreaks' private variable value.					**
// *******************************************************************************************
int Game::getTotalOutbreaks() const
{
	return totalOutbreaks;
}

// *******************************************************************************************
// **     Function: IncrementInfectionRate													**
// **   Parameters: N/A																		**
// **       Return: int																		**
// **  Description: Increments the infection rate and returns the new infection rate.		**
// *******************************************************************************************
int Game::IncrementInfectionRate()
{
	if (infectionRateIndex < INFECTIONRATESIZE)
	{
		++infectionRateIndex;
	}
	return getInfectionRate();
}

// *******************************************************************************************
// **     Function: IncrementOutbreaks														**
// **   Parameters: N/A																		**
// **       Return: int																		**
// **  Description: Increments the total outbreaks and returns the new value.				**
// *******************************************************************************************
int Game::IncrementOutbreaks()
{
	return ++totalOutbreaks;
}

// *******************************************************************************************
// **     Function: DrawPlayerCard															**
// **   Parameters: N/A																		**
// **       Return: PlayerCard																**
// **  Description: Draws a player card from the top of the Player Card deck.				**
// *******************************************************************************************
PlayerCard Game::DrawPlayerCard() const
{
	return playerCardDeck->draw();
}

// *******************************************************************************************
// **     Function: DiscardPlayerCard														**
// **   Parameters: PlayerCard card															**
// **       Return: bool																	**
// **  Description: Discards a player card to the Player Card Deck discard pile.			**
// *******************************************************************************************
bool Game::DiscardPlayerCard(PlayerCard card) const
{
	return playerCardDeck->discard(card);
}

// *******************************************************************************************
// **     Function: DrawBottomInfectionCard													**
// **   Parameters: N/A																		**
// **       Return: City*																	**
// **  Description: Draws the bottom Infection Card, infects the city, and discards it.		**
// **				Returns a pointer to the newly infected city.							**
// *******************************************************************************************
City* Game::DrawBottomInfectionCard()
{
	// Create an empty city pointer for return.
	City* ret;

	// Draw the bottom card and infect it with three infection markers of it's primary disease.
	InfectionCard Card = infectionCardDeck->drawBottom(true);
	Card.DrawAction(3);

	// Set the return value, discard the card into the Infection Card deck's discard pile, and return.
	ret = Card.getCity();
	infectionCardDeck->discard(Card);
	return ret;
}

// *******************************************************************************************
// **     Function: IntensifyInfectionDeck													**
// **   Parameters: N/A																		**
// **       Return: bool																	**
// **  Description: Shuffles the Infection Card discard pile and adds it back to the draw	**
// **				pile.																	**
// *******************************************************************************************
bool Game::IntensifyInfectionDeck()
{
	// Set the default return value to false.
	bool ret = false;

	// Shuffle the Infection Card discard pile
	infectionCardDeck->shuffle(Deck<InfectionCard>::Discard);

	// Loop through the Infection Card discard pile and draw a card from the discard pile, discard in the draw pile, and set the return value to true.
	while(!infectionCardDeck->isEmpty(Deck<InfectionCard>::Discard))
	{
		InfectionCard card = infectionCardDeck->draw(true, Deck<InfectionCard>::Discard);
		infectionCardDeck->discard(card, Deck<InfectionCard>::Draw);
		ret = true;
	}

	return ret;
}

// *******************************************************************************************
// **     Function: EndGame																	**
// **   Parameters: GameOverReason reason													**
// **       Return: void																	**
// **  Description: Set the 'gameOver' private variable value to true and set the game over	**
// **				reason.																	**
// *******************************************************************************************
void Game::EndGame(GameOverReason reason)
{
	gameOver = true;
	this->reason = reason;
}

// *******************************************************************************************
// **     Function: DrawGameScreen															**
// **   Parameters: N/A																		**
// **       Return: void																	**
// **  Description: Draws the screen including cities, disease information, infection		**
// **				track, outbreak track, and cards in player hand.						**
// *******************************************************************************************
void Game::DrawGameScreen() const
{
	// Clear the screen for redraw.
	ClearScreen();

	// First let's write all the cities from the cityLinkedList to the screen.
	int y = 2;
	City* cityNodePtr = CurrentGame->getCityLinkedList();
	for (int city = 0; city < 48; ++city)
	{
		// Position information. For the first 24 cities we are setting the x-coord to 8 and the rest 46. Set the y-coord value based off of the current iteration and reset when it's the 24th iteration.
		int x = city < 24 ? 8 : 46;
		y = city == 24 ? 3 : ++y;

		// Move the printing "I" bar to the correct position on the screen.
		PrintAtScreenPosition("", x, y, DEFAULT, false);

		// Call the print function from the City node with the arguments to show if the player is at that location, if it has a research station, and print the infection markers.
		cityNodePtr->print(false, cityNodePtr == CurrentGame->getPlayer()->getPlayerLocation(), true, true);
		cout << endl;

		// Advance the node traversal pointer.
		cityNodePtr = cityNodePtr->nextNode;
	}

	// Next let's print out the disease information.
	Disease* diseaseNodePtr = diseaseLinkedList;
	for (int disease = 0; disease < 4; ++disease)
	{
		// Position information. The x-coord is constant and the y-coord value is based off the iteration + 3;
		int x = 80;
		y = disease + 3;

		// Move the printing "I" bar to the correct position on the screen.
		PrintAtScreenPosition("", x, y, DEFAULT, false);

		// Call the print function from the disease with the arguments to show the disease name, print one infection marker, print if it has been cured, and print the remaining infection markers.
		diseaseNodePtr->print(true, 1, true, true);
		cout << endl;

		// Advance the node traversal pointer.
		diseaseNodePtr = diseaseNodePtr->nextNode;
	}

	// Infection tracker
	PrintAtScreenPosition("Infection Tracker: 2 2 2 3 3 4 4", 84, 9, DEFAULT, false);
	PrintAtScreenPosition(to_string(getInfectionRate()), 103 + (2 * getInfectionRateIndex()), 9, SELECTED_TEXT, false);

	// Outbreak tracker
	PrintAtScreenPosition("Outbreak Tracker: 0 1 2 3 4 5 6 7 8", 84, 10, DEFAULT, false);
	PrintAtScreenPosition(to_string(getTotalOutbreaks()), 102 + (2 * getTotalOutbreaks()), 10, SELECTED_TEXT, false);

	// Print the cards in the players hand.
	PrintAtScreenPosition("Cards In Hand (max " + to_string(player->getMaxCardsInHand()) + ")", 84, 13, DEFAULT, false);
	PrintAtScreenPosition("--------------------------", 84, 14, DEFAULT, false);
	vector<PlayerCard*> playerCard = player->getPlayerHandCards();
	for (int card = 0; card < playerCard.size(); ++card)
	{
		// Position information. The x-coord is constant and the y-coord value is based off the iteration + 15;
		int x = 82;
		y = card + 15;

		// Move the printing "I" bar to the correct position on the screen.
		PrintAtScreenPosition("", x, y, DEFAULT, false);

		// Call the print function from the associated city with no arguments (this will just print the name of the city formatted with it's color).
		playerCard[card]->getCity()->print();
		cout << endl;
	}

	// Move the printing "I" bar to the position on the screen for other text to be written later.
	PrintAtScreenPosition("", 0, 30, DEFAULT, false);
}

// *******************************************************************************************
// **     Function: GetCurrentGame															**
// **   Parameters: N/A																		**
// **       Return: Game*																	**
// **  Description: Returns the 'CurrentGame' pointer variable from the Program header/cpp.	**
// *******************************************************************************************
Game* GetCurrentGame()
{
	return CurrentGame;
}

// *******************************************************************************************
// **     Function: GetStringInput															**
// **   Parameters: string prompt															**
// **       Return: string																	**
// **  Description: Prompts the user for a string input and returns their input.			**
// *******************************************************************************************
string GetStringInput(string prompt)
{
	string userInput;
	cout << prompt << ": ";
	getline(cin, userInput);
	return userInput;
}

// *******************************************************************************************
// **     Function: GetDestinationFromInputString											**
// **   Parameters: City* destination														**
// **				string &input															**
// **       Return: bool																	**
// **  Description: Requires the user to type in a destination. Returns true if the			**
// **				if the destination is valid and sets on the reference argument			**
// **				variable, if false then the user specified 'back' to return to the		**
// **				previous menu.															**
// *******************************************************************************************
bool GetDestinationFromInputString(City* &destination, string &userInput)
{
	// Set the default return value to false and call the GetStringInput function.
	bool ret = false;

	prompt:
	userInput = GetStringInput("Please enter a destination, or type 'back' to return to the Action menu");

	// Check if the user enter 'back'. If so, then return the function with a false.
	if (ToLower(userInput) != "back")
	{
		// Traverse the city linked list nodes to find a matching city.
		City* currentNode = CurrentGame->getCityLinkedList();
		while (currentNode != nullptr)
		{
			if (ToLower(currentNode->getName()) == ToLower(userInput))
			{
				destination = currentNode;
				ret = true;
				break;
			}
			currentNode = currentNode->nextNode;
		}

		// If a matching city wasn't found goto prompt to reprompt the user for input.
		if(ret == false)
		{
			goto prompt;
		}
	}
	return ret;
}

// *******************************************************************************************
// **     Function: GetCitiesContainingResearchStations										**
// **   Parameters: City* excludeCurrentCity												**
// **       Return: bool																	**
// **  Description: Returns cities that have research stations (excluding the argument).	**
// *******************************************************************************************
vector<City*> GetCitiesContainingResearchStations(City* excludeCurrentCity)
{
	// Create a vector of city pointers for return.
	vector<City*> ret;

	// Traverse the city linked list.
	City* currentCity = CurrentGame->getCityLinkedList();
	while (currentCity != nullptr)
	{
		// Check if the current city node has a research station and itn't the excluded city.  If so, add it to the return vector of city pointers.
		if (currentCity->hasResearchStation() && currentCity != excludeCurrentCity)
		{
			ret.push_back(currentCity);
		}
		currentCity = currentCity->nextNode;
	}
	return ret;
}

// *******************************************************************************************
// **     Function: GetNumericInput															**
// **   Parameters: int minValue (optional) [Default = INT_MIN]								**
// **				int maxValue (optional) [Default = INT_MAX]								**
// **				bool NonNegative (optional) [Default = true]							**
// **				bool ReturnZeroBased (optional) [Default = false]						**
// **       Return: int																		**
// **  Description: Prompts the user for an int input and returns their input if it matches	**
// **				the arguments criteria. If not, it will reprompt until valid.			**
// *******************************************************************************************
int GetNumericInput(int minValue, int maxValue, bool NonNegative, bool ReturnZeroBased)
{
	// Set the default return value to 0 and create a userInput string for getline.
	int ret = 0;
	string userInput;

	// Loop prompting the user to input an int value. If it doesn't match the input criterai, loop until it does.
	do
	{
		cout << "Please enter a value" << (minValue == INT_MIN && maxValue == INT_MAX ? (NonNegative ? " [non-negative]: " : ": ") : " [" + to_string(minValue) + "-" + to_string(maxValue) + "]: ");
		getline(cin, userInput);
	} while (!(IsNumeric(userInput, ret, NonNegative) && (minValue == INT_MIN || ret >= minValue) && (maxValue == INT_MAX || ret <= maxValue)));
	return ReturnZeroBased ? ret - 1 : ret;
}

// *******************************************************************************************
// **     Function: GetNumericInput															**
// **   Parameters: string &input															**
// **				int &output																**
// **				bool NonNegative (optional) [Default = true]							**
// **       Return: bool																	**
// **  Description: Takes the input value and checks if it is numeric and returns if it		**
// **				is. Additionally, it stores the converted int value in the output		**
// **				reference variable.														**
// *******************************************************************************************
bool IsNumeric(string &input, int &output, bool NonNegative)
{
	// Set the default return value to true
	bool ret = true;

	// If the size of the input is not zero let's check it.
	if (input.size() != 0)
	{
		// Loop character by character checking it it is a digit.
		for (char character : input)
		{
			// If it's not a digit and not non-negative (including the '-' symbol) set the return value to false.
			if (!isdigit(character) && (NonNegative || character != '-'))
			{
				ret = false;
				break;
			}
		}

		// Set the output variable to INT_MIN (used if we return false)
		output = INT_MIN;

		// If the input is a number convert it to an int and store it in the output reference variable.
		if (ret)
		{
			output = stoi(input);
		}
	}
	return ret;
}

// *******************************************************************************************
// **     Function: ToLower																	**
// **   Parameters: string input															**
// **       Return: string																	**
// **  Description: Returns the string in lowercase.										**
// *******************************************************************************************
string ToLower(string input)
{
	string ret = input;
	transform(input.begin(), input.end(), ret.begin(), ::tolower);
	return ret;
}

// *******************************************************************************************
// **     Function: ToUpper																	**
// **   Parameters: string input															**
// **       Return: string																	**
// **  Description: Returns the string in uppercase.										**
// *******************************************************************************************
string ToUpper(string input)
{
	string ret = input;
	transform(input.begin(), input.end(), ret.begin(), ::toupper);
	return ret;
}

// *******************************************************************************************
// **     Function: GamePauseUntilKeyPress													**
// **   Parameters: string keyname															**
// **				WORD key																**
// **       Return: void																	**
// **  Description: Cause the application to wait until a key is pressed.					**
// *******************************************************************************************
void GamePauseUntilKeyPress(string keyname, WORD key)
{
	cout << endl << "Please press the " << ToUpper(keyname) << " to continue...";
	while(_getch() != key)
	{
		// Nothing to do here, just go back to the while test line and wait until the correct key is pressed.
	}
}
