#pragma once
#ifndef CARD_H
#define CARD_H

// #12: Card Base Class and Derived Classes (PlayerCard & InfectionCard) (https://github.com/aadiego/CollegeProjects/issues/12)
#include <string>
#include "City.h"
using namespace std;

template <class T> class Deck;								// Empty Deck template class declaration required for some Card member functions to work. This fully gets defined in Deck.h

class Card
{
	protected:
		// Variables and constants
		string name;										// Holds the name of the card
		City* city;											// Holds a pointer to the city

	public:
		// Constructors
		Card(string name, City* city = nullptr);

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
		City* getCity() const;

		// Public Functions
		virtual bool DrawAction();

		// Operator Overrides
		bool operator==(Card*) const;
};

class PlayerCard : public Card
{
	private:
		// Variables and constants
		bool isEpidemic = false;							// Holds whether this player card is an epidemic or not

	public:
		// Constructor
		PlayerCard();
		PlayerCard(City*, bool = false);

		// Destructor
		~PlayerCard() = default;

		// Accessors (Getters)
		string getName() const override;
		bool getIsEpidemic() const;

		// Public Functions
		bool DrawAction() override;
		static void PreparePlayerDeck(Deck<PlayerCard>*);

		// Operator Overrides
		bool operator==(PlayerCard*) const;
};

class InfectionCard : public Card
{
	private:
		// Variables and constants
		Disease* disease = nullptr;							// Holds a pointer to the disease this infection card affects.

	public:
		// Constructor
		InfectionCard();
		InfectionCard(City*);

		// Destructor
		~InfectionCard() = default;

		// Accessors (Getters)
		string getName() const override;

		// Public Functions
		bool DrawAction(int = 1) const;

		// Operator Overrides
		bool operator==(InfectionCard*) const;
};

#endif
