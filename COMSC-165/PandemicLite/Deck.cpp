#include <random>
#include "Deck.h"
#include "City.h"
#include "Card.h"

// *******************************************************************************************
// **     Function: Deck (default constructor)												**
// **   Parameters: N/A																		**
// **       Return: N/A																		**
// **  Description: Initializes a Deck instance with the default values.					**
// *******************************************************************************************
template <class T>
Deck<T>::Deck() { }

// *******************************************************************************************
// **     Function: Deck (constructor)														**
// **   Parameters: City* cityLinkedList													**
// **				unsigned int drawCount													**
// **       Return: N/A																		**
// **  Description: Initializes a PlayerCard instance with the input parameter values.		**
// *******************************************************************************************
template <class T>
Deck<T>::Deck(City* cityLinkedList, unsigned int drawCount)
{
	// City linked list node traversal pointer
	City* nodePtr = cityLinkedList;

	// Loop while the node traversal pointer is not nullptr
	while(nodePtr != nullptr)
	{
		// Create a new card from the city node pointer, add it to the draw pile, and advance the node traversal pointer to the next node.
		T card = T(nodePtr);
		drawPile.push(card);
		nodePtr = nodePtr->nextNode;
	}

	// Set the drawCount private variable based off of input parameter value.
	this->drawCount = drawCount;

	// Shuffle the draw pile.
	shuffle(Draw);
}

// *******************************************************************************************
// **     Function: getDrawCount															**
// **   Parameters: N/A																		**
// **       Return: int																		**
// **  Description: Returns the card draw count.											**
// *******************************************************************************************
template <class T>
int Deck<T>::getDrawCount()
{
	return drawCount;
}

// *******************************************************************************************
// **     Function: getDeckSize																**
// **   Parameters: Pile pile (default = Both)												**
// **       Return: int																		**
// **  Description: Returns the size of provided deck's pile.								**
// *******************************************************************************************
template <class T>
int Deck<T>::getDeckSize(Pile pile)
{
	// Set the default return value to INT32_MIN.
	int ret = INT32_MIN;

	// Switch statement to call the individual pile's (Stack<T>) size member function.
	switch (pile)
	{
		case Draw:
			ret = drawPile.size();
			break;
		case Discard:
			ret = discardPile.size();
			break;
		default:
		case Both:
			// Add together the size of the draw and discard piles.
			ret = drawPile.size() + discardPile.size();
			break;
	}
	return ret;
}

// *******************************************************************************************
// **     Function: setDrawCount															**
// **   Parameters: unsigned int count														**
// **       Return: void																	**
// **  Description: Sets the 'drawCount' private variable value.							**
// *******************************************************************************************
template <class T>
void Deck<T>::setDrawCount(unsigned int count)
{
	this->drawCount = count;
}

// *******************************************************************************************
// **     Function: shuffle																	**
// **   Parameters: Pile pile																**
// **       Return: bool																	**
// **  Description: Shuffles the provided deck's pile. Returns true to signify that work 	**
// **				has been completed.														**
// *******************************************************************************************
template <class T>
bool Deck<T>::shuffle(Pile pile)
{
	// Set the default return value to false.
	bool ret = false;

	// Switch statement to call the rand_shuffle private function for the individual pile (Stack<T>).
	switch(pile)
	{
		case Draw:
			ret = rand_shuffle(&drawPile);
			break;
		case Discard:
			ret = rand_shuffle(&discardPile);
			break;
		default:
		case Both:
			// Shuffle both piles individually.
			ret = rand_shuffle(&drawPile);
			ret += rand_shuffle(&discardPile);
			break;
	}
	return ret;
}

// *******************************************************************************************
// **     Function: rand_shuffle															**
// **   Parameters: Stack<T>* deckStack														**
// **       Return: bool																	**
// **  Description: Calls the built in C++ shuffle function on the specified pile. Returns 	**
// **				true to signify that work has been completed.							**
// *******************************************************************************************
template <class T>
bool Deck<T>::rand_shuffle(Stack<T>* deckStack)
{
	// Set the default return value to false.
	bool ret = false;

	// Temporary vector to hold the cards as the shuffle function cannot shuffle my Stack linked list implementation.
	vector<T> temp;

	// Loop until the deckStack is empty.
	while (!deckStack->isEmpty())
	{
		// Store the top card in the temporary vector and 'pop' it from the stack.
		temp.push_back(deckStack->top());
		deckStack->pop();
	}

	// Call shuffle on the temporary vector.
	std::shuffle(temp.begin(), temp.end(), default_random_engine(rand()));

	// Loop until the temporary vector is empty.
	while(!temp.empty())
	{
		// Store the bottom card in the deckStack vector and 'pop_back' it from the vector.
		deckStack->push(temp.back());
		temp.pop_back();
	}

	// Set the return boolean flag to true to signify that work has been completed.
	ret = true;

	return ret;
}

// *******************************************************************************************
// **     Function: draw																	**
// **   Parameters: bool SkipDrawAction														**
// **				Pile pile																**
// **       Return: T																		**
// **  Description: Draws a card off the specified stack and completes the draw action.		**
// **				Returns the card.														**
// *******************************************************************************************
template <class T>
T Deck<T>::draw(bool SkipDrawAction, Pile pile)
{
	// Create a return variable of the type T.
	T ret;

	// Switch statement to call the appropriate stack's 'top' and 'pop' private functions.
	switch(pile)
	{
		case Draw:
			ret = drawPile.top();
			drawPile.pop();
			break;
		case Discard:
			ret = discardPile.top();
			discardPile.pop();
			break;
		// Since it's impossible to draw from both piles at the same time, throw an exception if 'Both' is provided as an parameter value.
		default:
		case Both:
			throw InvalidPileException();
	}

	// Check if we are skipping the card's draw action. If not, call the card's DrawAction member function.
	if(!SkipDrawAction)
	{
		ret.DrawAction();
	}
	return ret;
}

// *******************************************************************************************
// **     Function: drawBottom																**
// **   Parameters: bool SkipDrawAction														**
// **				Pile pile																**
// **       Return: T																		**
// **  Description: Draws a card off the bottom of the specified stack and completes the 	**
// **				draw action. Returns the card.											**
// *******************************************************************************************
template <class T>
T Deck<T>::drawBottom(bool SkipDrawAction, Pile pile)
{
	// Draw the card off the bottom of the pile and 'pop' it from the stack
	T ret = drawPile.bottom();
	drawPile.pop_back();

	// Check if we are skipping the card's draw action. If not, call the card's DrawAction member function.
	if (!SkipDrawAction)
	{
		ret.DrawAction();
	}
	return ret;
}

// *******************************************************************************************
// **     Function: discard																	**
// **   Parameters: T card																	**
// **				Pile pile																**
// **       Return: bool																	**
// **  Description: Discards the card into the specified pile. Returns true to signify that **
// **				work has been completed.												**
// *******************************************************************************************
template <class T>
bool Deck<T>::discard(T card, Pile pile)
{
	// Set the default return value to false.
	bool ret = false;

	// Switch statement to call the appropriate stack's 'push' private function.
	switch (pile)
	{
		case Draw:
			drawPile.push(card);
			ret = true;
			break;
		case Discard:
			discardPile.push(card);
			ret = true;
			break;
		// Since it's impossible to discard to both piles at the same time, throw an exception if 'Both' is provided as an parameter value.
		default:
		case Both:
			throw InvalidPileException();
	}
	return ret;
}

// *******************************************************************************************
// **     Function: isEmpty																	**
// **   Parameters: Pile pile																**
// **       Return: bool																	**
// **  Description: Returns true if the specified stack is empty.							**
// *******************************************************************************************
template <class T>
bool Deck<T>::isEmpty(Pile pile)
{
	// Set the default return value to false.
	bool ret = false;

	// Switch statement to call the appropriate stack's 'isEmpty' private function.
	switch (pile)
	{
		case Draw:
			ret = drawPile.isEmpty();
			break;
		case Discard:
			ret = discardPile.isEmpty();
			break;
			// Since we can only return one boolean value, throw an exception if 'Both' is provided as an parameter value.
		default:
		case Both:
			throw InvalidPileException();
	}
	return ret;
}

// Explicit Objects that the Deck template class will work with
template class Deck<PlayerCard>;
template class Deck<InfectionCard>;
