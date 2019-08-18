#pragma once
#ifndef MAP_H
#define MAP_H

#include "pch.h"

class Map
{
	int mapSize; /// rozmiar map

	sf::Vector2f position; /// pozycja mapy
	sf::Vector2f size; /// rozmiar mapy
	std::vector <std::vector <Tile*>> Tiles; /// wektor wektor�w pojedynczych kafelk�w

public:
	std::pair<int, int> test1;
	std::pair<int, int> test2;
	Map(int size); /// konstruktor (przyjmuje rozmiar mapy)
	void newMap(); /// tworzy now� map�
	
	/// Zwraca okre�lony kafelek
	Tile* getTile(unsigned x, unsigned y); 
	Tile* getTile(sf::Vector2i position);

	char getMapOverlayData(unsigned x, unsigned y, char level, char type);
	
	void setSize(int newSize); /// ustawia rozmiar mapy (przyjmuje rozmiar mapy)
	int getSize(); /// zwraca rozmiar mapy
};

#endif /* MAP_H */