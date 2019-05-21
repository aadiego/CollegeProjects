#pragma once
#ifndef MEDICROLE_H
#define MEDICROLE_H

// #16: Game (Pt. 2 - Player Turn Logic) / Role and Player Class (https://github.com/aadiego/CollegeProjects/issues/16)
#include "BasePlayer.h"

class MedicRole : public BasePlayer
{
	private:
		// Variables and constants
		const string roleName = "Medic";						// Constant that holds the role name.
		const string description = "The Medic removes all infection markers, not 1, of the same disease when doing the Treat Disease action. If a disease has been cured, he automatically removes all of the infection markers of that disease from a city, simply by entering it or being there. This does not take an action.";				// Constant that holds the description of the role.

		// Private functions
		void ClearCuredInfections();

	public:
		// Constructor
		MedicRole(string name, City*);

		// Destructor
		~MedicRole() = default;

		// Accessors (Getters)
		string getRoleName();
		string getDescription();

		// Base class overrides
		bool DriveFerry() override;
		bool DirectFlight() override;
		bool CharterFlight() override;
		bool ShuttleFlight() override;
		bool TreatDisease(bool = false) override;
};

#endif
