#pragma once
#ifndef CITY_H
#define CITY_H

#include "pch.h"


class City : public Object, public Selectable
{
	std::vector <std::vector <BuildingInstance*>> buildings; /// Wektor budynk�w
	sf::Texture* texture; /// Przechowuje teksture miasta
	sf::RectangleShape body; /// Przechowuje kszta� miasta
	sf::Vector2f position; /// pierwsza warto�� to indeks x, a druga to index y
	char cityType; /// Typ miasta (nie u�ywane)
	char cityExtra; /// nie u�ywane


public:

	/// Konstruktory (przyjmuj� r�ne warto�ci)
	City(sf::Vector2f newPosition, sf::Texture* newTexture);
	City(sf::Vector2f newPosition, sf::Texture* newTexture, std::vector <std::vector <Building*>> setOfBuildings);
	City(sf::Vector2f newPosition, sf::Texture* newTexture, Building* building, sf::Vector2i index);
	City(sf::Vector2f newPosition, sf::Texture* newTexture, Building* building, std::pair<short, short> index);
	City(sf::Vector2f newPosition, sf::Texture* newTexture, Building* building, short x, short y);

	void draw(sf::RenderWindow& window) override; /// witualna funkcja rysowania
	void draw(sf::RenderWindow& window, sf::View& view, float zoom) override; /// wirtualna funkcja rysowania (tylko mapa u�ywa tej funkcji!)
	void draw(sf::RenderTexture& texture) override;

	void setSetOfBuildings(std::vector <std::vector <Building*>> setOfBuildings); /// Pozwala ustawi� gotowy zestaw budynk�w w mie�cie
	
	///NIE U�YWA� Funkcje pozwalaj� budowa� budynki w mie�cie
	void setSpecificBuilding(Building* building, sf::Vector2i index);
	void setSpecificBuilding(Building* building, std::pair<short, short> index);
	void setSpecificBuilding(Building* building, short x, short y);

	///Funkcje pozwalaj� budowa� budynki w mie�cie dla gracza
	void setSpecificBuildingForPlayer(Player* player, Building* building, sf::Vector2i index);
	void setSpecificBuildingForPlayer(Player* player, Building* building, std::pair<short, short> index);
	void setSpecificBuildingForPlayer(Player* player, Building* building, short x, short y);

	///Usuwanie budynk�w
	void deleteBuilding(sf::Vector2i index);
	void deleteBuilding(std::pair <short, short> index);
	void deleteBuilding(short x, short y);

	///Zwraca dostep do konkretnego budynku
	BuildingInstance* getBuilding(sf::Vector2i index) { return buildings[index.x][index.y]; }
	BuildingInstance* getBuilding(std::pair<short, short> index) { return buildings[index.first][index.second]; }
	BuildingInstance* getBuilding(short x, short y) { return buildings[x][y]; }

	///Funkcje zwi�zne z zaznaczaniem
	Function* onSelect() override;
	Function* onClick() override;
	Function* onDeselect() override;

};

#endif /*CITY_H*/

