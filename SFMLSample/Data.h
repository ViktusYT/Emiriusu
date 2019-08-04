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

	std::map<std::string, std::map <std::string, std::string>> datas; /// Przechowuje informacje o typach
	std::map <std::string, Biome*> biomes; /// Przechowuje gotowe biomy
	std::map <std::string, Building*> buildings; /// Przechowuje gotowe budynki (pierwowzory)

	void loadData(); /// �aduje informacje o lokalizacji plik�w info
	void loadSelectData(std::string type); /// �aduje informacje o wskazanej tre�ci
	void createTypes(); ///tworzy typy danych na podstawie informacji

	//Funkcje przestarza�e lub nieu�ywane
	std::map <std::string, std::string> biomeDatas; /// Przechowuje informacje o biomach
	Building* riverPlaceholder; /// Placeholder rzeka
	BuildingInstance* riverPlaceholderInstance; /// Placeholder rzeka - instancja

	void loadBiomeData(); /// �aduje informacje o biomach (depracted)
	void loadRiverPlaceholder(); ///�aduje budynek-rzeka (tymczasowe)

public:

	Data(); /// konstruktor
	~Data() {} /// destruktor

	World& World() { return world; } /// zwraca referencj� na World_
	Textures& Textures() { return textures; } /// zwraca referencj� na Textures_
	Settings& Settings() { return settings; } /// zwraca referencj� na Settings_

	Biome* getBiome(std::string type); /// zwraca dost�p do wskazamego biomu
	Building* getBuilding(std::string type); /// zwraca dostep do wskazanego budynku


	BuildingInstance* getRiverPlaceholderInstance() { return riverPlaceholderInstance; } /// zwraca wska�nik na bloker budynk�w
};

#endif /* DATA_H */

