#pragma once
#ifndef DECK_H
#define DECK_H

// #13: Deck Class (https://github.com/aadiego/CollegeProjects/issues/13)
#include <iostream>
#include "Stack.h"
#include "City.h"
using namespace std;

template <class T>
class Deck
{
	private:
		// Variables and constants
		Stack<T> drawPile;
		Stack<T> discardPile;
		unsigned int drawCount = 1;

		// Private Functions
		bool rand_shuffle(Stack<T>*);

	public:
		// Constructors
		Deck();
		Deck(City*, unsigned int = 1);

		// Destructor
		~Deck() = default;

		// Exception Class
		class InvalidPileException : public exception
		{
			private:
				string message;
			public:
				InvalidPileException(const string& message = "") : exception(message.c_str())
				{
					this->message = message;
				}
				friend ostream& operator<<(ostream& stream, InvalidPileException& object)
				{
					stream << "Invalid Pile Exception: " + object.message;
					return stream;
				}
		};

		// Enumerator
		enum Pile { Draw, Discard, Both };

		// Accessors (Getters)
		int getDeckSize(Pile = Both);

		// Mutators (Setters)
		void setDrawCount(unsigned int);
		
		// Public Functions
		bool shuffle(Pile = Both);
		T draw(bool = false, Pile = Draw);
		T drawBottom(bool = false, Pile = Draw);
		bool discard(T, Pile = Discard);
		bool isEmpty(Pile = Draw);
};

#endif
