#include "MedicRole.h"
#include "Disease.h"

// *******************************************************************************************
// **     Function: MedicRole (constructor)													**
// **   Parameters: string name																**
// **				City* startingLocation													**
// **       Return: N/A																		**
// **  Description: Initializes a MedicRole instance with the input parameter values.		**
// *******************************************************************************************
MedicRole::MedicRole(string name, City* startingLocation) : BasePlayer(name, startingLocation) { }

// *******************************************************************************************
// **     Function: getRoleName																**
// **   Parameters: N/A																		**
// **       Return: string																	**
// **  Description: Returns the 'roleName' private variable value.							**
// *******************************************************************************************
string MedicRole::getRoleName()
{
	return roleName;
}

// *******************************************************************************************
// **     Function: getDescription															**
// **   Parameters: N/A																		**
// **       Return: string																	**
// **  Description: Returns the 'description' private variable value.						**
// *******************************************************************************************
string MedicRole::getDescription()
{
	return description;
}

// *******************************************************************************************
// **     Function: ClearCuredInfections													**
// **   Parameters: N/A																		**
// **       Return: void																	**
// **  Description: Clears the cured infection markers from the player's current location	**
// **				only if the disease is cured. (per special ability)						**
// *******************************************************************************************
void MedicRole::ClearCuredInfections()
{
	// Node traversal pointer for the city's infections
	City::Infection* infection = playerLocation->getPrimaryInfection();

	// Loop through each infection to see if the infection is cured. If so, then the Medic role can remove all infection markers for free.
	while (infection != nullptr)
	{
		if (infection->disease->getIsCured())
		{
			BasePlayer::TreatDisease(true);
		}
		infection = infection->nextNode;
	}
}

// *******************************************************************************************
// **     Function: DriveFerry																**
// **   Parameters: N/A																		**
// **       Return: bool																	**
// **  Description: Overrides the base implementation by calling the ClearCuredInfections	**
// **				function before and after running the base implementation of			**
// **				DriveFerry.																**
// *******************************************************************************************
bool MedicRole::DriveFerry()
{
	// Call ClearCuredInfections to check if there are any infections that popped up in the player's current city that can be cleaned before moving.
	ClearCuredInfections();

	// Call the base implementation of DriveFerry and store the return value in ret.
	bool ret = BasePlayer::DriveFerry();

	// Call ClearCuredInfections again for the new location and return.
	ClearCuredInfections();
	return ret;
}

// *******************************************************************************************
// **     Function: DirectFlight															**
// **   Parameters: N/A																		**
// **       Return: bool																	**
// **  Description: Overrides the base implementation by calling the ClearCuredInfections	**
// **				function before and after running the base implementation of			**
// **				DirectFlight.															**
// *******************************************************************************************
bool MedicRole::DirectFlight()
{
	// Call ClearCuredInfections to check if there are any infections that popped up in the player's current city that can be cleaned before moving.
	ClearCuredInfections();

	// Call the base implementation of DirectFlight and store the return value in ret.
	bool ret = BasePlayer::DirectFlight();

	// Call ClearCuredInfections again for the new location and return.
	ClearCuredInfections();
	return ret;
}

// *******************************************************************************************
// **     Function: CharterFlight															**
// **   Parameters: N/A																		**
// **       Return: bool																	**
// **  Description: Overrides the base implementation by calling the ClearCuredInfections	**
// **				function before and after running the base implementation of			**
// **				CharterFlight.															**
// *******************************************************************************************
bool MedicRole::CharterFlight()
{
	// Call ClearCuredInfections to check if there are any infections that popped up in the player's current city that can be cleaned before moving.
	ClearCuredInfections();

	// Call the base implementation of CharterFlight and store the return value in ret.
	bool ret = BasePlayer::CharterFlight();

	// Call ClearCuredInfections again for the new location and return.
	ClearCuredInfections();
	return ret;
}

// *******************************************************************************************
// **     Function: ShuttleFlight															**
// **   Parameters: N/A																		**
// **       Return: bool																	**
// **  Description: Overrides the base implementation by calling the ClearCuredInfections	**
// **				function before and after running the base implementation of			**
// **				ShuttleFlight.															**
// *******************************************************************************************
bool MedicRole::ShuttleFlight()
{
	// Call ClearCuredInfections to check if there are any infections that popped up in the player's current city that can be cleaned before moving.
	ClearCuredInfections();

	// Call the base implementation of ShuttleFlight and store the return value in ret.
	bool ret = BasePlayer::ShuttleFlight();

	// Call ClearCuredInfections again for the new location and return.
	ClearCuredInfections();
	return ret;
}

// *******************************************************************************************
// **     Function: TreatDisease															**
// **   Parameters: bool IsMedic															**
// **       Return: bool																	**
// **  Description: Overrides the base implementation by calling the base implementation	**
// **				with the IsMedic flag set to true.										**
// *******************************************************************************************
bool MedicRole::TreatDisease(bool IsMedic)
{
	// Call the base implementation of TreatDisease (with IsMedic flag as true) and return value.
	return BasePlayer::TreatDisease(true);
}
