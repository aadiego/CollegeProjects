#pragma once
#ifndef DISEASE_H
#define DISEASE_H

// #10: Disease Class (https://github.com/aadiego/CollegeProjects/issues/10)
#include <string>
#include <vector>
#include <Windows.h>
#include "City.h"

class Disease
{
	private:
		// Variables and constants
		const int MAXINFECTIONS = 24;							// Holds the maximum infections possible per instance of disease class
		const unsigned int MAXPERCITY = 3;						// Holds the maximum infections possible per city instance
		string name;											// Holds the name of the disease
		WORD color;												// Holds the output formatting color of the disease name
		WORD infectioncolor;									// Holds the output formatting color of the infection markers
		bool isCured = false;									// Holds if the disease has been cured
		bool isEradicated = false;								// Holds if the disease has been eradicated (cured and cleared from the board)
		int remainingInfectionCount = MAXINFECTIONS;			// Holds the remaining infection count (defaults to MAXINFECTIONS when instanced)
		
		// Private Helper Functions
		bool infect(City*, int, vector<City*>*);
		bool outbreak(City*, vector<City*>*);
		static bool hasOutbroken(City*, vector<City*>*);

	public:
		// Constructor
		Disease(string, WORD, WORD, Disease*);
		
		// Destructor
		~Disease() = default;
		
		// Accessors (Getters)
		string getName() const;
		bool getIsCured() const;
		bool getIsEradicated() const;
		int getRemainingInfectionCount() const;
		
		// Public Functions
		bool infect(City*, int = 1);
		bool disinfect(City*, int = 1);
		void discoverCure();
		void print(bool = true, int = 1, bool = false, bool = false) const;

		// Variables
		Disease* nextNode = nullptr;							// Holds the next disease in the linked list.
		
		// Operator Overrides
		bool operator==(Disease*) const;
		bool operator!=(Disease*) const;
		friend ostream& operator<<(ostream&, Disease&);
};

#endif
