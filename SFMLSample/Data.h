#pragma once
#ifndef DATA_H
#define DATA_H

#include "pch.h"
#include "Types.h"

class Settings
{
	float zoom; /// przybli�enie mapy

	///Zablokowanie mo�liwo�ci kopiowania
	Settings operator= (const Settings& other);
	Settings(const Settings& other);

public:

	Settings(); /// konstruktor
	void setZoom(float newZoom); /// ustawia nowe przybli�enie mapy (przyjmuje nowe przybli�enie)
	float getZoom(); /// zwraca obecne przybli�enie mapy
	void increaseZoom(float val); ///zmienia przybli�enie mapy o podan� warto��
};

class World
{
	int mapSize; /// rozmiar mapy
	float landPercentage; ///  ilo�� l�du - u�amek
	float mountainsPercentage; /// ilo�� g�r - u�amek

	///Zablokowanie mo�liwo�ci kopiowania
	World operator= (const World& other);
	World(const World& other);

public:

	World(); /// konstruktor
	float getLandPercentage(); /// zwraca procent l�du na mapie
	float getMountainsPercentage(); /// zwraca procent g�r na mapie
	int getMapSize();/// zwraca rozmiar mapy

};

class Textures
{
	std::map <std::string, sf::Texture*> textures; /// wszystkie tekstury
	std::map <std::string, sf::Texture*> tileSets; /// wszystkie zestawy tekstur

	void loadTileSets(); /// �aduje zestawy tekstur do pami�ci
	void loadOtherTextures(); /// �aduje tekstury do pami�ci

	///Zablokowanie mo�liwo�ci kopiowania
	Textures operator= (const Textures& other);
	Textures(const Textures& other);

public:

	Textures(); /// konstruktor
	sf::Texture* getTileSet (std::string name); /// zwraca wska�nik na tileSet 
	sf::Texture* getTexture (std::string name); /// zwraca wska�nik na tekstur�
	sf::Texture* getFractionTexture(Fraction* fraction, std::string name); /// zwraca wska�nik na tektur� styl�w frakcji
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
	std::map <std::string, Fraction*> fractions; /// Przechowuje frakcje
	std::map <std::string, ArmyPrototype*> armies; /// Przechowuje prototypy armii
	std::map <std::string, Player*> playersMap; /// Przechowuje graczy w mapie
	std::map <BuildingInstance*, District*> districtMap; /// Przechowuje budynki i przypisane do nich dzielnice
	std::set <District*> districts; /// Przechowuje dzielnice (dla Garbage Collectora)
	std::queue <Player*> players; ///Przechowuje graczy w kolejce gry
	std::map <BuildingInstance*, City*> citiesByBuildings; /// Przechowuje budynki i przypisane do nich miasta

	void loadData(); /// �aduje informacje o lokalizacji plik�w info
	void loadSelectData(std::string type); /// �aduje informacje o wskazanej tre�ci
	void createTypes(); ///tworzy typy danych na podstawie informacji

	void addToDisMap(BuildingInstance* b, District* d); /// Dodaje nowe warto�ci do mapy Dzielnic
	void garbageCollector(); /// Usuwa niepotrzebne dzielnice

	///Zablokowanie mo�liwo�ci kopiowania
	Data operator= (const Data& other);
	Data(const Data& other);

public:

	Data(); /// konstruktor
	~Data() {} /// destruktor

	World& World() { return world; } /// zwraca referencj� na World
	Textures& Textures() { return textures; } /// zwraca referencj� na Textures
	Settings& Settings() { return settings; } /// zwraca referencj� na Settings

	Biome* getBiome(std::string type); /// zwraca dost�p do wskazamego biomu
	Building* getBuilding(std::string type); /// zwraca dostep do wskazanego budynku
	Fraction* getFraction(std::string type); /// zwraca dost�p do wskazanej frakcji
	ArmyPrototype* getArmyPrototype(std::string type); /// zwraca dost�p do wskazanego prototypu armii
	District* getDistrict(BuildingInstance* buildingD); /// zwraca dostep do wskazanej dzielnicy
	City* getCity(BuildingInstance* buildingC); /// zwraca dostep do wskazanego miasta

	Player* getPlayer(std::string name); /// Pozwala uzyska� dost�p do konkretnego gracza
	void addPlayer(Player* newPlayer); /// Dodaje nowego gracza (nie mo�na tu stworzt� gracza, trzeba go stworzy� wcze�niej)
	bool checkIfPlayer(std::string name); /// Sprawdza, czy gracz o nicku ju� istnieje

	void reportBuildingInstance(BuildingInstance* buildingToCity, City* newCity); /// Trzeba tu zg�o�i� powstanie nowego budynku
	void reportDestructionBuildingInstance(BuildingInstance* toDestroy); /// Nale�y zg�osi� zniszczenie budynku
	void addDistrict(BuildingInstance* buildingToDistrict); /// Dodaje wskazany budynek do dzielnicy 
	int getNumberOfDistricts(); /// Uzyskaj liczb� dzielnic
	void refreshDistricts(Player* refreshPlayer); /// Zbuduj wszystkie dzielnice gracza na nowo (podczas usuwania budynku jest wywo�ywana)
	
};

#endif /* DATA_H */

