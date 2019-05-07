#pragma once
#ifndef CARD_H
#define CARD_H

// #12: Card Base Class and Derived Classes (PlayerCard & InfectionCard) (https://github.com/aadiego/CollegeProjects/issues/12)
#include <string>
#include <regex>
#include <vector>
#include "Game.h"
#include "City.h"
using namespace std;

class Card
{
	protected:
		// Variables and constants
		string name;
		string description;
		City* city;

	public:
		// Constructors
		Card(string name) : Card(name, "", nullptr) { };
		Card(string name, string description, City* city = nullptr);

		// Destructor
		virtual ~Card() = default;

		// Exception Class
		class InvalidCardAssignmentException : public exception
		{
			private:
				string message;
			public:
				InvalidCardAssignmentException(const string& message = "") : exception(message.c_str())
				{
					this->message = message;
				}
				friend ostream& operator<<(ostream& stream, InvalidCardAssignmentException& object)
				{
					stream << "Invalid Card Assignment Exception: " + object.message;
					return stream;
				}
		};

		// Accessors (Getters)
		virtual string getName() const;
		virtual string getDescription() const;

		// Public Functions
		virtual bool DrawAction();

		// Operator Overrides
		bool operator==(Card*) const;
};

class PlayerCard : public Card
{
	private:
		// Variables and constants
		bool isEpidemic = false;

	public:
		// Constructor
		PlayerCard(City* = nullptr, bool = false);

		// Accessors (Getters)
		string getName() const override;
		string getDescription() const override;

		// Public Functions
		bool DrawAction() override;
};

class InfectionCard : public Card
{
	private:
		// Variables and constants
		Disease* disease = nullptr;

	public:
		// Constructor
		InfectionCard(City* = nullptr);

		// Accessors (Getters)
		string getName() const override;
		string getDescription() const override;

		// Public Functions
		bool DrawAction(int = 1) const;
};

#endif
