#pragma once
#ifndef BASEPLAYER_H
#define BASEPLAYER_H

// #16: Game (Pt. 2 - Player Turn Logic) / Role and Player Class (https://github.com/aadiego/CollegeProjects/issues/16)
#include <string>
#include <vector>
#include "Stack.h"
#include "City.h"
using namespace std;

class PlayerCard;										// Empty PlayerCard class declaration required for some BasePlayer member functions to work. This fully gets defined in Card.h

class BasePlayer
{
	protected:
		// Variables and constants
		string name;									// Holds the name of the base player (currently the role name)
		unsigned int maxActions = 4;					// Holds the maximum number of actions the player can take
		Stack<PlayerCard> playerHand;					// Holds the cards in the player's hand
		unsigned int maxCardsInHand = 9;				// Holds the maximum number of cards in the player hand
		City* playerLocation = nullptr;					// Holds the player's current location
		unsigned int discoverCureNumber = 5;			// Holds the minimum number of cards to discover a cure for a disease

		// Private functions
		vector<vector<PlayerCard>> calcDiscoverCureCards() const;

	public:
		// Constructor
		BasePlayer(string, City*, unsigned int = 4, unsigned int = 5, unsigned int = 9);

		// Destructor
		virtual ~BasePlayer() = default;

		// Accessors (Getters)
		string getName() const;
		unsigned int getMaxActions() const;
		unsigned int getMaxCardsInHand() const;
		vector<PlayerCard*> getPlayerHandCards();
		City* getPlayerLocation();

		// Public functions
		void AddPlayerCardToHand(PlayerCard);
		void DiscardCardFromHand(PlayerCard*);
		bool isPlayerHandAtMax();
		vector<string> getAvailableActions();

		// Public overridable Action function
		virtual bool DriveFerry();
		virtual bool DirectFlight();
		virtual bool CharterFlight();
		virtual bool ShuttleFlight();
		virtual bool BuildResearchStation();
		virtual bool TreatDisease(bool = false);
		virtual bool DiscoverCure();
};

#endif
