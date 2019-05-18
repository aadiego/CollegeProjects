#pragma once
#ifndef GAME_H
#define GAME_H

#include <ctime>
#include <iostream>
#include <string>
#include "ConsoleStyling.h"
#include "Card.h"
using namespace std;

struct GameOptions
{
	unsigned int seed = 0;
	string BlueDiseaseName = "Blue";
	string YellowDiseaseName = "Yellow";
	string PurpleDiseaseName = "Purple";
	string RedDiseaseName = "Red";
	unsigned int NumberOfEpidemics = 4;
};

const int INFECTIONRATESIZE = 7;
const int INFECTIONRATE[INFECTIONRATESIZE] = { 2,2,2,3,3,4,4 };
const int MAXOUTBREAKS = 8;
static int infectionRateIndex = 0;
static int totalOutbreaks = 0;                                          
static GameOptions globalGameOptions;

class City;

int SetupGame(GameOptions);
int PlayGame();
int IncrementOutbreaks();
int IncrementInfectionRate();
int GetInfectionRate();
int GetResearchStationCount();
City* DrawBottomInfectionCard();
bool IntensifyInfectionDeck();
PlayerCard DrawPlayerCard();
bool DiscardPlayerCard(PlayerCard);
City* getCityLinkedList();
string GetStringInput(string);
bool GetDestinationFromInputString(City*&, string&);
vector<City*> GetCitiesContainingResearchStations(City*);
int GetNumericInput(int = INT_MIN, int = INT_MAX, bool = true, bool = false);
bool IsNumeric(string&, int&, bool = true);
string ToLower(string);

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
