#include <algorithm>
#include "Program.h"
#include "City.h"
#include "Disease.h"
#include "Card.h"
#include "Deck.h"
#include "BasePlayer.h"
#include "MedicRole.h"

Game::Game()
{
	// Set the current game pointer to this game instance
	CurrentGame = this;
}

Game::~Game()
{
	Disease* diseaseNodePtr = diseaseLinkedList;
	Disease* diseaseNextNode = nullptr;
	while (diseaseNodePtr != nullptr)
	{
		diseaseNextNode = diseaseNodePtr->nextNode;
		delete diseaseNodePtr;
		diseaseNodePtr = diseaseNextNode;
	}

	City* cityNodePtr = cityLinkedList;
	City* cityNextNode = nullptr;
	while (cityNodePtr != nullptr)
	{
		cityNextNode = cityNodePtr->nextNode;
		delete cityNodePtr;
		cityNodePtr = cityNextNode;
	}

	delete player;
	delete playerCardDeck;
	delete infectionCardDeck;
}

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

	// Create the City* objects
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

	ClearScreen();
	cout << "The world is falling apart. Four diseases are sweeping the planet and you are on the front lines. We've identified the" << endl;
	cout << "following nine cities as the origin of the infections. Travel the world helping to treat the diseases and gather samples" << endl;
	cout << "to help discover cures. Can you save humanity before it becomes a world wide pandemic?" << endl << endl;

	infectionCardDeck = new Deck<InfectionCard>(cityLinkedList, getInfectionRate());
	for(int initialInfection = 0; initialInfection < 9; ++initialInfection)
	{
		int infectionRate = 1;
		if (initialInfection < 3)
		{
			infectionRate = 3;
		}
		else if (initialInfection < 6)
		{
			infectionRate = 2;
		}

		InfectionCard Card = infectionCardDeck->draw(true);
		Card.DrawAction(infectionRate);
		infectionCardDeck->discard(Card);
	}

	GamePauseUntilKeyPress("Enter", KEY_ENTER);

	player = new MedicRole("Medic", Atlanta);
	playerCardDeck = new Deck<PlayerCard>(cityLinkedList, 2);
	for (int initialHand = 0; initialHand < 5; ++initialHand)
	{
		player->AddPlayerCardToHand(playerCardDeck->draw(true));
	}
	PlayerCard::PreparePlayerDeck(playerCardDeck);

	DrawGameScreen();
}

bool Game::Play()
{
	do
	{
		for (int ActionNumber = 0; ActionNumber < player->getMaxActions() && !gameOver; ++ActionNumber)
		{
			bool ret = false;
			do
			{
				vector<string> AvailableActions = player->getAvailableActions();
				cout << "Action " << ActionNumber + 1 << " of " << player->getMaxActions() << endl;
				cout << "------------------" << endl;
				int selectionIndex = -1;
				for (string Action : AvailableActions)
				{
					++selectionIndex;
					cout << (selectionIndex + 1) << ": " << Action << endl;
				}

				int userSelection = GetNumericInput(1, selectionIndex + 1, true, true);
				if (userSelection == selectionIndex)
				{
					ActionNumber = player->getMaxActions();
					DrawGameScreen();
					break;
				}

				DrawGameScreen();
				cout << "Action " << ActionNumber + 1 << " of " << player->getMaxActions() << endl;
				cout << "------------------" << endl;
				ret = DoPlayerAction(player, AvailableActions[userSelection]);

				int iteration = 0;
				bool allDiseasesCured[4] = { false, false, false, false };
				Disease* disease = diseaseLinkedList;
				while(disease != nullptr)
				{
					allDiseasesCured[iteration] = disease->getIsCured();
					disease = disease->nextNode;
					++iteration;
				}

				if (allDiseasesCured[0] && allDiseasesCured[1] && allDiseasesCured[2] && allDiseasesCured[3])
				{
					EndGame(GameOverReason::WIN);
				}
				DrawGameScreen();
			} while (!gameOver && !ret);
		}

		for (int PlayerDeckDraw = 0; PlayerDeckDraw < playerCardDeck->getDrawCount() && !gameOver; ++PlayerDeckDraw)
		{
			cout << "Player Deck draw " << PlayerDeckDraw + 1 << " of " << playerCardDeck->getDrawCount() << endl;
			cout << "----------------------------" << endl;
			if (!playerCardDeck->isEmpty())
			{
				PlayerCard card = playerCardDeck->draw();
				if (!card.getIsEpidemic())
				{
					player->AddPlayerCardToHand(card);
				}

				GamePauseUntilKeyPress("Enter", KEY_ENTER);
				DrawGameScreen();
				while (player->isPlayerHandAtMax())
				{
					cout << "You have too many cards in your player hand (maximum " + to_string(player->getMaxCardsInHand()) + ")." << endl;
					cout << "Please select the card below that you would like to discard:" << endl;

					int selectionIndex = -1;
					vector<PlayerCard*> cards = player->getPlayerHandCards();
					for(PlayerCard* card : cards)
					{
						++selectionIndex;
						cout << (selectionIndex + 1) << ": " << card->getName() << endl;
					}

					int userSelection = GetNumericInput(1, selectionIndex + 1, true, true);
					player->DiscardCardFromHand(cards[userSelection]);
					DrawGameScreen();
				}
			}
			else
			{
				EndGame(GameOverReason::LOSS_PLAYERDECKEMPTY);
			}
		}

		for (int InfectionDeckDraw = 0; InfectionDeckDraw < getInfectionRate() && !gameOver; ++InfectionDeckDraw)
		{
			cout << "Infection Deck draw " << InfectionDeckDraw + 1 << " of " << getInfectionRate() << endl;
			cout << "-------------------------------" << endl;
			InfectionCard card = infectionCardDeck->draw();
			infectionCardDeck->discard(card);
			GamePauseUntilKeyPress("Enter", KEY_ENTER);
			DrawGameScreen();
		}
	} while (!gameOver);

	Disease* diseaseNodePtr = diseaseLinkedList;
	switch(reason)
	{
		case WIN:
			cout << "Congratulations! You have saved humanity this time... But can you do it again?" << endl;
			break;
		case LOSS_INFECTIONMARKERS:
			while (diseaseNodePtr != nullptr)
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

bool Game::DoPlayerAction(BasePlayer* player, string &action)
{
	bool ret = false;
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

Game::Options Game::getGameOptions() const
{
	return options;
}

City* Game::getCityLinkedList() const
{
	return cityLinkedList;
}

Disease* Game::getDiseaseLinkedList() const
{
	return diseaseLinkedList;
}

int Game::getInfectionRate() const
{
	return INFECTIONRATE[infectionRateIndex];
}

int Game::getInfectionRateIndex() const
{
	return infectionRateIndex;
}

BasePlayer* Game::getPlayer() const
{
	return player;
}

int Game::getMaxOutbreaks() const
{
	return MAXOUTBREAKS;
}

int Game::getMaxResearchStations() const
{
	return MAXRESEARCHSTATIONS;
}

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

int Game::getTotalOutbreaks() const
{
	return totalOutbreaks;
}

int Game::IncrementInfectionRate()
{
	if (infectionRateIndex < INFECTIONRATESIZE)
	{
		++infectionRateIndex;
	}
	return getInfectionRate();
}

int Game::IncrementOutbreaks()
{
	return ++totalOutbreaks;
}

PlayerCard Game::DrawPlayerCard() const
{
	return playerCardDeck->draw();
}

bool Game::DiscardPlayerCard(PlayerCard card) const
{
	return playerCardDeck->discard(card);
}

City* Game::DrawBottomInfectionCard()
{
	City* ret;
	InfectionCard Card = infectionCardDeck->drawBottom(true);
	Card.DrawAction(3);
	ret = Card.getCity();
	infectionCardDeck->discard(Card);
	return ret;
}

bool Game::IntensifyInfectionDeck()
{
	bool ret = false;

	infectionCardDeck->shuffle(Deck<InfectionCard>::Discard);

	while(!infectionCardDeck->isEmpty(Deck<InfectionCard>::Discard))
	{
		InfectionCard card = infectionCardDeck->draw(true, Deck<InfectionCard>::Discard);
		infectionCardDeck->discard(card, Deck<InfectionCard>::Draw);
	}

	return ret;
}

void Game::EndGame(GameOverReason reason)
{
	gameOver = true;
	this->reason = reason;
}

void Game::DrawGameScreen() const
{
	ClearScreen();

	int y = 2;
	City* cityNodePtr = CurrentGame->getCityLinkedList();
	for (int city = 0; city < 48; ++city)
	{
		int x = city < 24 ? 8 : 46;
		y = city == 24 ? 3 : ++y;

		PrintAtScreenPosition("", x, y, DEFAULT, false);
		cityNodePtr->print(false, cityNodePtr == CurrentGame->getPlayer()->getPlayerLocation(), true, true);
		cout << endl;

		cityNodePtr = cityNodePtr->nextNode;
	}

	Disease* diseaseNodePtr = diseaseLinkedList;
	for (int disease = 0; disease < 4; ++disease)
	{
		int x = 80;
		y = disease + 3;
		PrintAtScreenPosition("", x, y, DEFAULT, false);
		diseaseNodePtr->print(true, 1, true, true);
		cout << endl;

		diseaseNodePtr = diseaseNodePtr->nextNode;
	}

	PrintAtScreenPosition("Infection Tracker: 2 2 2 3 3 4 4", 84, 9, DEFAULT, false);
	PrintAtScreenPosition(to_string(getInfectionRate()), 103 + (2 * getInfectionRateIndex()), 9, SELECTED_TEXT, false);

	PrintAtScreenPosition("Outbreak Tracker: 0 1 2 3 4 5 6 7 8", 84, 10, DEFAULT, false);
	PrintAtScreenPosition(to_string(getTotalOutbreaks()), 102 + (2 * getTotalOutbreaks()), 10, SELECTED_TEXT, false);

	PrintAtScreenPosition("Cards In Hand (max " + to_string(player->getMaxCardsInHand()) + ")", 84, 13, DEFAULT, false);
	PrintAtScreenPosition("--------------------------", 84, 14, DEFAULT, false);
	vector<PlayerCard*> playerCard = player->getPlayerHandCards();
	for (int card = 0; card < playerCard.size(); ++card)
	{
		int x = 82;
		y = card + 15;
		PrintAtScreenPosition("", x, y, DEFAULT, false);
		playerCard[card]->getCity()->print();
		cout << endl;
	}

	PrintAtScreenPosition("", 0, 30, DEFAULT, false);
}

Game* GetCurrentGame()
{
	return CurrentGame;
}

string GetStringInput(string prompt)
{
	string userInput;
	cout << prompt << ": ";
	getline(cin, userInput);
	return userInput;
}

bool GetDestinationFromInputString(City* &destination, string &userInput)
{
	bool ret = false;
	userInput = GetStringInput("Please enter a destination, or type 'back' to return to the Action menu");

	if (ToLower(userInput) != "back")
	{
		do
		{
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

			if(ret == false)
			{
				userInput = GetStringInput("Please enter a destination");
			}
		} while (ret == false);
	}
	return ret;
}

vector<City*> GetCitiesContainingResearchStations(City* excludeCurrentCity)
{
	vector<City*> ret;
	City* currentCity = CurrentGame->getCityLinkedList();
	while (currentCity != nullptr)
	{
		if (currentCity->hasResearchStation() && currentCity != excludeCurrentCity)
		{
			ret.push_back(currentCity);
		}
		currentCity = currentCity->nextNode;
	}
	return ret;
}

int GetNumericInput(int minValue, int maxValue, bool NonNegative, bool ReturnZeroBased)
{
	int ret = 0;
	string userInput;
	do
	{
		cout << "Please enter a value" << (minValue == INT_MIN && maxValue == INT_MAX ? (NonNegative ? " [non-negative]: " : ": ") : " [" + to_string(minValue) + "-" + to_string(maxValue) + "]: ");
		getline(cin, userInput);
	} while (!(IsNumeric(userInput, ret, NonNegative) && (minValue == INT_MIN || ret >= minValue) && (maxValue == INT_MAX || ret <= maxValue)));
	return ReturnZeroBased ? ret - 1 : ret;
}

bool IsNumeric(string &input, int &output, bool NonNegative)
{
	bool ret = true;
	if (input.size() != 0)
	{
		for (char character : input)
		{
			if (!isdigit(character) && (NonNegative || character != '-'))
			{
				ret = false;
			}
		}

		output = INT_MIN;
		if (ret)
		{
			output = stoi(input);
		}
	}
	return ret;
}

string ToLower(string input)
{
	string ret = input;
	transform(input.begin(), input.end(), ret.begin(), ::tolower);
	return ret;
}

string ToUpper(string input)
{
	string ret = input;
	transform(input.begin(), input.end(), ret.begin(), ::toupper);
	return ret;
}

void GamePauseUntilKeyPress(string keyname, WORD key)
{
	cout << endl << "Please press the " << ToUpper(keyname) << " to continue...";
	while(_getch() != key)
	{
		// Nothing to do here, just go back to the while test line and wait until the correct key is pressed.
	}
}
