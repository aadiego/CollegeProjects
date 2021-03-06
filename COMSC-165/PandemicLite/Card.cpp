#include <random>
#include <regex>
#include "Card.h"
#include "Deck.h"
#include "Disease.h"
#include "Game.h"

// *******************************************************************************************
// **     Function: Card (constructor)														**
// **   Parameters: string name																**
// **				City* city																**
// **       Return: N/A																		**
// **  Description: Initializes a Card instance with the input parameter values.			**
// *******************************************************************************************
Card::Card(string name, City* city)
{
	this->name = name;
	this->city = city;
}

// *******************************************************************************************
// **     Function: getName																	**
// **   Parameters: N/A																		**
// **       Return: string																	**
// **  Description: Returns the 'name' private variable value.								**
// *******************************************************************************************
string Card::getName() const
{
	return name;
}

// *******************************************************************************************
// **     Function: getCity																	**
// **   Parameters: N/A																		**
// **       Return: City*																	**
// **  Description: Returns the 'city' private variable value.								**
// *******************************************************************************************
City* Card::getCity() const
{
	return city;
}

// *******************************************************************************************
// **     Function: DrawAction																**
// **   Parameters: N/A																		**
// **       Return: bool																	**
// **  Description: Calling this base member function will return a							**
// **				NotImplementedException.												**
// *******************************************************************************************
bool Card::DrawAction()
{
	throw NotImplementedException("The DrawAction base member function is not defined. If this exception is getting called check the stack trace to see why.");
}

// *******************************************************************************************
// **     Function: == (operator)															**
// **   Parameters: Card* rhs																**
// **       Return: bool																	**
// **  Description: Compares two class instances and returns true if they are equal.		**
// *******************************************************************************************
bool Card::operator==(Card* rhs) const
{
	// Return true if the name, and city variables match.
	return name == rhs->name
		&& city == rhs->city;
}

// *******************************************************************************************
// **     Function: PlayerCard (default constructor)										**
// **   Parameters: N/A																		**
// **       Return: N/A																		**
// **  Description: Initializes a PlayerCard instance with the default values.				**
// *******************************************************************************************
PlayerCard::PlayerCard() : Card("Player Card") { }

// *******************************************************************************************
// **     Function: PlayerCard (constructor)												**
// **   Parameters: City* city																**
// **				bool isEpidemic															**
// **       Return: N/A																		**
// **  Description: Initializes a PlayerCard instance with the input parameter values.		**
// *******************************************************************************************
PlayerCard::PlayerCard(City* city, bool isEpidemic) : Card("Player Card")
{
	// Check if the city pointer is a nullptr and if isEpidemic is false. If so, throw an exception.
	if(city == nullptr && !isEpidemic)
	{
		throw Card::InvalidCardAssignmentException("Cannot generate a PlayerCard object when the City pointer is a nullptr and isEpidemic boolean value is false.");
	}

	// Set the private variable values based off of input parameter values.
	this->name = city != nullptr ? city->getName() : "Epidemic";
	this->city = city;
	this->isEpidemic = isEpidemic;
}

// *******************************************************************************************
// **     Function: getName																	**
// **   Parameters: N/A																		**
// **       Return: string																	**
// **  Description: Returns the 'name' private variable value.								**
// *******************************************************************************************
string PlayerCard::getName() const
{
	return name;
}

// *******************************************************************************************
// **     Function: getIsEpidemic															**
// **   Parameters: N/A																		**
// **       Return: bool																	**
// **  Description: Returns the 'isEpidemic' private variable value.						**
// *******************************************************************************************
bool PlayerCard::getIsEpidemic() const
{
	return isEpidemic;
}

// *******************************************************************************************
// **     Function: DrawAction																**
// **   Parameters: N/A																		**
// **       Return: bool																	**
// **  Description: Overrides the base implementation of the DrawAction member function.	**
// **				If the PlayerCard is an Epidemic, it will complete the epidemic steps,	**
// **				else it will output a message of what card was added to the player's	**
// **				hand. Returns true to signify that work has been completed.				**
// *******************************************************************************************
bool PlayerCard::DrawAction()
{
	// Set the default return value to false.
	bool ret = false;

	// Check if the card is an epidemic card. If so, execute the epidemic steps.
	if(isEpidemic)
	{
		// 1. Increase: Move the infection rate marker forward 1 space on the Infection Rate Track.
		int infectionRate = GetCurrentGame()->IncrementInfectionRate();

		// 2. Infect: Draw the bottom card from the Infection Deck. Unless its disease color has been eradicated, put 3 disease cubes of that color on the named city.
		City* newlyInfectedCity = GetCurrentGame()->DrawBottomInfectionCard();

		// Output information pertaining to this epidemic.
		cout << "EPIDEMIC! " << endl;
		cout << " - Infection rate has increased to " << GetCurrentGame()->getInfectionRate() << "," << endl;;
		cout << " - " << *newlyInfectedCity << " has become infected with the " << *newlyInfectedCity->getPrimaryInfection()->disease << " disease," << endl;
		cout << " - and existing infections continue to intensify.";
		cout << endl;

		// 3. Intensify: Reshuffle just the cards in the Infection Discard Pile and place them on top of the Infection Deck
		GetCurrentGame()->IntensifyInfectionDeck();

		// Set the return boolean flag to true to signify that work has been completed.
		ret = true;
	}
	else
	{
		// Output a message saying that a city card has been drawn.
		cout << "You have drawn " << *city << ". Use this card:" << endl;
		cout << " - as a Direct Flight to " << *city << "," << endl;
		cout << " - as a Charter Flight from " << *city << " to any city on the board," << endl;
		cout << " - to build a Research Station in " << *city << " (if the player is in the city)," << endl;
		cout << " - or to Discover a Cure for the " << *city->getPrimaryInfection()->disease << " disease (requires discarding 5 city cards of the same disease from your hand).";
		cout << endl;

		// Set the return boolean flag to true to signify that work has been completed.
		ret = true;
	}

	return ret;
}

// *******************************************************************************************
// **     Function: PreparePlayerDeck														**
// **   Parameters: Deck<PlayerCard>* deck													**
// **       Return: void																	**
// **  Description: Prepares the PlayerDeck by shuffling once more, dividing the deck into	**
// **				equal piles, adding an Epidemic card, shuffling the piles, and			**
// **				reassembling the PlayerDeck.											**
// *******************************************************************************************
void PlayerCard::PreparePlayerDeck(Deck<PlayerCard>* deck)
{
	// Shuffle the PlayerDeck again to make sure it's different than the InfectionDeck shuffling (due using the same randomization engine and seed).
	deck->shuffle(Deck<PlayerCard>::Draw);

	// Calculate the individual pile size based off of the number of epidemics.
	int partialPileSize = deck->getDeckSize() / GetCurrentGame()->getGameOptions().NumberOfEpidemics;

	// Loop through creating the individual piles.
	for (int EpidemicCard = 0; EpidemicCard < GetCurrentGame()->getGameOptions().NumberOfEpidemics; ++EpidemicCard)
	{
		// Store the cards in a temporary vector for easy shuffling.
		vector<PlayerCard> partialPile;

		// Loop through the draw deck, drawing the number of cards for the pile.
		for (int card = 0; card < partialPileSize && !deck->isEmpty(); ++card)
		{
			// Draw the card (with the true boolean flag to skip the draw action event) and store it in the vector.
			partialPile.push_back(deck->draw(true));
		}

		// Create an epidemic card and add it to the pile.
		partialPile.push_back(PlayerCard(nullptr, true));

		// Shuffle the pile.
		shuffle(partialPile.begin(), partialPile.end(), default_random_engine(rand()));

		// Loop through the pile until its empty.
		while(!partialPile.empty())
		{
			// Place the cards in the PlayerDeck discard pile (so we can draw new cards on the next iteration) and remove it from the vector.
			deck->discard(partialPile.back());
			partialPile.pop_back();
		}
	}

	// Loop through the PlayerDeck discard pile until its empty.
	while(!deck->isEmpty(Deck<PlayerCard>::Discard))
	{
		// Move the card from the discard pile to the draw pile.
		deck->discard(deck->draw(true, Deck<PlayerCard>::Discard), Deck<PlayerCard>::Draw);
	}
}

// *******************************************************************************************
// **     Function: == (operator)															**
// **   Parameters: PlayerCard* rhs															**
// **       Return: bool																	**
// **  Description: Compares two class instances and returns true if they are equal.		**
// *******************************************************************************************
bool PlayerCard::operator==(PlayerCard* rhs) const
{
	// Return true if the name, city, and isEpidemic variables match.
	return name == rhs->name
		&& city == rhs->city
		&& isEpidemic == rhs->isEpidemic;
}

// *******************************************************************************************
// **     Function: InfectionCard (default constructor)										**
// **   Parameters: N/A																		**
// **       Return: N/A																		**
// **  Description: Initializes a InfectionCard instance with the default values.			**
// *******************************************************************************************
InfectionCard::InfectionCard() : Card("Infection Card") { }

// *******************************************************************************************
// **     Function: InfectionCard (constructor)												**
// **   Parameters: City* city																**
// **       Return: N/A																		**
// **  Description: Initializes a InfectionCard instance with the input parameter values.	**
// *******************************************************************************************
InfectionCard::InfectionCard(City* city) : Card("Infection Card")
{
	// Check if the city pointer is a nullptr. If so, throw an exception.
	if (city == nullptr)
	{
		throw Card::InvalidCardAssignmentException("Cannot generate an InfectionCard object when the City pointer is a nullptr.");
	}

	// Set the private variable values based off of input parameter values.
	this->name = city->getName();
	this->city = city;
	this->disease = city->getPrimaryInfection()->disease;
}

// *******************************************************************************************
// **     Function: getName																	**
// **   Parameters: N/A																		**
// **       Return: string																	**
// **  Description: Returns the 'name' private variable value.								**
// *******************************************************************************************
string InfectionCard::getName() const
{
	return name;
}

// *******************************************************************************************
// **     Function: DrawAction																**
// **   Parameters: int count																**
// **       Return: bool																	**
// **  Description: Overrides the base implementation of the DrawAction member function.	**
// **				Infects the city of the drawn card with the number of infection markers	**
// **				in the count parameter.													**
// *******************************************************************************************
bool InfectionCard::DrawAction(int count) const
{
	// Set the default return value to false.
	bool ret = false;

	// Call the disease infect member function.
	ret = disease->infect(city, count);

	return ret;
}

// *******************************************************************************************
// **     Function: == (operator)															**
// **   Parameters: InfectionCard* rhs														**
// **       Return: bool																	**
// **  Description: Compares two class instances and returns true if they are equal.		**
// *******************************************************************************************
bool InfectionCard::operator==(InfectionCard* rhs) const
{
	// Return true if the name, city, and disease variables match.
	return name == rhs->name
		&& city == rhs->city
		&& disease == rhs->disease;
}
