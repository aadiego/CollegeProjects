// #include "City.h"			// !!!!!! DO NOT INCLUDE CITY.H AS IT IS INCLUDED IN THE DISEASE.H FILE !!!!!!
#include "Disease.h"
#include "Game.h"

// *******************************************************************************************
// **     Function: City (constructor)														**
// **   Parameters: string name																**
// **				WORD color																**
// **				Disease* primaryInfection												**
// **				City* previousNode														**
// **       Return: N/A																		**
// **  Description: Initializes a City instance with the input parameter values.			**
// *******************************************************************************************
City::City(string name, WORD color, Disease* primaryInfection, City* previousNode)
{
	this->name = name;
	this->color = color;

	// Set the containsResearchStation boolean variable to false, unless the city is Atlanta (the home of the CDC and starting location of the game)
	this->containsResearchStation = (name == "Atlanta");

	// Create the Infection linked list head node and set it to the primaryInfection of the city
	this->infections = new Infection();
	this->infections->disease = primaryInfection;
	this->infections->count = 0;
	this->infections->nextNode = nullptr;

	// Check if the previousNode has a value. If so, set the previous node of the city linked list nextNode to this node
	if (previousNode)
	{
		previousNode->nextNode = this;
	}
}

// *******************************************************************************************
// **     Function: ~City (destructor)														**
// **   Parameters: N/A																		**
// **       Return: N/A																		**
// **  Description: Deletes the Infection linked list nodes so the City instance can be		**
// **				deleted.																**
// *******************************************************************************************
City::~City()
{
	// Infection linked list node traversal pointer
	Infection* nodePtr = infections;

	// Loop while the node traversal pointer is not nullptr
	while (nodePtr != nullptr)
	{
		// Set a temporary pointer to hold the current Infection linked list node and advance the node traversal pointer to the next node in the list
		Infection* temp = nodePtr;
		nodePtr = nodePtr->nextNode;

		// Delete the current node.
		delete temp;
	}

}

// *******************************************************************************************
// **     Function: getName																	**
// **   Parameters: N/A																		**
// **       Return: Infection*																**
// **  Description: Returns the 'name' private variable value.								**
// *******************************************************************************************
string City::getName() const
{
	return name;
}

// *******************************************************************************************
// **     Function: getPrimaryInfection														**
// **   Parameters: N/A																		**
// **       Return: Infection*																**
// **  Description: Returns the first Infection node in the Infection linked list.			**
// *******************************************************************************************
City::Infection* City::getPrimaryInfection() const
{
	return infections;
}

// *******************************************************************************************
// **     Function: getInfection															**
// **   Parameters: Disease* disease														**
// **       Return: Infection*																**
// **  Description: Traverses the Infection linked list and returns the Infection that		**
// **				matches the disease. If no matching Infection is found, it will create	**
// **				a new one.																**
// *******************************************************************************************
City::Infection* City::getInfection(Disease* disease) const
{
	// Infection linked list node traversal pointers
	Infection* nodePtr = infections;
	Infection* previousNode = nullptr;

	// Loop while the node traversal pointer is not nullptr and does not match the Infection disease
	while(nodePtr != nullptr && nodePtr->disease != disease)
	{
		// Store the current Infection node in the previousNode pointer variable and advance the nodePtr to the next Infection node.
		previousNode = nodePtr;
		nodePtr = nodePtr->nextNode;
	}

	// Check if the Infection linked list node traversal pointer is nullptr. If so, create a new Infection node for the disease.
	if (!nodePtr)
	{
		// Create a new Infection linked list node and append it to the nextNode pointer on the previous node.
		Infection* newInfection = new Infection();
		newInfection->disease = disease;
		newInfection->count = 0;
		newInfection->nextNode = nullptr;
		previousNode->nextNode = newInfection;
		nodePtr = newInfection;
	}

	// Return the Infection linked list node.
	return nodePtr;
}

// *******************************************************************************************
// **     Function: getNeighbors															**
// **   Parameters: N/A																		**
// **       Return: vector<City*>															**
// **  Description: Returns the 'neighbors' private variable value. 						**
// *******************************************************************************************
vector<City*> City::getNeighbors() const
{
	return neighbors;
}

// *******************************************************************************************
// **     Function: hasResearchStation														**
// **   Parameters: N/A																		**
// **       Return: bool																	**
// **  Description: Returns true if the city has a research station or false if it does		**
// **				not.																	**
// *******************************************************************************************
bool City::hasResearchStation() const
{
	return containsResearchStation;
}

// *******************************************************************************************
// **     Function: setNeighbors															**
// **   Parameters: vector<City*> neighbors													**
// **       Return: void																	**
// **  Description: Sets the 'neighbors' private variable value.		  					**
// *******************************************************************************************
void City::setNeighbors(vector<City*> neighbors)
{
	this->neighbors = neighbors;
}

// *******************************************************************************************
// **     Function: buildResearchStation													**
// **   Parameters: N/A																		**
// **       Return: void																	**
// **  Description: Sets the 'containsResearchStation' private variable to true.			**
// *******************************************************************************************
void City::buildResearchStation()
{
	this->containsResearchStation = true;
}

// *******************************************************************************************
// **     Function: print																	**
// **   Parameters: bool Selected (optional) [Default = false]								**
// **				bool PlayerIsHere (optional) [Default = false]							**
// **				bool ShowResearchStation (optional) [Default = false]					**
// **				bool ShowInfectionMarkers (optional) [Default = false]					**
// **       Return: void																	**
// **  Description: Prints out the City name and it's infection markers, if					**
// **				'ShowInfectionMarkers' argument is true.								**
// *******************************************************************************************
void City::print(bool Selected, bool PlayerIsHere, bool ShowResearchStation, bool ShowInfectionMarkers) const
{
	// Reset the font color to DEFAULT in case it wasn't already.
	ChangeFontColor(DEFAULT);

	// Check if the 'PlayerIsHere' flag is set. If so, print out the player symbol '»' or, if not, prefix whitespace equal to the length of the is player symbol.
	if (PlayerIsHere)
	{
		cout << (char)175 << " ";
	}
	else
	{
		cout << "  ";
	}

	// Set the font color to the city color and output the city name.
	ChangeFontColor(color);
	cout << name;

	// Check if the 'ShowResearchStation' flag is set and if the current city contains a research station. If both, then output the research station symbol '(+)'.
	if (ShowResearchStation && containsResearchStation)
	{
		// Reset the font color to DEFAULT
		ChangeFontColor(DEFAULT);
		cout << " (+)";
	}

	// Check if the 'ShowInfectionMarkers' flag is set. If so, call the print function from each disease/infection to output the city's infection markers.
	if (ShowInfectionMarkers)
	{
		// Output some padding
		cout << "  ";

		// Node traversal pointer
		Infection* infection = infections;

		// Loop through each infection node calling the disease print function.
		while (infection != nullptr)
		{
			infection->disease->print(false, infection->count);
			infection = infection->nextNode;
		}
	}

	// Reset the font color to DEFAULT
	ChangeFontColor(DEFAULT);
}

// *******************************************************************************************
// **     Function: == (operator)															**
// **   Parameters: City* rhs																**
// **       Return: bool																	**
// **  Description: Compares two class instances and returns true if they are equal.		**
// *******************************************************************************************
bool City::operator==(City* rhs) const
{
	return name == rhs->name
		&& color == rhs->color
		&& containsResearchStation == rhs->containsResearchStation
		&& neighbors == rhs->neighbors
		&& infections == rhs->infections;
}

// *******************************************************************************************
// **     Function: != (operator)															**
// **   Parameters: City* rhs																**
// **       Return: bool																	**
// **  Description: Compares two class instances and returns true if they are not equal.	**
// *******************************************************************************************
bool City::operator!=(City* rhs) const
{
	// Call the equality operator and use ! to inverse the returned value.
	return !(this->operator==(rhs));
}

// *******************************************************************************************
// **     Function: << (operator)															**
// **   Parameters: ostream& stream															**
// **				City& object															**
// **       Return: ostream&																**
// **  Description: Prints out the class instance values to the output stream.				**
// *******************************************************************************************
ostream& operator<<(ostream& stream, City& object)
{
	// Set the font color to the city color and output the city name.
	ChangeFontColor(object.color);
	stream << object.name;

	// Reset the font color to DEFAULT before returning the stream
	ChangeFontColor(DEFAULT);
	return stream;
}
