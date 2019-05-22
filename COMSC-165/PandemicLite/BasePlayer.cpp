#include "Card.h"
#include "Disease.h"
#include "BasePlayer.h"
#include "Game.h"

// *******************************************************************************************
// **     Function: BasePlayer (constructor)												**
// **   Parameters: string name																**
// **				City* startingLocation													**
// **				unsigned int maxActions (optional) [Default = 4]						**
// **				unsigned int discoverCureNumber (optional) [Default = 5]				**
// **				unsigned int maxCardsInHand (optional) [Default = 9]					**
// **       Return: N/A																		**
// **  Description: Initializes a BasePlayer instance with the input parameter values.		**
// *******************************************************************************************
BasePlayer::BasePlayer(string name, City* startingLocation, unsigned int maxActions, unsigned int discoverCureNumber, unsigned int maxCardsInHand)
{
	this->name = name;
	this->maxActions = maxActions;
	this->discoverCureNumber = discoverCureNumber;
	this->maxCardsInHand = maxCardsInHand;
	this->playerHand = Stack<PlayerCard>();
	this->playerLocation = startingLocation;
}

// *******************************************************************************************
// **     Function: getName																	**
// **   Parameters: N/A																		**
// **       Return: string																	**
// **  Description: Returns the 'name' private variable value.								**
// *******************************************************************************************
string BasePlayer::getName() const
{
	return name;
}

// *******************************************************************************************
// **     Function: getMaxActions															**
// **   Parameters: N/A																		**
// **       Return: unsigned int															**
// **  Description: Returns the 'maxActions' private variable value.						**
// *******************************************************************************************
unsigned int BasePlayer::getMaxActions() const
{
	return maxActions;
}

// *******************************************************************************************
// **     Function: getMaxCardsInHand														**
// **   Parameters: N/A																		**
// **       Return: unsigned int															**
// **  Description: Returns the 'maxCardsInHand' private variable value.					**
// *******************************************************************************************
unsigned int BasePlayer::getMaxCardsInHand() const
{
	return maxCardsInHand;
}

// *******************************************************************************************
// **     Function: getPlayerHandCards														**
// **   Parameters: N/A																		**
// **       Return: vector<PlayerCard*>														**
// **  Description: Returns a vector of pointers to the cards in the player hand.			**
// *******************************************************************************************
vector<PlayerCard*> BasePlayer::getPlayerHandCards()
{
	// Create and set the default return value to an empty vector<PlayerCard*>.
	vector<PlayerCard*> ret;

	// Node traversal pointer for the stack
	Stack<PlayerCard>::LinkedListNode* currentCard = playerHand.stack_nodes();

	// Loop through each node of the player hand stack and push into return vector.
	while (currentCard != nullptr)
	{
		ret.push_back(&currentCard->data);
		currentCard = currentCard->nextNode;
	}
	return ret;
}

// *******************************************************************************************
// **     Function: getPlayerLocation														**
// **   Parameters: N/A																		**
// **       Return: City*																	**
// **  Description: Returns the 'getPlayerLocation' private variable value.					**
// *******************************************************************************************
City* BasePlayer::getPlayerLocation()
{
	return playerLocation;
}

// *******************************************************************************************
// **     Function: AddPlayerCardToHand														**
// **   Parameters: PlayerCard card															**
// **       Return: void																	**
// **  Description: Adds the PlayerCard object into the player hand stack.					**
// *******************************************************************************************
void BasePlayer::AddPlayerCardToHand(PlayerCard card)
{
	playerHand.push(card);
}

// *******************************************************************************************
// **     Function: DiscardCardFromHand														**
// **   Parameters: PlayerCard* card														**
// **       Return: void																	**
// **  Description: Removes the specified PlayerCard object from the player hand stack.		**
// *******************************************************************************************
void BasePlayer::DiscardCardFromHand(PlayerCard* card)
{
	// Set an index variable to zero to hold the position in the stack where the node resides.
	int index = 0;

	// Node traversal pointer for the stack
	Stack<PlayerCard>::LinkedListNode* currentCard = playerHand.stack_nodes();

	// Loop through each node of the player hand stack and compare the node's data to the provided card.
	while(currentCard != nullptr)
	{
		// If the card matches, pop the node from the stack at the specific index and break.
		if (currentCard->data == card)
		{
			playerHand.pop_Nth(index);
			break;
		}

		// Advance the index and node traversal pointer
		++index;
		currentCard = currentCard->nextNode;
	}
}

// *******************************************************************************************
// **     Function: getAvailableActions														**
// **   Parameters: N/A																		**
// **       Return: vector<string>															**
// **  Description: Calculates the available actions for the player using their player		**
// **				hand and location. Returns a string of available actions.				**
// *******************************************************************************************
vector<string> BasePlayer::getAvailableActions()
{
	// Create and set the default return value to an empty vector<string>.
	vector<string> ret;

	// Drive/Ferry action is always available as an Action, so add it to the return vector
	ret.push_back("Drive/Ferry");

	// Check if the player hand is empty.
	if (!playerHand.isEmpty())
	{
		// If the player has any player cards in hand, he/she can take the Direct Flight option.
		ret.push_back("Direct Flight");

		// Check if any of the cards in the player hand matches the current location. If so, then the player can take the Charter Flight action.
		if (playerHand.contains(PlayerCard(playerLocation, false)))
		{
			ret.push_back("Charter Flight");
		}
	}

	// Check if the player's current location has a research station and that there are more than 1 on the board. If so, then the player can
	// take the Shuttle Flight action.
	if(playerLocation->hasResearchStation() && GetCurrentGame()->getResearchStationCount() > 1)
	{
		ret.push_back("Shuttle Flight");
	}

	// Check if the player's current location already has a research station. If not, and the player has the city in their hand and there are available
	// research stations, then make the Build a Research Station action available.
	if (!(playerLocation->hasResearchStation()) && playerHand.contains(PlayerCard(playerLocation, false)) && GetCurrentGame()->getResearchStationCount() < GetCurrentGame()->getMaxResearchStations())
	{
		ret.push_back("Build a Research Station");
	}

	// Node traversal pointer for the city's infections
	City::Infection* infection = playerLocation->getPrimaryInfection();

	// Loop through each infection to see if the infection is greater than 0. If so, then the player can Treat Disease in his/her current location.
	while(infection != nullptr)
	{
		if (infection->count > 0)
		{
			ret.push_back("Treat Disease");
			break;
		}
		infection = infection->nextNode;
	}

	// Check if the player's current location has a research station and he/she has enough cards to Discover a Cure. If so, add the Discover Cure action to the
	// return vector.
	if(playerLocation->hasResearchStation() && !calcDiscoverCureCards().empty())
	{
		ret.push_back("Discover a Cure");
	}

	// Finally always add Pass as an option and return the vector.
	ret.push_back("Pass");
	return ret;
}

// *******************************************************************************************
// **     Function: isPlayerHandAtMax														**
// **   Parameters: N/A																		**
// **       Return: bool																	**
// **  Description: Returns true of the player's hand is over the maximum allowable value.	**
// *******************************************************************************************
bool BasePlayer::isPlayerHandAtMax()
{
	return playerHand.size() > maxCardsInHand;
}

// *******************************************************************************************
// **     Function: DriveFerry																**
// **   Parameters: N/A																		**
// **       Return: bool																	**
// **  Description: Prompts the player which neighboring city that they would like to move	**
// **				to and moves their character upon selection.							**
// *******************************************************************************************
bool BasePlayer::DriveFerry()
{
	// Set the default return value to false.
	// NOTE: Returning false from any Action will make the Action not count against the players available actions this turn.
	bool ret = false;

	// Display a message to the user about performing this action.
	cout << "You are Driving/Ferrying from " << *playerLocation << " to a neighboring city.\nPlease select the city you would like to travel to from the list below." << endl;

	// Variable that stores the corresponding (zero-based) menu option number.
	int selectionIndex = -1;

	// Loop through each of the neighbors listing each one out with a number.
	for(City* neighbor : playerLocation->getNeighbors())
	{
		++selectionIndex;
		cout << (selectionIndex + 1) << ": " << neighbor->getName() << endl;
	}

	// Add an option to return back the the Action selection menu.
	++selectionIndex;
	cout << (selectionIndex + 1) << ": Back to Action selection menu" << endl;

	// Prompt the user for input using the GetNumericInput.
	int userSelection = GetNumericInput(1, selectionIndex + 1, true, true);

	// If the value entered by the user is the last option on the list, return false from the action so it doesn't count towards the action limit.
	if(userSelection == selectionIndex)
	{
		return ret;
	}

	// Set the player's location to the selected location and set the return value to true.
	playerLocation = playerLocation->getNeighbors()[userSelection];
	ret = true;

	return ret;
}

// *******************************************************************************************
// **     Function: DirectFlight															**
// **   Parameters: N/A																		**
// **       Return: bool																	**
// **  Description: Prompts the player which city they would like to travel to based off	**
// **				of the cards in their hand. Once selected the matching city card will	**
// **				be discarded.															**
// *******************************************************************************************
bool BasePlayer::DirectFlight()
{
	// Set the default return value to false.
	// NOTE: Returning false from any Action will make the Action not count against the players available actions this turn.
	bool ret = false;

	// Display a message to the user about performing this action.
	cout << "You are taking a Direct Flight from " << *playerLocation << ".\nPlease select your destination from the list below. Note that this action will discard the city card from your hand." << endl;

	// Variable that stores the corresponding (zero-based) menu option number.
	int selectionIndex = -1;

	// Use a loop to traverse through the nodes in the player hand stack.
	Stack<PlayerCard>::LinkedListNode* destinationCity = playerHand.stack_nodes();
	while(destinationCity != nullptr)
	{
		++selectionIndex;
		cout << (selectionIndex + 1) << ": " << destinationCity->data.getCity()->getName() << endl;
		destinationCity = destinationCity->nextNode;
	}

	// Add an option to return back the the Action selection menu.
	++selectionIndex;
	cout << (selectionIndex + 1) << ": Back to Action selection menu" << endl;

	// Prompt the user for input using the GetNumericInput.
	int userSelection = GetNumericInput(1, selectionIndex + 1, true, true);

	// If the value entered by the user is the last option on the list, return false from the action so it doesn't count towards the action limit.
	if (userSelection == selectionIndex)
	{
		return ret;
	}

	// Set the player's location to the selected location, add the card to the player deck discard pile, remove it from the player's hand, and set the return value to true.
	playerLocation = playerHand.nth(userSelection).getCity();
	GetCurrentGame()->DiscardPlayerCard(playerHand.nth(userSelection));
	playerHand.pop_Nth(userSelection);
	ret = true;

	return ret;
}

// *******************************************************************************************
// **     Function: DirectFlight															**
// **   Parameters: N/A																		**
// **       Return: bool																	**
// **  Description: Prompts the player which city they would like to travel to based off	**
// **				of the cards in their hand. Once selected the matching city card will	**
// **				be discarded.															**
// *******************************************************************************************
bool BasePlayer::CharterFlight()
{
	// Set the default return value to false.
	// NOTE: Returning false from any Action will make the Action not count against the players available actions this turn.
	bool ret = false;

	// Display a message to the user about performing this action.
	cout << "You are taking a Charter flight from " << *playerLocation << " to any city on the board." << endl;

	// Variable to hold the user input string and destination city pointer
	string userInput;
	City* destination = nullptr;

	// Use the GetDestinationFromInputString function to prompt the user for input and return a true if the location is valid and stores the city pointer in the destination city pointer.
	// If the user types "back" in the GetDestinationFromInputString function it will return back to the action menu.
	if (!GetDestinationFromInputString(destination, userInput) && destination == nullptr)
	{
		return ret;
	}

	// Look through the player cards finding the current city in the hand.
	Stack<PlayerCard>::LinkedListNode* playerCards = playerHand.stack_nodes();
	int index = 0;
	while (playerCards != nullptr && playerCards->data.getCity() != playerLocation)
	{
		++index;
		playerCards = playerCards->nextNode;
	}

	// If the player doesn't have the city card matching their current location then throw an exception.
	if (playerCards == nullptr)
	{
		throw InvalidArgumentException("Cannot perform the 'Charter Flight' action as there was no player card matching the player's current location '" + playerLocation->getName() + "' in the player's hand.");
	}

	// Set the player's location to the selected location, add the card to the player deck discard pile, remove it from the player's hand, and set the return value to true.
	playerLocation = destination;
	GetCurrentGame()->DiscardPlayerCard(playerHand.nth(index));
	playerHand.pop_Nth(index);
	ret = true;

	return ret;
}

// *******************************************************************************************
// **     Function: ShuttleFlight															**
// **   Parameters: N/A																		**
// **       Return: bool																	**
// **  Description: Prompts the player which research station they want to travel to from	**
// **				the current city with a research station.								**
// *******************************************************************************************
bool BasePlayer::ShuttleFlight()
{
	// Set the default return value to false.
	// NOTE: Returning false from any Action will make the Action not count against the players available actions this turn.
	bool ret = false;

	// Display a message to the user about performing this action.
	cout << "You are taking a Shuttle Flight from the Research Station in " << *playerLocation << " to another city's Research Station.\nPlease select the city you would like to travel to from the list below." << endl;

	// Variable that stores the corresponding (zero-based) menu option number and a variable that holds the cities with research stations (excluding the current player's location)
	int selectionIndex = -1;
	vector<City*> researchStationCities = GetCitiesContainingResearchStations(playerLocation);

	// Loop through each of the cities in the vector listing each one out with a number.
	for(City* city : researchStationCities)
	{
		++selectionIndex;
		cout << (selectionIndex + 1) << ": " << city->getName() << endl;
	}

	// Add an option to return back the the Action selection menu.
	++selectionIndex;
	cout << (selectionIndex + 1) << ": Back to Action selection menu" << endl;

	// Prompt the user for input using the GetNumericInput.
	int userSelection = GetNumericInput(1, selectionIndex + 1, true, true);

	// If the value entered by the user is the last option on the list, return false from the action so it doesn't count towards the action limit.
	if (userSelection == selectionIndex)
	{
		return ret;
	}

	// Set the player's location to the selected location and set the return value to true.
	playerLocation = researchStationCities[userSelection];
	ret = true;

	return ret;
}

// *******************************************************************************************
// **     Function: BuildResearchStation													**
// **   Parameters: N/A																		**
// **       Return: bool																	**
// **  Description: Prompts the player which research station they want to travel to from	**
// **				the current city with a research station.								**
// *******************************************************************************************
bool BasePlayer::BuildResearchStation()
{
	// Set the default return value to false.
	// NOTE: Returning false from any Action will make the Action not count against the players available actions this turn.
	bool ret = false;

	// Look through the player cards finding the current city in the hand.
	Stack<PlayerCard>::LinkedListNode* playerCards = playerHand.stack_nodes();
	int index = 0;
	while (playerCards != nullptr && playerCards->data.getCity() != playerLocation)
	{
		++index;
		playerCards = playerCards->nextNode;
	}

	// If the player doesn't have the city card matching their current location then throw an exception.
	if (playerCards == nullptr)
	{
		throw InvalidArgumentException("Cannot perform the 'Build a Research Station' action as there was no player card matching the player's current location '" + playerLocation->getName() + "' in the player's hand.");
	}

	// Set the player's location to the selected location, add the card to the player deck discard pile, remove it from the player's hand, and set the return value to true.
	playerLocation->buildResearchStation();
	GetCurrentGame()->DiscardPlayerCard(playerHand.nth(index));
	playerHand.pop_Nth(index);
	ret = true;

	return ret;
}

// *******************************************************************************************
// **     Function: TreatDisease															**
// **   Parameters: bool IsMedic															**
// **       Return: bool																	**
// **  Description: Treats disease at the current player's location. If there is more than,	**
// **				one infection in the city, it will prompt the user what to treat.		**
// *******************************************************************************************
bool BasePlayer::TreatDisease(bool IsMedic)
{
	// Set the default return value to false.
	// NOTE: Returning false from any Action will make the Action not count against the players available actions this turn.
	bool ret = false;

	// Variable that holds the city's current infection linked list nodes and a vector to hold the current infections.
	City::Infection* cityInfections = playerLocation->getPrimaryInfection();
	vector<Disease*> currentDiseases;

	// Loop through each of the city's infections
	while(cityInfections != nullptr)
	{
		// Add the infection to a vector of current infections if it has a count greater than zero
		if(cityInfections->count > 0)
		{
			currentDiseases.push_back(cityInfections->disease);
		}
		cityInfections = cityInfections->nextNode;
	}

	// Variable to hold the user's selection (default to 0 in case there is only one disease which will automatically get treated).
	int userSelection = 0;

	// Check if the current diseases vector has more than one disease listed.
	if(currentDiseases.size() > 1)
	{
		// Display a message to the user about performing this action.
		cout << "Which disease would you like to Treat?\nPlease select the disease from the list below." << endl;

		// Variable that stores the corresponding (zero-based) menu option number.
		int selectionIndex = -1;

		// Loop through each of the diseases listing each one out with a number.
		for (Disease* disease : currentDiseases)
		{
			++selectionIndex;
			cout << (selectionIndex + 1) << ": " << disease->getName() << endl;
		}

		// Add an option to return back the the Action selection menu.
		++selectionIndex;
		cout << (selectionIndex + 1) << ": Back to Action selection menu" << endl;

		// Prompt the user for input using the GetNumericInput.
		userSelection = GetNumericInput(1, selectionIndex + 1, true, true);

		// If the value entered by the user is the last option on the list, return false from the action so it doesn't count towards the action limit.
		if (userSelection == selectionIndex)
		{
			return ret;
		}
	}

	// Check if the IsMedic flag is set to true. If so, the medic has a special ability.
	if(IsMedic)
	{
		// The Medic can clear all the infection markers of a disease in the player city. If the disease is cured, this action is free else it counts as 1 action.
		if (!currentDiseases.empty())
		{
			currentDiseases[userSelection]->disinfect(playerLocation, 3);
			ret = !currentDiseases[userSelection]->getIsCured();
		}
	}
	else
	{
		// If the infection is cured then the player can treat all infection markers for 1 action. Set the return value to true.
		int removeInfectionMarkerCount = !currentDiseases[userSelection]->getIsCured() ? 1 : 3;
		currentDiseases[userSelection]->disinfect(playerLocation, removeInfectionMarkerCount);
		ret = true;
	}

	return ret;
}

// *******************************************************************************************
// **     Function: DiscoverCure															**
// **   Parameters: N/A																		**
// **       Return: bool																	**
// **  Description: If the player has the required number of cards and is located at a		**
// **				research station then they can Discover a Cure for the disease.			**
// *******************************************************************************************
bool BasePlayer::DiscoverCure()
{
	// Set the default return value to false.
	// NOTE: Returning false from any Action will make the Action not count against the players available actions this turn.
	bool ret = false;

	// Calculate the diseases that can be cured with the cards in the player's hand and divide them into individual piles for processing later.
	vector<vector<PlayerCard>> availableCures = calcDiscoverCureCards();

	// Variable to hold the user's selection (default to 0 in case there is only one disease which will automatically get cured).
	int userCureSelection = 0;

	// Check if the available cures vector has more than one disease listed.
	if (availableCures.size() > 1)
	{
		// Display a message to the user about performing this action.
		cout << "Which disease would you like to Cure?\nPlease select the disease from the list below." << endl;

		// Variable that stores the corresponding (zero-based) menu option number.
		int selectionIndex = -1;

		// Loop through each of the available cures listing each disease out with a number.
		for (vector<PlayerCard> cardStack : availableCures)
		{
			++selectionIndex;
			cout << (selectionIndex + 1) << ": " << cardStack[0].getCity()->getPrimaryInfection()->disease->getName() << endl;
		}

		// Add an option to return back the the Action selection menu.
		++selectionIndex;
		cout << (selectionIndex + 1) << ": Back to Action selection menu" << endl;

		// Prompt the user for input using the GetNumericInput.
		userCureSelection = GetNumericInput(1, selectionIndex + 1, true, true);

		// If the value entered by the user is the last option on the list, return false from the action so it doesn't count towards the action limit.
		if (userCureSelection == selectionIndex)
		{
			return ret;
		}
	}

	// Create a vector of player cards to discard. Note: If the number of cards is equal to the number of cards required to discover a cure then this vector will automatically get populated in the
	// else... statement.
	vector<PlayerCard> discardCards;

	// Check if the number of cards available to discover a cure in hand is greater than the discover a cure minimum. If so, the game needs to prompt the user to select which cards to discard.
	if (availableCures[userCureSelection].size() > discoverCureNumber)
	{
		// Iterate through the number of cards required for to discover a cure.
		for (int iteration = 0; iteration < discoverCureNumber; ++iteration)
		{
			// Redraw the game screen (makes the output look nicer)
			GetCurrentGame()->DrawGameScreen();

			// Display a message to the user about performing this action.
			cout << "Please select which cards you would like to discard to Discover a Cure for " << *availableCures[userCureSelection][0].getCity()->getPrimaryInfection()->disease << "." << endl;

			// Variable that stores the corresponding (zero-based) menu option number.
			int selectionIndex = -1;

			// Loop through each of the cards listing each one out with a number.
			for (PlayerCard card : availableCures[userCureSelection])
			{
				++selectionIndex;
				cout << (selectionIndex + 1) << ": " << card.getName() << endl;
			}

			// Add an option to return back the the Action selection menu.
			++selectionIndex;
			cout << (selectionIndex + 1) << ": Back to Action selection menu" << endl;

			// Display the iteration number, letting the player know that they be doing the multiple times.
			cout << "[" << iteration + 1 << " of " << discoverCureNumber << "] " << endl;

			// Prompt the user for input using the GetNumericInput.
			int userCardSelection = GetNumericInput(1, selectionIndex + 1, true, true);

			// If the value entered by the user is the last option on the list, return false from the action so it doesn't count towards the action limit.
			if (userCardSelection == selectionIndex)
			{
				return ret;
			}

			// Add the card to the discard card vector (this is a temporary location until all the cards have been selected) and remove it from the cure disease pile.
			discardCards.push_back(availableCures[userCureSelection][userCardSelection]);
			availableCures[userCureSelection].erase(availableCures[userCureSelection].begin() + userCardSelection);
		}
	}
	else
	// If there is exactly the number of cards required to discover a cure, just copy them over to the discard cards vector
	{
		discardCards = availableCures[userCureSelection];
	}

	// Loop through the discard cards vector and remove them from the player hand.
	for (PlayerCard card : discardCards)
	{
		Stack<PlayerCard>::LinkedListNode* playerCards = playerHand.stack_nodes();
		int index = 0;
		while (playerCards != nullptr && playerCards->data.getCity() != card.getCity())
		{
			++index;
			playerCards = playerCards->nextNode;
		}
		GetCurrentGame()->DiscardPlayerCard(playerHand.nth(index));
		playerHand.pop_Nth(index);
	}

	// Set the disease as cured and set the return value to true.
	discardCards[0].getCity()->getPrimaryInfection()->disease->discoverCure();
	ret = true;

	return ret;
}

// *******************************************************************************************
// **     Function: calcDiscoverCureCards													**
// **   Parameters: N/A																		**
// **       Return: vector<vector<PlayerCard>>												**
// **  Description: Goes through the player's hand and groups together cities with the		**
// **				primary disease. If the count of cards is greater than the number		**
// **				required to discover a cure, it is added to an output vector			**
// **				containing a vector of the cards.										**
// *******************************************************************************************
vector<vector<PlayerCard>> BasePlayer::calcDiscoverCureCards() const
{
	// Create a vector containing a vector of player cards.
	vector<vector<PlayerCard>> ret;

	// Create a vector of player cards for each of the diseases.
	vector<PlayerCard> BluePlayerCards;
	vector<PlayerCard> YellowPlayerCards;
	vector<PlayerCard> PurplePlayerCards;
	vector<PlayerCard> RedPlayerCards;

	// Loop through each of the cards in the player hand, adding to the correct vector based on their city's primary disease.
	Stack<PlayerCard>::LinkedListNode* playerCards = playerHand.stack_nodes();
	while (playerCards != nullptr)
	{
		// If the disease on the current player cards matches the Blue disease and the Blue disease is not cured then add it to the blue disease vector.
		if (playerCards->data.getCity()->getPrimaryInfection()->disease->getName() == GetCurrentGame()->getGameOptions().BlueDiseaseName && !playerCards->data.getCity()->getPrimaryInfection()->disease->getIsCured())
		{
			BluePlayerCards.push_back(playerCards->data);
		}
		// If the disease on the current player cards matches the Blue disease and the Yellow disease is not cured then add it to the yellow disease vector.
		else if (playerCards->data.getCity()->getPrimaryInfection()->disease->getName() == GetCurrentGame()->getGameOptions().YellowDiseaseName && !playerCards->data.getCity()->getPrimaryInfection()->disease->getIsCured())
		{
			YellowPlayerCards.push_back(playerCards->data);
		}
		// If the disease on the current player cards matches the Blue disease and the Purple disease is not cured then add it to the purple disease vector.
		else if (playerCards->data.getCity()->getPrimaryInfection()->disease->getName() == GetCurrentGame()->getGameOptions().PurpleDiseaseName && !playerCards->data.getCity()->getPrimaryInfection()->disease->getIsCured())
		{
			PurplePlayerCards.push_back(playerCards->data);
		}
		// If the disease on the current player cards matches the Blue disease and the Red disease is not cured then add it to the red disease vector.
		else if (playerCards->data.getCity()->getPrimaryInfection()->disease->getName() == GetCurrentGame()->getGameOptions().RedDiseaseName && !playerCards->data.getCity()->getPrimaryInfection()->disease->getIsCured())
		{
			RedPlayerCards.push_back(playerCards->data);
		}
		playerCards = playerCards->nextNode;
	}

	// Check if each of the blue vector is greater than the number of cards required for a cure. If so, then add it to the return vector containing a vector of player cards.
	if (BluePlayerCards.size() >= discoverCureNumber)
	{
		ret.push_back(BluePlayerCards);
	}

	// Check if each of the yellow vector is greater than the number of cards required for a cure. If so, then add it to the return vector containing a vector of player cards.
	if (YellowPlayerCards.size() >= discoverCureNumber)
	{
		ret.push_back(YellowPlayerCards);
	}

	// Check if each of the purple vector is greater than the number of cards required for a cure. If so, then add it to the return vector containing a vector of player cards.
	if (PurplePlayerCards.size() >= discoverCureNumber)
	{
		ret.push_back(PurplePlayerCards);
	}

	// Check if each of the red vector is greater than the number of cards required for a cure. If so, then add it to the return vector containing a vector of player cards.
	if (RedPlayerCards.size() >= discoverCureNumber)
	{
		ret.push_back(RedPlayerCards);
	}

	return ret;
}
