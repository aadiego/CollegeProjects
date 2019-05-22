#pragma once
#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include "Game.h"
using namespace std;

// Function Prototypes
bool parseCmdLineArgs(int, char* []);
void displayHelpMessage(string&);
void displayHowToPlayMessage();

// Variables and Constants
extern Game::Options options;								// Holds the game options used by the Game class constructor to build the game objects.
extern Game* CurrentGame;									// Holds a pointer to the current game

#endif
