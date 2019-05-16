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

	public:
		BasePlayer(string name, City* startingLocation, unsigned int maxActions = 4, unsigned int discoverCureNumber = 5);
		~BasePlayer() = default;

		string getName() const;
		string getDescription() const;
		unsigned int getMaxActions() const;

		void AddPlayerCardToHand(PlayerCard);
		vector<string> getAvailableActions();

		bool DriveFerry();
		//bool CharterFlight(Card);
		//bool ShuttleFlight(Card);
		//bool BuildResearchStation(Card);
		//bool TreatDisease();
		//bool DiscoverCure(Disease*, vector<Card>);
		//bool Pass();

};

#endif
