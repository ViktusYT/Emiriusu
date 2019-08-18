#pragma once
#ifndef DISTRICT_H
#define DISTRICT_H

#include "pch.h"

class District
{
private:

	std::set <BuildingInstance*> buildings; /// Budynki nale��ce do dzielnicy

	Player* owner; /// W�a�ciciel dzielnicy
	void setOwner(Player* newOwner); /// Ustawa w�a�cicela dzielnicy

public:

	District(BuildingInstance* moderator); /// Konstruktor - przyjmuje moderatora (budynek tworzacy dzielnic�, puste dzielnice s� usuwane)

	void addBuilding(BuildingInstance* newBuilding); /// Dodaje nowy budynek do dzielnicy
	std::set <BuildingInstance*> exportData(); /// Eksportuje dane w celu usuni�cia dzielnicy

	int getNumberOfBuildings(); /// Zwraca liczb� budynk�w w dzielnicy
	Player* getOwner(); /// Zwraca w�a�ciciela

};

#endif /* DISTRICT_H */

