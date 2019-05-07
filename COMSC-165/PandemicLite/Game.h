#pragma once
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <locale>
#include <ctime>
#include <sstream>
#include <Windows.h>
#include "City.h"
#include "Disease.h"
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

const int INFECTIONRATESIZE = 7;
const int INFECTIONRATE[INFECTIONRATESIZE] = { 2,2,2,3,3,4,4 };
const int MAXOUTBREAKS = 8;
static int infectionRateIndex = 0;
static int totalOutbreaks = 0;

bool SetupGame(unsigned int);
int IncrementOutbreaks();
int IncrementInfectionRate();
int GetInfectionRate();
City* DrawBottomInfectionCard();

#endif
