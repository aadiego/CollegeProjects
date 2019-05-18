#pragma once
#ifndef GAME_H
#define GAME_H

#include <ctime>
#include <iostream>
#include <string>
#include <Windows.h>
#include "Card.h"
using namespace std;

#define BLUE_DISEASE (BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY)
#define YELLOW_DISEASE (BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY)
#define PURPLE_DISEASE (BACKGROUND_BLUE | BACKGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY)
#define RED_DISEASE (BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY)

#define DEFAULT (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY)
#define BLUE_TEXT (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define YELLOW_TEXT (FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY)
#define PURPLE_TEXT (FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY)
#define RED_TEXT (FOREGROUND_RED | FOREGROUND_INTENSITY)

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