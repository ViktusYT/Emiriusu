#pragma once
#ifndef DATA_H
#define DATA_H

#include "pch.h"
#include "Types.h"

class Settings
{
	float zoom; /// przybli�enie mapy

public:

	Settings(); /// konstruktor
	void setZoom(float newZoom); /// ustawia nowe przybli�enie mapy (przyjmuje nowe przybli�enie)
	float getZoom() { return zoom; } /// zwraca obecne przybli�enie mapy
	void increaseZoom(float val); ///zmienia przybli�enie mapyo podan� warto��
};

class World
{
	int mapSize; /// rozmiar mapy
	float landPercentage; ///  ilo�� l�du - u�amek
	float mountainsPercentage; /// ilo�� g�r - u�amek

public:

	World(); /// konstruktor
	float getLandPercentage() { return landPercentage; } /// zwraca procent l�du na mapie
	float getMountainsPercentage() { return mountainsPercentage; } /// zwraca procent g�r na mapie
	int getMapSize() { return mapSize; } /// zwraca rozmiar mapy

};

class Textures
{
	std::map <std::string, sf::Texture*> textures; /// wszystkie tekstury
	std::map <std::string, sf::Texture*> tileSets; /// wszystkie zestawy tekstur

	void loadTileSets(); /// �aduje zestawy tekstur do pami�ci
	void loadOtherTextures(); /// �aduje tekstury do pami�ci

public:

	Textures(); /// konstruktor
	sf::Texture* getTileSet (std::string name); /// zwraca wska�nik na tileSet 
	sf::Texture* getTexture (std::string name); /// zwraca wska�nik na tekstur�
	void clearTextures(); /// usuwa wszystkie tekstury z pami�ci
};

class Data
{
	///Tworzenie wszystkich klas przechowuj�cych dane
	World world; /// Przechowuje informacje dotycz�ce �wiata
	Textures textures; /// Przechowuje tekstury
	Settings settings; /// Przechowuje ustawienia gry
	std::map <std::string, std::string> biomeDatas; /// Przechowuje informacje o biomach
	std::map <std::string, Biome*> biomes; /// Przechowuje biomy

	Building* riverPlaceholder; /// Placeholder rzeka
	BuildingInstance* riverPlaceholderInstance; /// Placeholder rzeka - instancja

	void loadBiomeData(); /// �aduje informacje o biomach
	void loadRiverPlaceholder(); ///�aduje budynek-rzeka (tymczasowe)

public:

	Data(); /// konstruktor
	~Data() {} /// destruktor

	World& World() { return world; } /// zwraca referencj� na World_
	Textures& Textures() { return textures; } /// zwraca referencj� na Textures_
	Settings& Settings() { return settings; } /// zwraca referencj� na Settings_
	BuildingInstance* getRiverPlaceholderInstance() { return riverPlaceholderInstance; } /// zwraca wska�nik na bloker budynk�w
	Biome* getBiome(std::string biome); /// zwraca dostep do wkazanego biomu
};

#endif /* DATA_H */

