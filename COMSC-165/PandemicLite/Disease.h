#pragma once
#ifndef DISEASE_H
#define DISEASE_H

// #10: Disease Class (https://github.com/aadiego/CollegeProjects/issues/10)
#include <string>
#include <vector>
#include <Windows.h>
#include "City.h"
using namespace std;

class Disease
{
	private:
		// Variables and constants
		const int MAXINFECTIONS = 24;							// Holds the maximum infections possible per instance of disease class
		const unsigned int MAXPERCITY = 3;						// Holds the maximum infections possible per city instance
		string name;											// Holds the name of the disease
		WORD color;												// Holds the output formatting color of the disease
		bool isCured = false;									// Holds if the disease has been cured
		bool isEradicated = false;								// Holds if the disease has been eradicated (cured and cleared from the board)
		int remainingInfectionCount = MAXINFECTIONS;			// Holds the remaining infection count (defaults to MAXINFECTIONS when instanced)
		
		// Private Helper Functions
		bool infect(City*, int, vector<City*>*);
		bool outbreak(City*, vector<City*>*);
		static bool hasOutbroken(City*, vector<City*>*);

	public:
		// Constructor
		Disease(string, WORD);
		
		// Destructor
		~Disease() = default;
		
		// Accessors (Getters)
		string getName() const;
		int getRemainingInfectionCount() const;
		
		// Public Functions
		bool infect(City*, int = 1);
		bool disinfect(City*, int = 1);
		
		// Operator Overrides
		bool operator==(Disease*) const;
		bool operator!=(Disease*) const;
		friend ostream& operator<<(ostream&, Disease&);
};

#endif
