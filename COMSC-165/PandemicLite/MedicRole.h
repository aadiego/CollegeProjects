#pragma once
#ifndef MEDICROLE_H
#define MEDICROLE_H

// #16: Game (Pt. 2 - Player Turn Logic) / Role and Player Class (https://github.com/aadiego/CollegeProjects/issues/16)
#include "BasePlayer.h"

class MedicRole : public BasePlayer
{
	private:
		string roleName = "Medic";
		string description = "The Medic removes all infection markers, not 1, of the same disease when doing the Treat Disease action. If a disease has been cured, he automatically removes all of the infection markers of that disease from a city, simply by entering it or being there. This does not take an action.";

	public:
		MedicRole(string name, City*);
		~MedicRole();

		string getRoleName();
		string getDescription();

		bool TreatDisease();
};

#endif
