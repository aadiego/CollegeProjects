#include "MedicRole.h"

MedicRole::MedicRole(string name, City* startingLocation) : BasePlayer(name, startingLocation) { }

string MedicRole::getRoleName()
{
	return roleName;
}

string MedicRole::getDescription()
{
	return description;
}

bool MedicRole::TreatDisease()
{
	bool ret = false;

	return ret;
}
