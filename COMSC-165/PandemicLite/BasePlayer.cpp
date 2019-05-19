#include "Card.h"
#include "Disease.h"
#include "BasePlayer.h"
#include "Game.h"

BasePlayer::BasePlayer(string name, City* startingLocation, unsigned int maxActions, unsigned int discoverCureNumber, unsigned int maxCardsInHand)
{
	this->name = name;
	this->maxActions = maxActions;
	this->discoverCureNumber = discoverCureNumber;
	this->maxCardsInHand = maxCardsInHand;
	this->playerHand = Stack<PlayerCard>();
	this->playerLocation = startingLocation;
}

string BasePlayer::getName() const
{
	return name;
}

unsigned int BasePlayer::getMaxActions() const
{
	return maxActions;
}

unsigned int BasePlayer::getMaxCardsInHand() const
{
	return maxCardsInHand;
}

vector<PlayerCard*> BasePlayer::getPlayerHandCards()
{
	vector<PlayerCard*> ret;
	Stack<PlayerCard>::LinkedListNode* currentCard = playerHand.stack_nodes();
	while (currentCard != nullptr)
	{
		ret.push_back(&currentCard->data);
		currentCard = currentCard->nextNode;
	}
	return ret;
}


void BasePlayer::AddPlayerCardToHand(PlayerCard card)
{
	playerHand.push(card);
}

void BasePlayer::DiscardCardFromHand(PlayerCard* card)
{
	int index = 0;
	Stack<PlayerCard>::LinkedListNode* currentCard = playerHand.stack_nodes();
	while(currentCard != nullptr)
	{
		if (currentCard->data == card)
		{
			playerHand.pop_Nth(index);
			break;
		}
		++index;
	}
}

vector<string> BasePlayer::getAvailableActions()
{
	vector<string> ret;

	// Drive/Ferry action is always available as an Action
	ret.push_back("Drive/Ferry");

	if (!playerHand.isEmpty())
	{
		ret.push_back("Direct Flight");
		if (playerHand.contains(PlayerCard(playerLocation, false)))
		{
			ret.push_back("Charter Flight");
		}
	}

	if(playerLocation->hasResearchStation() && GetResearchStationCount() > 1)
	{
		ret.push_back("Shuttle Flight");
	}

	if (!(playerLocation->hasResearchStation()) && playerHand.contains(PlayerCard(playerLocation, false)))
	{
		ret.push_back("Build a Research Station");
	}

	City::Infection* infection = playerLocation->getPrimaryInfection();
	while(infection != nullptr)
	{
		if(infection->count > 0)
		{
			ret.push_back("Treat Disease");
			break;
		}
		infection = infection->nextNode;
	}

	if(playerLocation->hasResearchStation() && !calcDiscoverCureCards().empty())
	{
		ret.push_back("Discover a Cure");
	}

	ret.push_back("Pass");
	return ret;
}

bool BasePlayer::isPlayerHandAtMax()
{
	return playerHand.size() >= maxCardsInHand;
}


bool BasePlayer::DriveFerry()
{
	bool ret = false;

	cout << "You are Driving/Ferrying from " << playerLocation->getName() << " to a neighboring city. Please select the city you would like to travel to from the list below." << endl;

	int selectionIndex = -1;
	for(City* neighbor : playerLocation->getNeighbors())
	{
		++selectionIndex;
		cout << (selectionIndex + 1) << ": " << neighbor->getName() << endl;
	}
	++selectionIndex;
	cout << (selectionIndex + 1) << ": Back to Action selection menu" << endl;

	int userSelection = GetNumericInput(1, selectionIndex + 1, true, true);
	if(userSelection == selectionIndex)
	{
		return ret;
	}

	playerLocation = playerLocation->getNeighbors()[userSelection];
	ret = true;

	return ret;
}

bool BasePlayer::DirectFlight()
{
	bool ret = false;

	cout << "You are taking a Direct Flight from " << playerLocation->getName() << ". Please select your destination from the list below. Note that this action will discard the city card from your hand." << endl;

	int selectionIndex = -1;
	Stack<PlayerCard>::LinkedListNode* destinationCity = playerHand.stack_nodes();
	while(destinationCity != nullptr)
	{
		++selectionIndex;
		cout << (selectionIndex + 1) << ": " << destinationCity->data.getCity()->getName() << endl;
		destinationCity = destinationCity->nextNode;
	}
	++selectionIndex;
	cout << (selectionIndex + 1) << ": Back to Action selection menu" << endl;

	int userSelection = GetNumericInput(1, selectionIndex + 1, true, true);
	if (userSelection == selectionIndex)
	{
		return ret;
	}

	playerLocation = playerHand.nth(userSelection).getCity();
	DiscardPlayerCard(playerHand.nth(userSelection));
	playerHand.pop_Nth(userSelection);
	ret = true;

	return ret;
}

bool BasePlayer::CharterFlight()
{
	bool ret = false;

	cout << "You are taking a Charter flight from " << playerLocation->getName() << " to any city on the board." << endl;

	string userInput;
	City* destination = nullptr;
	if (!GetDestinationFromInputString(destination, userInput) && destination == nullptr)
	{
		return ret;
	}

	Stack<PlayerCard>::LinkedListNode* playerCards = playerHand.stack_nodes();
	int index = 0;
	while (playerCards != nullptr && playerCards->data.getCity() != playerLocation)
	{
		++index;
		playerCards = playerCards->nextNode;
	}

	if (playerCards == nullptr)
	{
		throw InvalidArgumentException("Cannot perform the 'Charter Flight' action as there was no player card matching the player's current location '" + playerLocation->getName() + "' in the player's hand.");
	}

	playerLocation = destination;
	DiscardPlayerCard(playerHand.nth(index));
	playerHand.pop_Nth(index);
	ret = true;

	return ret;
}

bool BasePlayer::ShuttleFlight()
{
	bool ret = false;

	cout << "You are taking a Shuttle Flight from the Research Station in " << playerLocation->getName() << " to another city's Research Station. Please select the city you would like to travel to from the list below." << endl;

	int selectionIndex = -1;
	vector<City*> researchStationCities = GetCitiesContainingResearchStations(playerLocation);
	for(City* city : researchStationCities)
	{
		++selectionIndex;
		cout << (selectionIndex + 1) << ": " << city->getName() << endl;
	}
	++selectionIndex;
	cout << (selectionIndex + 1) << ": Back to Action selection menu" << endl;

	int userSelection = GetNumericInput(1, selectionIndex + 1, true, true);
	if (userSelection == selectionIndex)
	{
		return ret;
	}

	playerLocation = researchStationCities[userSelection];
	ret = true;

	return ret;
}

bool BasePlayer::BuildResearchStation()
{
	bool ret = false;

	Stack<PlayerCard>::LinkedListNode* playerCards = playerHand.stack_nodes();
	int index = 0;
	while (playerCards != nullptr && playerCards->data.getCity() != playerLocation)
	{
		++index;
		playerCards = playerCards->nextNode;
	}

	if (playerCards == nullptr)
	{
		throw InvalidArgumentException("Cannot perform the 'Build a Research Station' action as there was no player card matching the player's current location '" + playerLocation->getName() + "' in the player's hand.");
	}

	playerLocation->buildResearchStation();
	DiscardPlayerCard(playerHand.nth(index));
	playerHand.pop_Nth(index);
	ret = true;

	return ret;
}

bool BasePlayer::TreatDisease(bool IsMedic)
{
	bool ret = false;

	City::Infection* cityInfections = playerLocation->getPrimaryInfection();
	vector<Disease*> currentDiseases;
	while(cityInfections != nullptr)
	{
		if(cityInfections->count > 0)
		{
			currentDiseases.push_back(cityInfections->disease);
		}
		cityInfections = cityInfections->nextNode;
	}

	int userSelection = 0;
	if(currentDiseases.size() > 1)
	{
		cout << "Which disease would you like to Treat? Please select the disease from the list below." << endl;

		int selectionIndex = -1;
		for (Disease* disease : currentDiseases)
		{
			++selectionIndex;
			cout << (selectionIndex + 1) << ": " << disease->getName() << endl;
		}
		++selectionIndex;
		cout << (selectionIndex + 1) << ": Back to Action selection menu" << endl;

		userSelection = GetNumericInput(1, selectionIndex + 1, true, true);
		if (userSelection == selectionIndex)
		{
			return ret;
		}
	}

	if(IsMedic)
	{
		currentDiseases[userSelection]->disinfect(playerLocation, 3);
		ret = !currentDiseases[userSelection]->getIsEradicated();
	}
	else
	{
		int removeInfectionMarkerCount = !currentDiseases[userSelection]->getIsCured() ? 1 : 3;
		currentDiseases[userSelection]->disinfect(playerLocation, removeInfectionMarkerCount);
		ret = true;
	}

	return ret;
}

bool BasePlayer::DiscoverCure()
{
	bool ret = false;
	vector<vector<PlayerCard>> availableCures = calcDiscoverCureCards();

	int userCureSelection = 0;
	if (availableCures.size() > 1)
	{
		cout << "Which disease would you like to Cure? Please select the disease from the list below." << endl;

		int selectionIndex = -1;
		for (vector<PlayerCard> cardStack : availableCures)
		{
			++selectionIndex;
			cout << (selectionIndex + 1) << ": " << cardStack[0].getCity()->getPrimaryInfection()->disease->getName() << endl;
		}
		++selectionIndex;
		cout << (selectionIndex + 1) << ": Back to Action selection menu" << endl;

		userCureSelection = GetNumericInput(1, selectionIndex + 1, true, true);
		if (userCureSelection == selectionIndex)
		{
			return ret;
		}
	}

	vector<PlayerCard> discardCards;
	if (availableCures[userCureSelection].size() > discoverCureNumber)
	{
		cout << "Please select which cards you would like to discard to Discover a Cure for " << availableCures[userCureSelection][0].getCity()->getPrimaryInfection()->disease->getName() << "." << endl;

		for (int iteration = 0; iteration < discoverCureNumber; ++iteration)
		{
			int selectionIndex = -1;
			for (PlayerCard card : availableCures[userCureSelection])
			{
				++selectionIndex;
				cout << (selectionIndex + 1) << ": " << card.getName() << endl;
			}
			++selectionIndex;
			cout << (selectionIndex + 1) << ": Back to Action selection menu" << endl;
			cout << "[" << iteration + 1 << " of " << discoverCureNumber << "] " << endl;

			int userCardSelection = GetNumericInput(1, selectionIndex + 1, true, true);
			if (userCardSelection == selectionIndex)
			{
				return ret;
			}

			discardCards.push_back(availableCures[userCureSelection][userCardSelection]);
			availableCures[userCureSelection].erase(availableCures[userCureSelection].begin() + userCardSelection);
		}
	}
	else
	{
		discardCards = availableCures[userCureSelection];
	}

	for (PlayerCard card : discardCards)
	{
		Stack<PlayerCard>::LinkedListNode* playerCards = playerHand.stack_nodes();
		int index = 0;
		while (playerCards != nullptr && playerCards->data.getCity() != card.getCity())
		{
			++index;
			playerCards = playerCards->nextNode;
		}
		DiscardPlayerCard(playerHand.nth(index));
		playerHand.pop_Nth(index);
	}

	discardCards[0].getCity()->getPrimaryInfection()->disease->discoverCure();
	ret = true;

	return ret;
}

vector<vector<PlayerCard>> BasePlayer::calcDiscoverCureCards() const
{
	vector<vector<PlayerCard>> ret;

	vector<PlayerCard> BluePlayerCards;
	vector<PlayerCard> YellowPlayerCards;
	vector<PlayerCard> PurplePlayerCards;
	vector<PlayerCard> RedPlayerCards;

	Stack<PlayerCard>::LinkedListNode* playerCards = playerHand.stack_nodes();
	while (playerCards != nullptr)
	{
		if (playerCards->data.getCity()->getPrimaryInfection()->disease->getName() == globalGameOptions.BlueDiseaseName && !playerCards->data.getCity()->getPrimaryInfection()->disease->getIsCured())
		{
			BluePlayerCards.push_back(playerCards->data);
		}
		else if (playerCards->data.getCity()->getPrimaryInfection()->disease->getName() == globalGameOptions.YellowDiseaseName && !playerCards->data.getCity()->getPrimaryInfection()->disease->getIsCured())
		{
			YellowPlayerCards.push_back(playerCards->data);
		}
		else if (playerCards->data.getCity()->getPrimaryInfection()->disease->getName() == globalGameOptions.PurpleDiseaseName && !playerCards->data.getCity()->getPrimaryInfection()->disease->getIsCured())
		{
			PurplePlayerCards.push_back(playerCards->data);
		}
		else if (playerCards->data.getCity()->getPrimaryInfection()->disease->getName() == globalGameOptions.RedDiseaseName && !playerCards->data.getCity()->getPrimaryInfection()->disease->getIsCured())
		{
			RedPlayerCards.push_back(playerCards->data);
		}
		playerCards = playerCards->nextNode;
	}

	if (BluePlayerCards.size() >= discoverCureNumber)
	{
		ret.push_back(BluePlayerCards);
	}

	if (YellowPlayerCards.size() >= discoverCureNumber)
	{
		ret.push_back(YellowPlayerCards);
	}

	if (PurplePlayerCards.size() >= discoverCureNumber)
	{
		ret.push_back(PurplePlayerCards);
	}

	if (RedPlayerCards.size() >= discoverCureNumber)
	{
		ret.push_back(RedPlayerCards);
	}

	return ret;
}
