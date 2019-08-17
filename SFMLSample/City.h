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
	sf::Vector2f realPos;

	Player* owner; /// W�a�cicel miasta


public:

	/// Konstruktory (przyjmuj� r�ne warto�ci)
	City(sf::Vector2f newPosition, Player* player);
	City(sf::Vector2f newPosition, Player* player, std::vector <std::vector <Building*>> setOfBuildings);
	City(sf::Vector2f newPosition, Player* player, Building* building, sf::Vector2i index);
	City(sf::Vector2f newPosition, Player* player, Building* building, std::pair<short, short> index);
	City(sf::Vector2f newPosition, Player* player, Building* building, short x, short y);

	void draw(sf::RenderWindow& window) override; /// witualna funkcja rysowania
	void draw(sf::RenderWindow& window, sf::View& view, float zoom) override; /// wirtualna funkcja rysowania (tylko mapa u�ywa tej funkcji!)
	void draw(sf::RenderTexture& texture) override;

	void setSetOfBuildings(std::vector <std::vector <Building*>> setOfBuildings); /// Pozwala ustawi� gotowy zestaw budynk�w w mie�cie

	///Funkcje pozwalaj� budowa� budynki w mie�cie dla gracza
	void setSpecificBuilding(Building* building, sf::Vector2i index);
	void setSpecificBuilding(Building* building, std::pair<short, short> index);
	void setSpecificBuilding(Building* building, short x, short y);

	///Usuwanie budynk�w
	void deleteBuilding(sf::Vector2i index);
	void deleteBuilding(std::pair <short, short> index);
	void deleteBuilding(short x, short y);

	///Zwraca dostep do konkretnego budynku
	BuildingInstance* getBuilding(sf::Vector2i index); 
	BuildingInstance* getBuilding(std::pair<short, short> index);
	BuildingInstance* getBuilding(short x, short y);

	bool existBuilding(sf::Vector2i index);
	bool existBuilding(std::pair<short, short> index);
	bool existBuilding(short x, short y);

	///Funkcje zwi�zne z zaznaczaniem
	Function* onSelect() override;
	Function* onClick() override;
	Function* onDeselect() override;

	void setOwner(Player* newPlayer);
	Player* getOwner();

	void makeClearVectorOfBuildings();

	std::vector <BuildingInstance*> getFriends(std::pair <short, short> pos);
};

#endif /*CITY_H*/

