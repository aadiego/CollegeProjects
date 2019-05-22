#pragma once
#ifndef GAME_H
#define GAME_H

#include <ctime>
#include <iostream>
#include <string>
#include "ConsoleStyling.h"
#include "Card.h"

using namespace std;

class City;														// Empty City class declaration required for some Game member functions to work. This fully gets defined in City.h
class BasePlayer;												// Empty BasePlayer class declaration required for some Game member functions to work. This fully gets defined in BasePlayer.h

class Game
{
	public:
		struct Options
		{
			unsigned int seed = 0;
			string BlueDiseaseName = "Blue";
			string YellowDiseaseName = "Yellow";
			string PurpleDiseaseName = "Purple";
			string RedDiseaseName = "Red";
			unsigned int NumberOfEpidemics = 4;
		};

		// Enumerator
		enum GameOverReason { NA, WIN, LOSS_OUTBREAKS, LOSS_INFECTIONMARKERS, LOSS_PLAYERDECKEMPTY };

	private:
		// Variables and constants
		int INFECTIONRATESIZE = 7;
		int INFECTIONRATE[7] = { 2,2,2,3,3,4,4 };
		const int MAXOUTBREAKS = 8;
		const int MAXRESEARCHSTATIONS = 6;
		int infectionRateIndex = 0;
		int totalOutbreaks = 0;
		Options options;
		Disease* diseaseLinkedList = nullptr;
		City* cityLinkedList = nullptr;
		Deck<PlayerCard>* playerCardDeck;
		Deck<InfectionCard>* infectionCardDeck;
		BasePlayer* player;
		bool gameOver = false;
		GameOverReason reason = NA;

	public:
		// Constructor	
		Game();

		// Destructor
		~Game();

		// Accessors (Getters)
		Options getGameOptions() const;
		City* getCityLinkedList() const;
		Disease* getDiseaseLinkedList() const;
		int getInfectionRate() const;
		int getInfectionRateIndex() const;
		BasePlayer* getPlayer() const;
		int getMaxOutbreaks() const;
		int getMaxResearchStations() const;
		int getResearchStationCount() const;
		int getTotalOutbreaks() const;

		// Public functions
		void SetupGame(Options);
		bool Play();
		static bool DoPlayerAction(BasePlayer*, string&);
		int IncrementOutbreaks();
		int IncrementInfectionRate();
		PlayerCard DrawPlayerCard() const;
		bool DiscardPlayerCard(PlayerCard) const;
		City* DrawBottomInfectionCard();
		bool IntensifyInfectionDeck();
		void EndGame(GameOverReason);
		void DrawGameScreen() const;

};

// Function prototypes
Game* GetCurrentGame();
string GetStringInput(string);
bool GetDestinationFromInputString(City*&, string&);
vector<City*> GetCitiesContainingResearchStations(City*);
int GetNumericInput(int = INT_MIN, int = INT_MAX, bool = true, bool = false);
bool IsNumeric(string&, int&, bool = true);
string ToLower(string);
string ToUpper(string);
void GamePauseUntilKeyPress(string, WORD);

// Exception classes
class InvalidArgumentException : public exception
{
	private:
		string message;
	public:
		InvalidArgumentException(const string& message = "") : exception(message.c_str())
		{
			this->message = message;
		}
		friend ostream& operator<<(ostream& stream, InvalidArgumentException& object)
		{
			stream << "Invalid Argument Exception: " + object.message + " Please execute the game again with a corrected argument value.";
			return stream;
		}
};

class NotImplementedException : public exception
{
	private:
		string message;
	public:
		NotImplementedException(const string & message = "") : exception(message.c_str())
		{
			this->message = message;
		}
		friend ostream& operator<<(ostream & stream, NotImplementedException& object)
		{
			stream << "Not Implemented Exception: " + object.message;
			return stream;
		}
};

#endif
