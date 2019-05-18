#pragma once
#ifndef BASEPLAYER_H
#define BASEPLAYER_H

// #16: Game (Pt. 2 - Player Turn Logic) / Role and Player Class (https://github.com/aadiego/CollegeProjects/issues/16)
#include <string>
#include <vector>
#include "Stack.h"
#include "City.h"
using namespace std;

//template <class T> class Stack;
class PlayerCard;

class BasePlayer
{
	protected:
		string name;
		unsigned int maxActions = 4;
		Stack<PlayerCard> playerHand;
		unsigned int maxCardsInHand = 9;
		City* playerLocation = nullptr;
		unsigned int discoverCureNumber = 5;
		vector<vector<PlayerCard>> calcDiscoverCureCards() const;

	public:
		BasePlayer(string, City*, unsigned int = 4, unsigned int = 5, unsigned int = 9);
		~BasePlayer() = default;

		string getName() const;
		unsigned int getMaxActions() const;

		void AddPlayerCardToHand(PlayerCard);
		vector<string> getAvailableActions();

		virtual bool DriveFerry();
		virtual bool DirectFlight();
		virtual bool CharterFlight();
		virtual bool ShuttleFlight();
		virtual bool BuildResearchStation();
		virtual bool TreatDisease(bool = false);
		virtual bool DiscoverCure();
};

#endif
