#pragma once
#ifndef CITY_H
#define CITY_H

// #11: City Class (https://github.com/aadiego/CollegeProjects/issues/11)
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
using namespace std;

class Disease;												// Empty Disease class declaration required for some City member functions to work. This fully gets defined in Disease.h
class City
{
	public:
		// Infection linked list data structure
		struct Infection
		{
			Disease* disease = nullptr;						// Holds the disease information (via pointer)
			unsigned int count = 0;							// Holds the total number of infection markers for the disease
			Infection* nextNode = nullptr;					// Holds the next disease in the linked list.
		};

	private:
		// Variables
		string name;										// Holds the name of the city
		WORD color;											// Holds the output formatting color of the city
		bool containsResearchStation = false;				// Holds if the city contains a research station (defaults to false - unless the city is Atlanta)
		vector<City*> neighbors;							// Holds the list of neighboring cities (via pointers)
		Infection* infections = nullptr;					// Holds the current list of infections in the city (linked list)

	public:
		// Constructor
		City(string, WORD, Disease*, City*);

		// Destructor
		~City();

		// Accessors (Getters)
		string getName() const;
		Infection* getPrimaryInfection() const;
		Infection* getInfection(Disease*) const;
		vector<City*> getNeighbors() const;
		bool hasResearchStation() const;
		
		// Mutators (Setters)
		void setNeighbors(vector<City*>);

		// Public functions
		void buildResearchStation();
		void print(bool = false, bool = false, bool = false, bool = false) const;
	
		// Variables
		City* nextNode = nullptr;							// Holds the next city in the linked list for calling a world print.

		// Operator Overrides
		bool operator==(City*) const;
		bool operator!=(City*) const;
		friend ostream& operator<<(ostream&, City&);
};

#endif
