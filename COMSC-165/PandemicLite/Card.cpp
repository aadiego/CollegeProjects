#include "Card.h"

Card::Card(string name, string description, City* city)
{
	this->name = name;
	this->description = description;
	this->city = city;
}

string Card::getName() const
{
	return name;
}

string Card::getDescription() const
{
	return description;
}

bool Card::DrawAction()
{
	return false;
}


PlayerCard::PlayerCard(City* city, bool isEpidemic) : Card("Player Card")
{
	if(city == nullptr && !isEpidemic)
	{
		throw Card::InvalidCardAssignmentException("Cannot generate a PlayerCard object when the City pointer is a nullptr and isEpidemic boolean value is false.");
	}

	this->name = city != nullptr ? city->getName() : "Epidemic";
	this->city = city;
	this->description = !isEpidemic ? "Use this card as a Direct Flight to " + city->getName() + ", a Shuttle Flight from " + city->getName() + " to any city on the board, or to Discover a Cure for the " + city->getPrimaryInfection()->disease->getName() + " disease (requires discarding 5 city cards of the same disease from your hand)." : "Infection rate has increased to {Rate}, {City} has become infected with the {Disease} disease, and existing infections continue to intensify.";
	this->isEpidemic = isEpidemic;
};

bool PlayerCard::DrawAction()
{
	bool ret = false;

	if(isEpidemic)
	{
		int infectionRate = IncrementInfectionRate();
		City* newlyInfectedCity = DrawBottomInfectionCard();
		// TODO: Shuffle Infection Discard pile
		
		string output = description;
		output = regex_replace(output, regex("\\{Rate\\}"), to_string(GetInfectionRate()));
		output = regex_replace(output, regex("\\{City\\}"), newlyInfectedCity->getName());
		output = regex_replace(output, regex("\\{Disease\\}"), newlyInfectedCity->getPrimaryInfection()->disease->getName());

		cout << "EPIDEMIC! " << output << endl;
		ret = true;
	}
	else
	{
		cout << "You have drawn " + this->name << ". " << description << endl;
		ret = true;
	}

	return ret;
}

string PlayerCard::getName() const
{
	return name;
}

string PlayerCard::getDescription() const
{
	return description;
}

InfectionCard::InfectionCard(City* city) : Card("Infection Card")
{
	if (city == nullptr)
	{
		throw Card::InvalidCardAssignmentException("Cannot generate an InfectionCard object when the City pointer is a nullptr.");
	}

	this->name = city->getName();
	this->city = city;
	this->description = name;
	this->disease = city->getPrimaryInfection()->disease;
}

bool InfectionCard::DrawAction(int count) const
{
	bool ret = false;
	ret = disease->infect(city, count);
	return ret;
}

string InfectionCard::getName() const
{
	return name;
}

string InfectionCard::getDescription() const
{
	return description;
}

