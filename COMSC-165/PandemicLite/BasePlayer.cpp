#include "Card.h"
#include "BasePlayer.h"
#include "Game.h"

BasePlayer::BasePlayer(string name, City* startingLocation, unsigned int maxActions, unsigned int discoverCureNumber)
{
	this->name = name;
	this->maxActions = maxActions;
	this->discoverCureNumber = discoverCureNumber;
	this->playerHand = Stack<PlayerCard>();
	this->playerLocation = startingLocation;
}

string BasePlayer::getName() const
{
	return name;
}

unsigned BasePlayer::getMaxActions() const
{
	return maxActions;
}

void BasePlayer::AddPlayerCardToHand(PlayerCard card)
{
	playerHand.push(card);
}


vector<string> BasePlayer::getAvailableActions()
{
	vector<string> ret;

	int ActionNumber = 0;
	// Drive/Ferry action is always available as an Action
	ret.push_back("Drive/Ferry");

	if (!playerHand.isEmpty())
	{
		ret.push_back("Direct Flight");
		ret.push_back("Charter Flight");
	}

	if(playerLocation->hasResearchStation() && GetResearchStationCount() < 1)
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

	int PlayerCardsMatchingDisease = 0;
	Disease* primaryInfection = playerLocation->getPrimaryInfection()->disease;
	Stack<PlayerCard>::LinkedListNode* nodePtr = playerHand.stack_nodes();
	while(nodePtr != nullptr)
	{
		if(nodePtr->data.getCity()->getPrimaryInfection()->disease == primaryInfection)
		{
			++PlayerCardsMatchingDisease;
		}
		nodePtr = nodePtr->nextNode;
	}
	
	if(playerLocation->hasResearchStation() && PlayerCardsMatchingDisease >= discoverCureNumber)
	{
		ret.push_back("Discover a Cure");
	}

	ret.push_back("Pass");
	return ret;
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

	int userSelection = GetNumericInput(1, selectionIndex + 1, true);
	if(userSelection == selectionIndex)
	{
		return ret;
	}


	return ret;
}

