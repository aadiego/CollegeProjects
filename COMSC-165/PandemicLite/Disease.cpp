#include "Disease.h"
#include "Game.h"

// *******************************************************************************************
// **     Function: Disease (constructor)													**
// **   Parameters: string name																**
// **				WORD color																**
// **				WORD infectioncolor														**
// **				Disease* previousNode													**
// **       Return: N/A																		**
// **  Description: Initializes a Disease instance with the input parameter values.			**
// *******************************************************************************************
Disease::Disease(string name, WORD color, WORD infectionColor, Disease* previousNode)
{
	this->name = name;
	this->color = color;
	this->infectioncolor = infectioncolor;
	
	// Check if the previousNode has a value. If so, set the previous node of the disease linked list nextNode to this node
	if (previousNode)
	{
		previousNode->nextNode = this;
	}
}

// *******************************************************************************************
// **     Function: getName																	**
// **   Parameters: N/A																		**
// **       Return: string																	**
// **  Description: Returns the 'name' private variable value.								**
// *******************************************************************************************
string Disease::getName() const
{
	return name;
}

// *******************************************************************************************
// **     Function: getIsCured																**
// **   Parameters: N/A																		**
// **       Return: bool																	**
// **  Description: Returns the 'isCured' private variable value.							**
// *******************************************************************************************
bool Disease::getIsCured() const
{
	return isCured;
}

// *******************************************************************************************
// **     Function: getIsEradicated															**
// **   Parameters: N/A																		**
// **       Return: bool																	**
// **  Description: Returns the 'isEradicated' private variable value.						**
// *******************************************************************************************
bool Disease::getIsEradicated() const
{
	return isEradicated;
}

// *******************************************************************************************
// **     Function: getRemainingInfectionCount												**
// **   Parameters: N/A																		**
// **       Return: int																		**
// **  Description: Returns the 'remainingInfectionCount' private variable value.			**
// *******************************************************************************************
int Disease::getRemainingInfectionCount() const
{
	return remainingInfectionCount;
}

// *******************************************************************************************
// **     Function: infect																	**
// **   Parameters: City* city																**
// **				int count (optional) [Default = 1]										**
// **       Return: bool																	**
// **  Description: Infects the city with the number of infection markers for the disease.	**
// **				Returns a true if it has infected at least one city or false if it has	**
// **				infected nothing.														**
// *******************************************************************************************
bool Disease::infect(City* city, int count)
{
	vector<City*> priorOutbreaks = { };
	return infect(city, count, &priorOutbreaks);
}


// *******************************************************************************************
// **     Function: infect																	**
// **   Parameters: City* city																**
// **				int count																**
// **				vector<City*> priorOutbreaks										 	**
// **       Return: bool																	**
// **  Description: Infects the city with the number of infection markers for the disease.	**
// **				Returns a true if it has infected at least one city or false if it has	**
// **				infected nothing.														**
// *******************************************************************************************
bool Disease::infect(City* city, int count, vector<City*>* priorOutbreaks)
{
	// Set the default return value to false.
	bool ret = false;

	// Check if the disease is eradicated. If not, proceed with infecting the city with the number of infection markers.
	if (!isEradicated)
	{
		// Call getInfection from the city pointer to get the infection linked list node that matches this disease instance.
		City::Infection* cityInfection = city->getInfection(this);

		// Loop once per infection marker count
		for(int iteration = 0; iteration < count; ++iteration)
		{
			// Check if the number of existing infection markers for this disease instance is at the maximum per city. If so, the disease outbreaks
			// from the city.
			if (cityInfection->count == MAXPERCITY)
			{
				// Increment the total outbreaks counter and check if we have hit the maximum outbreaks. If so, call the losing end game condition.
				if(IncrementOutbreaks() == MAXOUTBREAKS)
				{
					EndGame(GameOverReason::LOSS_OUTBREAKS);
					return ret;
				}

				// Output message saying that the city has had an outbreak and has infected neighboring cities.
				city->print();
				cout << " has had an outbreak and has infected its neighbors." << endl;

				// Add the city to the prior outbreaks vector and call the outbreak private helper function to infect neighboring cities.
				(*priorOutbreaks).push_back(city);
				ret = outbreak(city, priorOutbreaks);

				// Since the city has already caused an outbreak and cannot outbreak again this round, break out of the for loop to prevent any
				// further infection markers from getting placed this turn.
				break;
			}

			// Output message saying that the city has been infected with a number of infection marker(s). Only on the first iteration.
			if (iteration == 0)
			{
				//city->print();
				cout << *city << " has been infected with " + to_string(count) + " infection marker" + (count > 1 ? "s" : "") + " of the " << *this << " disease." << endl;
			}

			// Increment the infection marker count for this disease and decrement the remaining infection count on the disease.
			cityInfection->count += 1;
			--remainingInfectionCount;

			// Check if the number of remaining disease count is zero (0). If so, call the losing end game condition.
			if (remainingInfectionCount == 0)
			{
				EndGame(GameOverReason::LOSS_INFECTIONMARKERS);
				return ret;
			}

			// Set the return value to true.
			ret = true;
		}
	}
	else
	{
		cout << "The " + name + " disease has been eradicated. No new infection will occur in " + city->getName() + "." << endl;
	}
	return ret;
}

// *******************************************************************************************
// **     Function: disinfect																**
// **   Parameters: City* city																**
// **				int count (optional) [Default = 1]										**
// **       Return: bool																	**
// **  Description: Disinfects the city and returns the number of infection markers back to **
// **				the disease pool. Returns true if the city has been cleansed of at		**
// **				least one infection marker of this disease or false if nothing happens. **
// *******************************************************************************************
bool Disease::disinfect(City* city, int count)
{
	// Set the default return value to false.
	bool ret = false;

	// Check if the disease is eradicated. If not, proceed with disinfecting the city from the number of infection markers.
	if (!isEradicated)
	{
		// Call getInfection from the city pointer to get the infection linked list node that matches this disease instance.
		City::Infection* cityInfection = city->getInfection(this);

		// Loop once per disinfection count
		for (int iteration = count; iteration > 0; --iteration)
		{
			// Check if the city's infection marker count for this disease is zero. If so, break out of the for loop.
			if (cityInfection->count == 0)
			{
				break;
			}

			// Decrement the infection marker count for this disease and increment the remaining infection count on the disease.
			cityInfection->count -= 1;
			++remainingInfectionCount;

			// Check if the disease is cured and if the number of remaining infection markers matches the maximum infection markers. If so, the
			// disease has been eradicated so marked it eradicated and break out of the for loop.
			if (isCured && remainingInfectionCount == MAXINFECTIONS)
			{
				isEradicated = true;
				break;
			}
			ret = true;
		}
	}
	return ret;
}

// *******************************************************************************************
// **     Function: discoverCure															**
// **   Parameters: N/A																		**
// **       Return: void																	**
// **  Description: Sets the 'isCured' private variable value to true.						**
// *******************************************************************************************
void Disease::discoverCure()
{
	isCured = true;
}

void Disease::print(bool ShowDiseaseName, int NumberOfMarkers, bool ShowRemainingCount) const
{
	if (ShowDiseaseName)
	{
		change_font_color(color);
		cout << name;
	}

	for (int iteration = 0; iteration < NumberOfMarkers; ++iteration)
	{
		if (ShowDiseaseName && iteration ==0)
		{
			cout << "  ";
		}

		change_font_color(infectioncolor);
		cout << "  ";
		change_font_color(DEFAULT);
		cout << " ";
	}

	if (ShowRemainingCount)
	{
		cout << remainingInfectionCount;
	}
	change_font_color(DEFAULT);
}


// *******************************************************************************************
// **     Function: outbreak																**
// **   Parameters: City* city																**
// **				vector<City*> priorOutbreaks (optional)									**
// **       Return: bool																	**
// **  Description: Outbreaks the infection from the city to it's neighbors unless the city **
// **				has already had an outbreak this round. Returns true if at lease one	**
// **				neighboring city has been infected or false if nothing has happened.	**
// *******************************************************************************************
bool Disease::outbreak(City* city, vector<City*>* priorOutbreaks)
{
	// Set the default return value to false.
	bool ret = false;

	// Loop once per neighboring city.
	for(City* neighbor : city->getNeighbors())
	{
		// Check if the neighboring city has already had an outbreak this turn. If not, infect the neighboring city.
		if (!hasOutbroken(neighbor, priorOutbreaks))
		{
			// Output prefix message so the player can distinguish between chained outbreaks
			cout << "FROM OUTBREAK IN " + city->getName() + ": ";

			// Infect the neighboring city with one infection marker matching this disease. Also pass along the prior outbreaks vector to prevent
			// potential other outbreaks from causing a feedback loop.
			ret = infect(neighbor, 1, priorOutbreaks);
		}
	}
	return ret;
}

// *******************************************************************************************
// **     Function: hasOutbroken															**
// **   Parameters: City* searchCity														**
// **				vector<City*> priorOutbreaks (optional)									**
// **       Return: bool																	**
// **  Description: Checks the priorOutbreaks vector to see if the searchCity exists.		**
// **				Returns true of the city exists in the vector or false if it does not.	**
// *******************************************************************************************
bool Disease::hasOutbroken(City* searchCity, vector<City*>* priorOutbreaks)
{
	// Set the default return value to false.
	bool ret = false;

	// Loop once per city in priorOutbreaks vector
	for(City* outbrokenCity : * priorOutbreaks)
	{
		// Check if the outbroken city matches the search city. If so, set the return value to true.
		if (outbrokenCity == searchCity)
		{
			ret = true;
		}
	}
	return ret;
}

// *******************************************************************************************
// **     Function: == (operator)															**
// **   Parameters: Disease* rhs															**
// **       Return: bool																	**
// **  Description: Compares two class instances and returns true if they are equal.		**
// *******************************************************************************************
bool Disease::operator==(Disease* rhs) const
{
	// Return true if the name, color, remainingInfectionCount, isCured, and isEradicated variables match.
	return name == rhs->name
		&& color == rhs->color
		&& remainingInfectionCount == rhs->remainingInfectionCount
		&& isCured == rhs->isCured
		&& isEradicated == rhs->isEradicated;
}

// *******************************************************************************************
// **     Function: != (operator)															**
// **   Parameters: Disease* rhs															**
// **       Return: bool																	**
// **  Description: Compares two class instances and returns true if they are not equal.	**
// *******************************************************************************************
bool Disease::operator!=(Disease* rhs) const
{
	// Call the equality operator and use ! to inverse the returned value.
	return !(this->operator==(rhs));
}

// *******************************************************************************************
// **     Function: << (operator)															**
// **   Parameters: ostream& stream															**
// **				Disease& object															**
// **       Return: ostream&																**
// **  Description: Prints out the class instance values to the output stream.				**
// *******************************************************************************************
ostream& operator<<(ostream& stream, Disease& object)
{
	change_font_color(object.color);
	stream << object.name;
	change_font_color(DEFAULT);
	return stream;
}
